#pragma once

#include "Component.h"
#include "AABB.h"

class CollisionComponent : public Component {
public:
    CollisionComponent() : Component(C_COLLISION), aabb({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}) {}

    AABB aabb;
    bool movable = false;
};