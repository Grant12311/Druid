// You must include OpenGL yousrself. Druid also does NOT handle windowing, context creation, etc. It just abstracts the OpenGL API
#include <GLES3/gl31.h>

// Druid is a header-only library. Just include druid.h
#include "druid.h"

int main()
{
    Druid::VAO vao; // Create Vertex Array
    Druid::IBO ibo; // Create Index Buffer
    Druid::VBO vbo; // Create Vertex Buffer

    // Example Verticies and Indicies (for rendering a quad with an orthographics matrix)
    std::array<float, 16> quadVertices = {
        0, 0, 0.0f, 1.0f, // lower left
        0, 1, 0.0f, 0.0f, // upper left
        1, 1, 1.0f, 0.0f, // upper right
        1, 0, 1.0f, 1.0f  // lower right
    };
    std::array<unsigned int, 6> quadIndices = {
        0, 1, 2,
        0, 3, 2
    };

    vao.bind(); // Bind Vertex Array
    ibo.bind(); // Bind Index Buffer
    vbo.bind(); // Bind Vertex Buffer

    // Push Data Into the Vertex Buffer
    vbo.fill(quadVertices.size() * sizeof(float), // Size
                   quadVertices.data(),                 // Pointer to Data
                   GL_STATIC_DRAW);                     // Usage

    // Push Data Into the Index Buffer
    ibo.fill(quadIndices.size() * sizeof(unsigned int), // Size
                   quadIndices.data(),                        // Pointer to Data
                   GL_STATIC_DRAW);                           // Usage

    // Create Vertex Attribute Pointer
    vao.setAttrib(0,                 // Index
                        2,                 // Count
                        GL_FLOAT,          // Type
                        GL_FALSE,          // Normalized
                        sizeof(float) * 4, // Stride
                        0);                // Offset

    // Create Another Vertex Attribute Pointer
    vao.setAttrib(1,                  // Index
                        2,                  // Count
                        GL_FLOAT,           // Type
                        GL_FALSE,           // Normalized
                        sizeof(float) * 4,  // Stride
                        2 * sizeof(float)); // Offset

    ibo.unbind(); // Set Index Buffer Binding to Zero
    vbo.unbind(); // Set Vertex Buffer Binding to Zero
    vao.unbind();  // Set Index Array Binding to Zero

    return 0;
}
