#pragma once

#include "glm/glm.hpp"

class PhysicsComponent {
public:
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 rot;

    float mass; 
    float gravity;
};