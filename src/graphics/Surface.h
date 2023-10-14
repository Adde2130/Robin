#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

class Surface {
public:
    VertexArray* va;
    IndexBuffer* ib;
    Shader* shader;
    glm::mat4 model;
    Surface(float x, float y, float z, float width, float height);
    ~Surface();
    void draw(Camera* cam);
};