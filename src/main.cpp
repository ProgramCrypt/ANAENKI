#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include "core/globals.h"
#include "rendering/renderSystem.h"
#include "scene/testScene.h"
#include "core/logSystem.h"
#include "math/matrix2D.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Engine framework pointers
LogSystem* logSystem;

// Rendering pointers
SDL_Window* window;
SDL_GPUDevice* device;
SDL_GPUBuffer* vertexBuffer;
SDL_GPUTransferBuffer* transferBuffer;
SDL_GPUGraphicsPipeline* graphicsPipeline;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    //--------------------------------------------------------------------------
	// Construct Engine Framework Class Objects:
	//--------------------------------------------------------------------------

    logSystem = new LogSystem;
    logSystem->setLogLevel("TRACE", true);

    //--------------------------------------------------------------------------
	// Rendering Setup:
	//--------------------------------------------------------------------------

    // creates application window and sets window resolution based on primary display resolution (if able)
    SDL_Init(SDL_INIT_VIDEO);
    const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    if (displayMode) {
        windowWidth = displayMode->w;
        windowHeight = displayMode->h;
    }
    else {
        windowWidth = 1920;
        windowHeight = 1080;
    }
    windowRatio = windowWidth/windowHeight;
    window = SDL_CreateWindow("ANÆNKI",windowWidth,windowHeight,0);
    
    // creates the device
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);
    SDL_ClaimWindowForGPUDevice(device, window);

    // creates vertex and fragment shaders
    SDL_GPUShader* vertexShader = renderSystem::createVertexShader("src/rendering/shaders/vertex.spv", device);
    SDL_GPUShader* fragmentShader = renderSystem::createFragmentShader("src/rendering/shaders/fragment.spv", device);

    // creates graphics pipeline
    graphicsPipeline = renderSystem::createGPUGraphicsPipeline(vertexShader, fragmentShader, device, window);

    // creates vertex and transfer buffers
    vertexBuffer = renderSystem::createVertexBuffer(sizeof(testTriangle), device);
    transferBuffer = renderSystem::createTransferBuffer(sizeof(testTriangle), device);
    renderSystem::fillTransferBuffer(transferBuffer, testTriangle, sizeof(testTriangle), device);

    // performs copy pass
    renderSystem::bufferCopyPass(transferBuffer, vertexBuffer, sizeof(testTriangle), device);

    // Logs creation of rendering components
    if (window != nullptr && window != NULL) logSystem->log('D', "SDL_Init", "Window creation successful.");
    else logSystem->log('F', "SDL_Init", "Window creation failed.");
    if (device != nullptr && device != NULL) logSystem->log('D', "SDL_Init", "Device creation successful.");
    else logSystem->log('F', "SDL_Init", "Device creation failed.");
    if (vertexBuffer != nullptr && vertexBuffer != NULL) logSystem->log('D', "SDL_Init", "Vertex buffer creation successful.");
    else logSystem->log('F', "SDL_Init", "Vertex buffer creation failed.");
    if (transferBuffer != nullptr && transferBuffer != NULL) logSystem->log('D', "SDL_Init", "Transfer buffer creation successful.");
    else logSystem->log('F', "SDL_Init", "Transfer buffer creation failed.");
    if (graphicsPipeline != nullptr && graphicsPipeline != NULL) logSystem->log('D', "SDL_Init", "Graphics pipeline creation successful.");
    else logSystem->log('F', "SDL_Init", "Graphics pipeline creation failed.");

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate)
{
    //--------------------------------------------------------------------------
	// Rendering:
	//--------------------------------------------------------------------------
    logSystem->log('T', "SDL_AppIterate", "Beginning Rendering.");

    // acquires the command buffer
    SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);

    // gets the swapchain texture
    SDL_GPUTexture* swapchainTexture;
    Uint32 width, height;
    SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &swapchainTexture, &width, &height);

    // ends the frame early if a swapchain texture is not available
    if (swapchainTexture == NULL)
    {
        logSystem->log('E', "SDL_AppIterate", "SwapchainTexture get failed.");

        // you must always submit the command buffer
        SDL_SubmitGPUCommandBuffer(commandBuffer);
        return SDL_APP_CONTINUE;
    }

    // creates the color target
    SDL_GPUColorTargetInfo colorTargetInfo{};
    colorTargetInfo.clear_color = {240/255.0f, 240/255.0f, 240/255.0f, 255/255.0f};
    colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
    colorTargetInfo.texture = swapchainTexture;

    // begins a render pass and binds the pipeline
    SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, NULL);
    if (renderPass == NULL || renderPass == nullptr) logSystem->log('E', "SDL_AppIterate", "renderPass object creation failed.");
    SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline);

    // binds the vertex buffer
    SDL_GPUBufferBinding bufferBindings[1];
    bufferBindings[0].buffer = vertexBuffer; // index 0 is slot 0
    bufferBindings[0].offset = 0; // starts from the first byte
    SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings, 1); // binds one buffer starting from slot 0

    // issues draw call
    SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

    // end the render pass
    SDL_EndGPURenderPass(renderPass);

    // submit the command buffer
    SDL_SubmitGPUCommandBuffer(commandBuffer);

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // Detects keyboard KEY_DOWN inputs
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_Q:
                return SDL_APP_SUCCESS;
                break;
            default:
                break;
        }
    }
    // Detects keyboard KEY_UP inputs
    if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.key) {
            default:
                break;
        }
    }

    // closes the window on request
    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    //--------------------------------------------------------------------------
	// Deallocate Engine Framework Class Objects:
	//--------------------------------------------------------------------------

    delete logSystem;

    //--------------------------------------------------------------------------
	// Deallocate Render Objects:
	//--------------------------------------------------------------------------

    // releases buffers
    SDL_ReleaseGPUBuffer(device, vertexBuffer);

    // destroys the GPU device
    SDL_DestroyGPUDevice(device);

    // destroys the window
    SDL_DestroyWindow(window);
}