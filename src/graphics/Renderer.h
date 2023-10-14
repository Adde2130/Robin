#pragma once

#include <GL/glew.h>
#include "Model.h"
#include "util/math.h"
#include "Camera.h"

#define ASSERT(x) if(!x) __debugbreak();

class Renderer {
public:
    void clear();
    void set_clear_color(const Vec4f& color);
    void draw(Model& model) const;
    void draw(VertexArray* va, IndexBuffer* ib, Shader* shader);
};