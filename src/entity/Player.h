#pragma once

#include <memory>
#include "EventHandler.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "Renderer.h"

class Player {
public:
    Player(EventHandler& h_events, float x, float y, float z);
    void add_render_component(Renderer& renderer);

    PhysicsComponent c_physics;

    std::shared_ptr<Camera> get_camera() { return p_camera; }
private:
    void update(const Event& e);
    void mouse_update(const Event& e);
    void keyboard_update(const Event& e);

    float speed = 15.0f;

    std::shared_ptr<Camera> p_camera;

    std::unique_ptr<RenderComponent> HUD_Logo;
    std::unique_ptr<RenderComponent> HUD_HealthBar;
};