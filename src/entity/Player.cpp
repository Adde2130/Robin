#include "Player.h"
#include "Texture.h"

struct HUDVertex {
    float position[2];
    float texCoords[2];
    float texIndex[1];
    float color[3];
};

Player::Player(float x, float y, float z)
: x(x), y(y), z(z) {
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