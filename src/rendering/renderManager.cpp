#include <SDL3/SDL.h>
#include "rendering/renderManager.h"

namespace renderSystem
{
    // Creates a vertex buffer for the GPU
    SDL_GPUBuffer* createVertexBuffer(size_t dataSize, SDL_GPUDevice* device)
    {
        SDL_GPUBufferCreateInfo bufferInfo{};
        bufferInfo.size = dataSize;
        bufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
        SDL_GPUBuffer* vertexBuffer = SDL_CreateGPUBuffer(device, &bufferInfo);

        return vertexBuffer;
    }

    // Creates a transfer buffer for the GPU
    SDL_GPUTransferBuffer* createTransferBuffer(size_t dataSize, SDL_GPUDevice *device)
    {
        SDL_GPUTransferBufferCreateInfo transferInfo{};
        transferInfo.size = dataSize;
        transferInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
        SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(device, &transferInfo);
        
        return transferBuffer;
    }

    // Fills transfer buffer
    void fillTransferBuffer(SDL_GPUTransferBuffer* buffer, vertex vertArr[], size_t dataSize, SDL_GPUDevice* device)
    {
        // maps the transfer buffer to a pointer
        vertex* data = (vertex*)SDL_MapGPUTransferBuffer(device, buffer, false);

        // sets the data values
        SDL_memcpy(data, vertArr, dataSize);

        // unmaps the pointer once the transfer buffer has been updated
        SDL_UnmapGPUTransferBuffer(device, buffer);
    }

    // Performs a copy pass from a transfer buffer to another buffer
    void bufferCopyPass(SDL_GPUTransferBuffer* transferBuffer, SDL_GPUBuffer* destinationBuffer, size_t dataSize, SDL_GPUDevice* device)
    {
        // starts copy pass
        SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);
        SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);

        // defines data location
        SDL_GPUTransferBufferLocation location{};
        location.transfer_buffer = transferBuffer;
        location.offset = 0;

        // defines where to upload data
        SDL_GPUBufferRegion region{};
        region.buffer = destinationBuffer;
        region.size = dataSize;
        region.offset = 0;

        // uploads data
        SDL_UploadToGPUBuffer(copyPass, &location, &region, true);

        // ends the copy pass
        SDL_EndGPUCopyPass(copyPass);
        SDL_SubmitGPUCommandBuffer(commandBuffer);
    }
    
    // Creates vertex shader for the GPU
    SDL_GPUShader* createVertexShader(const char* file, SDL_GPUDevice* device)
    {
        // loads vertex shader code
        size_t vertexCodeSize;
        void* vertexCode = SDL_LoadFile(file, &vertexCodeSize);

        // creates vertex shader
        SDL_GPUShaderCreateInfo vertexInfo{};
        vertexInfo.code = (Uint8*)vertexCode; // converts to an array of bytes
        vertexInfo.code_size = vertexCodeSize;
        vertexInfo.entrypoint = "main";
        vertexInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
        vertexInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
        vertexInfo.num_samplers = 0;
        vertexInfo.num_storage_buffers = 0;
        vertexInfo.num_storage_textures = 0;
        vertexInfo.num_uniform_buffers = 0;
        SDL_GPUShader* vertexShader = SDL_CreateGPUShader(device, &vertexInfo);

        // frees the file
        SDL_free(vertexCode);

        return vertexShader;
    }
    
    // Creates fragment shader for the GPU
    SDL_GPUShader* createFragmentShader(const char* file, SDL_GPUDevice* device)
    {
        // loads vertex shader code
        size_t fragmentCodeSize;
        void* fragmentCode = SDL_LoadFile(file, &fragmentCodeSize);

        // creates vertex shader
        SDL_GPUShaderCreateInfo fragmentInfo{};
        fragmentInfo.code = (Uint8*)fragmentCode; // converts to an array of bytes
        fragmentInfo.code_size = fragmentCodeSize;
        fragmentInfo.entrypoint = "main";
        fragmentInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
        fragmentInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
        fragmentInfo.num_samplers = 0;
        fragmentInfo.num_storage_buffers = 0;
        fragmentInfo.num_storage_textures = 0;
        fragmentInfo.num_uniform_buffers = 0;
        SDL_GPUShader* fragmentShader = SDL_CreateGPUShader(device, &fragmentInfo);

        // frees the file
        SDL_free(fragmentCode);

        return fragmentShader;
    }

    // Creates the GPU graphics pipeline to set up all appropriate data for the GPU to render
    SDL_GPUGraphicsPipeline* createGPUGraphicsPipeline(SDL_GPUShader* vertexShader, SDL_GPUShader* fragmentShader, SDL_GPUDevice* device, SDL_Window* window)
    {
        SDL_GPUGraphicsPipelineCreateInfo pipelineInfo{};

        // binds shaders
        pipelineInfo.vertex_shader = vertexShader;
        pipelineInfo.fragment_shader = fragmentShader;

        // sets to draw triangles
        pipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

        // describes the vertex buffers
        SDL_GPUVertexBufferDescription vertexBufferDescriptions[1];
        vertexBufferDescriptions[0].slot = 0;
        vertexBufferDescriptions[0].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
        vertexBufferDescriptions[0].instance_step_rate = 0;
        vertexBufferDescriptions[0].pitch = sizeof(vertex);

        pipelineInfo.vertex_input_state.num_vertex_buffers = 1;
        pipelineInfo.vertex_input_state.vertex_buffer_descriptions = vertexBufferDescriptions;

        // describes the vertex attribute
        SDL_GPUVertexAttribute vertexAttributes[2];

        // a_position
        vertexAttributes[0].buffer_slot = 0;    // fetches data from the buffer at slot 0
        vertexAttributes[0].location = 0;       // layout (location = 0) in shader
        vertexAttributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3; // vec3
        vertexAttributes[0].offset = 0;         // starts from the first byte from current buffer position

        // a_color
        vertexAttributes[1].buffer_slot = 0;    // uses buffer at slot 0
        vertexAttributes[1].location = 1;       // layout (location = 1) in shader
        vertexAttributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4; // vec4
        vertexAttributes[1].offset = sizeof(float) * 3; // 4th float from current buffer position

        pipelineInfo.vertex_input_state.num_vertex_attributes = 2;
        pipelineInfo.vertex_input_state.vertex_attributes = vertexAttributes;

        // describes the color target
        SDL_GPUColorTargetDescription colorTargetDescriptions[1];
        colorTargetDescriptions[0] = {};
        colorTargetDescriptions[0].blend_state.enable_blend = true;
        colorTargetDescriptions[0].blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;
        colorTargetDescriptions[0].blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
        colorTargetDescriptions[0].blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
        colorTargetDescriptions[0].blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        colorTargetDescriptions[0].blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
        colorTargetDescriptions[0].blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        colorTargetDescriptions[0].format = SDL_GetGPUSwapchainTextureFormat(device, window);

        pipelineInfo.target_info.num_color_targets = 1;
        pipelineInfo.target_info.color_target_descriptions = colorTargetDescriptions;

        // creates the pipeline
        SDL_GPUGraphicsPipeline* graphicsPipeline = SDL_CreateGPUGraphicsPipeline(device, &pipelineInfo);

        // releases the shaders after the pipeline has been built (may remove this if we want to reuse the shaders)
        SDL_ReleaseGPUShader(device, vertexShader);
        SDL_ReleaseGPUShader(device, fragmentShader);

        return graphicsPipeline;
    }

    // Makes the GPU perform a render
    void renderOnGPU(SDL_GPUCommandBuffer* commandBuffer, SDL_GPUColorTargetInfo colorTargetInfo, SDL_GPUGraphicsPipeline* graphicsPipeline, SDL_GPUBuffer* vertexBuffer)
    {
        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, NULL);

        // binds the graphics pipeline
        SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline);

        // binds the vertex buffer
        SDL_GPUBufferBinding bufferBindings[1];
        bufferBindings[0].buffer = vertexBuffer; // index 0 is slot 0
        bufferBindings[0].offset - 0; // starts from the first byte

        SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings, 1); // binds one bufferstarting from slot 0

        // issues a draw call
        SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

        // ends the render pass
        SDL_EndGPURenderPass(renderPass);
    }
}
