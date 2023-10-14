#include "Model.h"

Model::Model(VertexArray& va, IndexBuffer& ib, Shader& shader) : va(va), ib(ib), shader(shader) {
    
}

Model Model::create_cube(const float size){
    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        size, 0.0f, 0.0f, 1.0f, 0.0f,
        size, size, 0.0f, 1.0f, 1.0f,
        0.0f, size, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size, 0.0f, 0.0f,
        size, 0.0f, size, 1.0f, 0.0f,
        size, size, size, 1.0f, 1.0f,
        0.0f, size, size, 0.0f, 1.0f
    };

    unsigned short indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        2, 3, 7, 7, 6, 2,
        0, 3, 7, 7, 4, 0,
        1, 2, 6, 6, 5, 1 
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.add_buffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned short));

    Shader shader("shader/solid_color.vs", "shader/solid_color.fs");

    Model model(va, ib, shader);
    return model;
}