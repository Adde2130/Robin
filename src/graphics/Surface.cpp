#include "Surface.h"

Surface::Surface(float x, float y, float z, float width, float height) : model(translate(glm::mat4(1.0f), glm::vec3(x, y, z))) {
    float vertices[] = {
        0.0f,  0.0f, 0.0f,   0.0f, 0.0f,
        width, 0.0f, 0.0f,   1.0f, 0.0f,
        width, 0.0f, height, 1.0f, 1.0f,
        0.0f,  0.0f, height, 0.0f, 1.0f,
    };

    unsigned short indices[] = {
        0, 1, 2, 
        2, 3, 0
    };

    va = new VertexArray();
    vb = new VertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va->add_buffer(vb, layout);

    ib = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned short));
    shader = new Shader("shader/solid_color.vs", "shader/solid_color.fs");
}

Surface::~Surface(){
    delete shader;
    delete ib;
    delete va;
    delete vb;
}

void Surface::draw(Camera* cam) {
    shader->bind();
    shader->set_uniform("model", model);
    shader->set_uniform("view", cam->get_view_matrix());
    shader->set_uniform("projection", cam->get_projection_matrix(4.0f / 3.0f));
    shader->set_uniform("u_Color", { 1, 238.0f / 255, 139.0f / 255, 1});
    va->bind();
    ib->bind();

    //glDrawElements(GL_TRIANGLES, ib->get_count(), GL_UNSIGNED_SHORT, nullptr);
}