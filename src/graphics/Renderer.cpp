#include "graphics/Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

void Renderer::draw(Model& model) const {
    model.get_shader().bind();
    model.get_va().bind();
    model.get_ib().bind();

    glDrawElements(GL_TRIANGLES, model.get_ib().get_count(), GL_UNSIGNED_SHORT, nullptr);    
}

void Renderer::draw(VertexArray* va, IndexBuffer* ib, Shader* shader){
    shader->bind();
    va->bind();
    ib->bind();

    glDrawElements(GL_TRIANGLES, ib->get_count(), GL_UNSIGNED_SHORT, nullptr);    
}

void Renderer::set_clear_color(const Vec4f& color){
    glClearColor(color.x, color.y, color.z, color.w);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}