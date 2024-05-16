#pragma once

#include "Component.h"
#include <string>
#include <vector>

class RenderComponent : Component {
public:
    RenderComponent(float* vertices, unsigned int vertex_count, int* indices, unsigned int index_count, const std::string shader);
    ~RenderComponent();

    void   setVertices(float* vertices) { this->vertices = vertices; }
    float* getVertices() { return this->vertices; }

    std::string shader;

    float* vertices;
    int    vertex_count;
    int    batch_vertices_index;

    int*   indices;
    int    index_count;
    int    batch_indices_index;

};