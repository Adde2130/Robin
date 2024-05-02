#pragma once

#include "RenderComponent.h"
#include "Shader.h"
#include "GL/glew.h"
#include <vector>

struct RenderBatch {
    RenderBatch(RenderComponent& c_render);
    ~RenderBatch();
    Shader* shader;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    std::vector<float> vertices;
    std::vector<int> indices;

    bool new_data = false;

    void update();
};