#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"

class Projectile {
public:
    Projectile();
    ~Projectile();
    void update(double dt);
    void render();

private:
    PhysicsComponent physics;
    TransformComponent transform;
    float speed;
};