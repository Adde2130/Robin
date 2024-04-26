#include "RenderComponent.h"

RenderComponent::RenderComponent(float* vertices, unsigned int vertex_count, int* indices, unsigned int index_count, const std::string shader) {
    this->vertices = vertices;
    this->vertex_count = vertex_count;

    this->indices = indices;
    this->index_count = index_count;

    this->shader = shader;
}