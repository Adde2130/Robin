#pragma once

#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"

class Cube {
public: 
    Cube(TransformComponent transform, Vec4f v4_color);
    ~Cube();
    void render(Renderer& renderer);
private:
    TransformComponent c_transform;
    RenderComponent* c_render;
    Vec4f v4_color;
};