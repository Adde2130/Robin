#pragma once

#include "RenderComponent.h"
#include "Shader.h"
#include "GL/glew.h"
#include <vector>
#include <memory>

struct RenderBatch {
    RenderBatch(const std::string& s_shader);
    ~RenderBatch();
    std::shared_ptr<Shader> shader;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    std::vector<float> vertices;
    std::vector<int> indices;
    std::vector<std::pair<std::string, unsigned int>> textures;

    bool new_data = false;

    void push_render_component(RenderComponent& c_render);
    void update();
    void update_component(RenderComponent& c_render);
};