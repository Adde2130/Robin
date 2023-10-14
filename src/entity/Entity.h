#pragma once

class Entity {
public:
    Entity(float x, float y, float z, float width, float height) : x(x), y(y), z(z), width(width), height(height) {}
    
    float x;
    float y;
    float z;
    float width;
    float height;
};