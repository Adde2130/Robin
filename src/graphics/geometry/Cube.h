#pragma once

#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"

class Cube {
public: 
    Cube(TransformComponent transform, Vec4f v4_color);
    void render(Renderer& renderer);
private:
    TransformComponent c_transform;
    Vec4f v4_color;
};