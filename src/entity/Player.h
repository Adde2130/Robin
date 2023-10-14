#pragma once

#include "Entity.h"

class Player {
public:
    Player(float x, float y, float z);
private:
    Entity entity;
    float speed;
};