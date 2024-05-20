#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class PhysicsComponent : public Component {
public:
    PhysicsComponent() : Component(C_PHYSICS), pos(0.0f), vel(0.0f), rot(0.0f), mass(0.0f), gravity(0.0f) {}

    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 rot;

    float mass; 
    float gravity;
};