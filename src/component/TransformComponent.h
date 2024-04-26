#pragma once

class TransformComponent {
public:
    TransformComponent(float x, float y, float z, float width, float height, float depth) : x(x), y(y), z(z), width(width), height(height), depth(depth){}

    float x;
    float y;
    float z;
    float pitch;
    float yaw;
    float roll;
    float width;
    float height;
    float depth;
};