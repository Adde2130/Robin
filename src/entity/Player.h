#pragma once

#include <memory>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"

class Player {
public:
    Player(float x, float y, float z);
    void add_render_component(Renderer& renderer);
private:
    float x, y, z;
    float speed;
    std::unique_ptr<RenderComponent> HUD_Logo;
    std::unique_ptr<RenderComponent> HUD_HealthBar;
};