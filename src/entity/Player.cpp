#include "Player.h"
#include "Texture.h"
#include "Input.h"
#include "EventHandler.h"
#include "ModelUtil.h"

using namespace std::placeholders;

struct HUDVertex {
    float position[2];
    float texCoords[2];
    float texIndex[1];
    float color[3];
};

Player::Player(EventHandler& h_event, float x, float y, float z) {
    p_camera = std::make_shared<Camera>(45.0f);

    c_physics.pos = glm::vec3(x, y, z);
    c_physics.gravity = 40;

    h_event.subscribe(E_UPDATE, std::bind(&Player::update, this, _1));
    h_event.subscribe(E_MOUSE_MOVE, std::bind(&Player::mouse_update, this, _1));
    h_event.subscribe(E_KEYBOARD, std::bind(&Player::keyboard_update, this, _1));

    /* Robin logo */
    HUDVertex* vertices_1 = new HUDVertex[4] {
        20.0f,   20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        148.0f,  20.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        148.0f, 148.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        20.0f,  148.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };

    int* indices_1 = new int[6] {
        0, 1, 2, 2, 3, 0
    };

    HUD_Logo = std::make_unique<RenderComponent>((float*)vertices_1, 32, indices_1, 6, "hud");


    /* Crosshair */
    Quad q_cro(300, 300, 18, 18);

    HUDVertex* vertices_2 = new HUDVertex[4] {
        250.0f, 250.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f,
        282.0f, 250.0f, 1.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f,
        282.0f, 282.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f,
        250.0f, 282.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f,
    };

    int* indices_2 = new int[6] {
        0, 1, 2, 2, 3, 0
    };

    HUD_Crosshair = std::make_unique<RenderComponent>((float*)vertices_2, 32, indices_2, 6, "hud");
}

void Player::add_render_component(Renderer& renderer) {
    renderer.push_render_component(*this->HUD_Logo);
    renderer.push_render_component(*this->HUD_Crosshair);
}

void Player::update(const Event& e) {
    const UpdateEvent& e_u = static_cast<const UpdateEvent&>(e);

    const float dt = e_u.dt;
    const float yaw = c_physics.rot.y;

    glm::vec3 dir(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw)));
    glm::vec3 dir_sideways(-dir.z, 0.0f, dir.x);

    if(key_pressed(GLFW_KEY_W))
        c_physics.pos += dir * (dt * speed);
    if(key_pressed(GLFW_KEY_S))
        c_physics.pos -= dir * (dt * speed);
    if(key_pressed(GLFW_KEY_D))
        c_physics.pos += dir_sideways * (speed * dt);
    if(key_pressed(GLFW_KEY_A))
        c_physics.pos -= dir_sideways * (speed * dt);

    c_physics.vel.y -= c_physics.gravity * dt;
    c_physics.vel.x = 0;
    c_physics.vel.z = 0;

    c_physics.pos += c_physics.vel * dt;
    c_physics.pos.y = clampf(c_physics.pos.y, 0.0f, 100.0f);

    if(key_pressed(GLFW_KEY_I))
        c_physics.rot.x += (dt * 40.0f);
    if(key_pressed(GLFW_KEY_K))
        c_physics.rot.x -= (dt * 40.0f);
    if(key_pressed(GLFW_KEY_L))
        c_physics.rot.y += (dt * 40.0f);
    if(key_pressed(GLFW_KEY_J))
        c_physics.rot.y -= (dt * 40.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(p_camera->yaw)) * cos(glm::radians(p_camera->pitch));
    front.y = sin(glm::radians(p_camera->pitch));
    front.z = sin(glm::radians(p_camera->yaw)) * cos(glm::radians(p_camera->pitch));
    p_camera->camera_front = glm::normalize(front);

    p_camera->camera_pos = c_physics.pos;
    p_camera->yaw = c_physics.rot.y;
    p_camera->pitch = c_physics.rot.x;
    
}

void Player::mouse_update(const Event& e) {
    const MouseMoveEvent& e_mm = static_cast<const MouseMoveEvent&>(e);

    const float sens = 0.1f;
    c_physics.rot.y += e_mm.dx * sens; // Rotation around the y-axis
    c_physics.rot.x -= e_mm.dy * sens; // Rotation around the x-axis
    c_physics.rot.x = clampf(c_physics.rot.x, -89.9f, 89.9f);
    glm::normalize(c_physics.rot);

    p_camera->yaw = c_physics.rot.y;
    p_camera->pitch = c_physics.rot.x;
}

void Player::keyboard_update(const Event& e) {
    const KeyboardEvent& e_kb = static_cast<const KeyboardEvent&>(e);

    switch(e_kb.key) {
    case GLFW_KEY_SPACE:
        if(e_kb.action == GLFW_PRESS)
           c_physics.vel.y = 10;
        break;

    }

    
}