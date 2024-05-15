#pragma once

#include <memory>
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "UpdateComponent.h"
#include "PhysicsComponent.h"
#include "Renderer.h"

class Player {
public:
    Player(float x, float y, float z);
    void add_render_component(Renderer& renderer);

    UpdateComponent<float> c_frame_update;
    UpdateComponent<double, double, double, double> c_mouse_update;
    UpdateComponent<int, int, int> c_keyboard_update;
    
    PhysicsComponent c_physics;

    std::shared_ptr<Camera> get_camera() { return p_camera; }
private:
    void frame_update(float dt);
    void mouse_update(double x, double y, double dx, double dy);
    void keyboard_update(int key, int action, int mode);

    float speed = 15.0f;

    std::shared_ptr<Camera> p_camera;

    std::unique_ptr<RenderComponent> HUD_Logo;
    std::unique_ptr<RenderComponent> HUD_HealthBar;
};