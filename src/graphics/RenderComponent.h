#pragma once

#include <string>
#include <vector>

class RenderComponent {
public:
    RenderComponent(float* vertices, unsigned int vertex_count, int* indices, unsigned int index_count, const std::string shader);

    void   setVertices(float* vertices) { this->vertices = vertices; }
    float* getVertices() { return this->vertices; }

    std::string shader;

    float* vertices;
    int    vertex_count;

    int*   indices;
    int    index_count;
};