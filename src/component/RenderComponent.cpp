#include "RenderComponent.h"

RenderComponent::RenderComponent(float* vertices, unsigned int vertex_count, int* indices, unsigned int index_count, const std::string shader) : Component(C_RENDER) {
    this->vertices = new float[vertex_count];
    std::copy(vertices, vertices + vertex_count, this->vertices);
    this->vertex_count = vertex_count;

    this->indices = new int[index_count];
    std::copy(indices, indices + index_count, this->indices);
    this->index_count = index_count;

    this->shader = shader;
}

RenderComponent::~RenderComponent(){
    delete[] vertices;
    delete[] indices;
}