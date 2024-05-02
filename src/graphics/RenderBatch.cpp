#include "RenderBatch.h"
#include "ResourceManager.h"

RenderBatch::RenderBatch(RenderComponent& c_render) {
    std::cout << "Creating render batch with the shader '" << c_render.shader << "'" << std::endl;

    if(!LoadedShaders.count(c_render.shader)) {
        std::cout << "Loading shader '" << c_render.shader << "'" << std::endl;
        shader = new Shader(c_render.shader);
    }

    shader = LoadedShaders.at(c_render.shader);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);


    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexAttribPointer(0, 2 + shader->is_3D(), GL_FLOAT, GL_FALSE, shader->va_size() * sizeof(float), 0);

    int current_size = 2 + shader->is_3D();
    for(int i = 0; current_size < shader->va_size(); i++ ) {
        glEnableVertexArrayAttrib(vao, i + 1);
        glVertexAttribPointer(i + 1, shader->param_sizes()[i], GL_FLOAT, GL_FALSE, shader->va_size() * sizeof(float), (const void*)(current_size * sizeof(float)));
        current_size += shader->param_sizes()[i];
    }

    glCreateBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

RenderBatch::~RenderBatch() {
    std::cout << "Deconstructing render batch" << std::endl;
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &ebo);
}

void RenderBatch::update() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), &this->vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(int), &this->indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}