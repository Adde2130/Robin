#include "graphics/Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

GLuint tex = 0;

Renderer::Renderer(int window_width, int window_height)
 : window_width(window_width), window_height(window_height) {

}

void Renderer::push_render_component(RenderComponent& c_render) {
    RenderBatch* batch;
    if(!render_batches.count(c_render.shader))
        render_batches.emplace(c_render.shader, new RenderBatch(c_render));

    batch = render_batches.at(c_render.shader);


    if(!batch)
        std::cout << "BIG PROBLEM" << std::endl;

    int64_t vertex_offset = batch->vertices.size() / batch->shader->va_size();
    for(int i = 0; i < c_render.vertex_count; i++)
        batch->vertices.push_back(c_render.vertices[i]);

    for(int i = 0; i < c_render.index_count; i++)
        batch->indices.push_back(c_render.indices[i] + vertex_offset);

    batch->new_data = true;
}



void Renderer::draw(Camera* camera) {
    clear();

    if(!tex)
        tex = LoadTexture("../gfx/Robin.png");
    glBindTextureUnit(0, tex);

    glm::mat4 view = camera->get_view_matrix();
    glm::mat4 projection = camera->get_projection_matrix((float)window_width / (float)window_height);
    for(const auto& pair : render_batches) {
        RenderBatch* batch = pair.second;
  
        if(batch->new_data) {
            std::cout << "Updating batch\n";
            batch->update();
            batch->new_data = false;
        }

        batch->shader->bind();
        if(batch->shader->use_camera()) {
            batch->shader->set_uniform("view", view);
            batch->shader->set_uniform("projection", projection);
        } else if(batch->shader->use_ortho()) {
            glDisable(GL_DEPTH_TEST);
            float left = 0.0f;
            float right = window_width;
            float bottom = 0.0f;
            float top = window_height;
            float near = -1.0f;
            float far = 1.0f;

            glm::mat4 ortho_projection = glm::ortho(left, right, bottom, top, near, far);

            batch->shader->set_uniform("projection", ortho_projection);

            auto loc  = glGetUniformLocation(batch->shader->r_id(), "u_Textures");
            int samplers = 0;
            glUniform1iv(loc, 1, &samplers);
        }

        glBindVertexArray(batch->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);
        glDrawElements(GL_TRIANGLES, batch->indices.size(), GL_UNSIGNED_INT, nullptr);

        glEnable(GL_DEPTH_TEST);
    }

}

void Renderer::set_clear_color(const Vec4f& color){
    glClearColor(color.x, color.y, color.z, color.w);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_window_dimensions(int window_width, int window_height){
    this->window_width = window_width;
    this->window_height = window_height;
}