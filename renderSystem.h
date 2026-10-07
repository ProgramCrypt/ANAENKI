#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL3/SDL.h>

struct vertex
{
    float x, y, z;      // position
    float r, g, b, a;   // color and alpha
};

namespace renderSystem
{
    // Creates a vertex buffer for the GPU
    SDL_GPUBuffer* createVertexBuffer(size_t dataSize, SDL_GPUDevice* device);
    
    // Creates a transfer buffer for the GPU
    SDL_GPUTransferBuffer* createTransferBuffer(size_t dataSize, SDL_GPUDevice* device);

    // Fills transfer buffer
    void fillTransferBuffer(SDL_GPUTransferBuffer* buffer, vertex vertArr[], size_t dataSize, SDL_GPUDevice* device);

    // Performs a copy pass from a transfer buffer to another buffer
    void bufferCopyPass(SDL_GPUTransferBuffer* transferBuffer, SDL_GPUBuffer* destinationBuffer, size_t dataSize, SDL_GPUDevice* device);

    // Creates vertex shader for the GPU
    SDL_GPUShader* createVertexShader(const char* file, SDL_GPUDevice* device);
    
    // Creates fragment shader for the GPU
    SDL_GPUShader* createFragmentShader(const char* file, SDL_GPUDevice* device);

    // Creates the GPU graphics pipeline to set up all appropriate data for the GPU to render
    SDL_GPUGraphicsPipeline* createGPUGraphicsPipeline(SDL_GPUShader* vertexShader, SDL_GPUShader* fragmentShader, SDL_GPUDevice* device, SDL_Window* window);
}

#endif // RENDERSYSTEM_H