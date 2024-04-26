#include "Player.h"
#include "Texture.h"

Player::Player(float x, float y, float z)
: x(x), y(y), z(z), HUD(nullptr) {
    float* vertices = new float[24] {
        20.0f, 20.0f, 0.0f, 0.0f, 0.0f,
        148.0f, 20.0f, 1.0f, 0.0f, 0.0f,
        148.0f, 148.0f, 1.0f, 1.0f, 0.0f,
        20.0f, 148.0f, 0.0f, 1.0f, 0.0f,
    };

    int* indices = new int[6] {
        0, 1, 2, 2, 3, 0
    };

    HUD = std::make_unique<RenderComponent>(vertices, 24, indices, 6, "hud");
    
}

void Player::add_render_component(Renderer& renderer) {
    renderer.push_render_component(*this->HUD);
}