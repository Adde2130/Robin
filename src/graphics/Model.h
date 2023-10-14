#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Model {
private:
    VertexArray va; 
    IndexBuffer ib;
    Shader shader;
public:
    Model(VertexArray& va, IndexBuffer& ib, Shader& shader);
    
    inline VertexArray& get_va() { return va; }
    inline IndexBuffer& get_ib() { return ib; }
    inline Shader& get_shader()  { return shader; }

    static Model create_cube(const float size);
};