#include "rendering/renderSystem.h"


// test triangle to render
static vertex testTriangle[]
{
    {0.0f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f, 1.0f},    // top vertex (position, color)
    {-0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.0f, 1.0f},    // bottom left vertex (position, color)
    {0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f}     // bottom right vertex (position, color)
};