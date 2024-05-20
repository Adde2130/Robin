#include "RenderBatch.h"
#include "ResourceManager.h"

RenderBatch::RenderBatch(const std::string& s_shader) {
    std::cout << "Creating render batch with the shader '" << s_shader << "'" << std::endl;

    if(!LoadedShaders.count(s_shader))
        shader = LoadShader(s_shader);
    else
        shader = LoadedShaders.at(s_shader);

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

void RenderBatch::push_render_component(RenderComponent& c_render) {
    int64_t vertex_offset = vertices.size() / shader->va_size();

    c_render.batch_vertices_index = vertices.size();
    for(int i = 0; i < c_render.vertex_count; i++)
        vertices.push_back(c_render.vertices[i]);

    c_render.batch_indices_index = indices.size();
    for(int i = 0; i < c_render.index_count; i++)
        indices.push_back(c_render.indices[i] + vertex_offset);

    new_data = true;
}

void RenderBatch::update() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), &this->vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(int), &this->indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderBatch::update_component(RenderComponent& c_render) {
    for(int i = 0; i < c_render.vertex_count; i++)
        vertices[i + c_render.batch_vertices_index] = c_render.vertices[i];

    new_data = true;
}