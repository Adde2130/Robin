#include "Player.h"
#include "Texture.h"
#include "Input.h"

using namespace std::placeholders;

struct HUDVertex {
    float position[2];
    float texCoords[2];
    float texIndex[1];
    float color[3];
};

Player::Player(float x, float y, float z) {
    p_camera = std::make_shared<Camera>(45.0f);

    c_physics.pos = glm::vec3(x, y, z);
    c_physics.gravity = 40;

    c_frame_update.update = std::bind(&Player::frame_update, this, _1);
    c_mouse_update.update = std::bind(&Player::mouse_update, this, _1, _2, _3, _4);
    c_keyboard_update.update = std::bind(&Player::keyboard_update, this, _1, _2, _3);

    subscribe_mouse_event(c_mouse_update);
    subscribe_keyboard_event(c_keyboard_update);

    HUDVertex* vertices = new HUDVertex[4] {
        20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        148.0f, 20.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        148.0f, 148.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        20.0f, 148.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };

    int* indices = new int[6] {
        0, 1, 2, 2, 3, 0
    };

    HUD_Logo = std::make_unique<RenderComponent>((float*)vertices, 32, indices, 6, "hud");
}

void Player::add_render_component(Renderer& renderer) {
    renderer.push_render_component(*this->HUD_Logo);
}

void Player::frame_update(float dt) {
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

void Player::mouse_update(double x, double y, double dx, double dy) {
    const float sens = 0.1f;
    c_physics.rot.y += dx * sens; // Rotation around the y-axis
    c_physics.rot.x -= dy * sens; // Rotation around the x-axis
    c_physics.rot.x = clampf(c_physics.rot.x, -89.9f, 89.9f);
    glm::normalize(c_physics.rot);

    p_camera->yaw = c_physics.rot.y;
    p_camera->pitch = c_physics.rot.x;
}

void Player::keyboard_update(int key, int action, int mode) {
    switch(key) {
    case GLFW_KEY_SPACE:
        if(action == GLFW_PRESS)
           c_physics.vel.y = 10;
        break;

    }

    
}