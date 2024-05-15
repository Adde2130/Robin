#include "Cube.h"
Cube::Cube(TransformComponent c_transform, Vec4f v4_color) 
: c_transform(c_transform), v4_color(v4_color) {
    float vertices[] = {
        c_transform.x,                     c_transform.y,                      c_transform.z, v4_color.x, v4_color.y, v4_color.z, v4_color.w,
        c_transform.x + c_transform.width, c_transform.y,                      c_transform.z, v4_color.x, v4_color.y, v4_color.z, v4_color.w,
        c_transform.x + c_transform.width, c_transform.y + c_transform.height, c_transform.z, v4_color.x, v4_color.y, v4_color.z, v4_color.w,
        c_transform.x,                     c_transform.y + c_transform.height, c_transform.z, v4_color.x, v4_color.y, v4_color.z, v4_color.w,

        c_transform.x,                     c_transform.y,                      c_transform.z + c_transform.depth, v4_color.x, v4_color.y, v4_color.z, v4_color.w,
        c_transform.x + c_transform.width, c_transform.y,                      c_transform.z + c_transform.depth, v4_color.x, v4_color.y, v4_color.z, v4_color.w,
        c_transform.x + c_transform.width, c_transform.y + c_transform.height, c_transform.z + c_transform.depth, v4_color.x, v4_color.y, v4_color.z, v4_color.w,
        c_transform.x,                     c_transform.y + c_transform.height, c_transform.z + c_transform.depth, v4_color.x, v4_color.y, v4_color.z, v4_color.w
    };

    int indices[] = {
        0, 1, 2, 2, 3, 0, // Front face
        1, 5, 6, 6, 2, 1, // Right face
        4, 5, 6, 6, 7, 4, // Back face
        0, 4, 7, 7, 3, 0, // Left face
        0, 1, 5, 5, 4, 0, // Top face
        2, 3, 7, 7, 6, 2  // Bottom face
    };

    c_render = new RenderComponent(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(int), "cube");
}

Cube::~Cube() {
    delete c_render;
}

void Cube::render(Renderer& renderer) {
    renderer.push_render_component(*c_render);
}