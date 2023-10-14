#pragma once

struct Vec4f {
    float x;
    float y;
    float z;
    float w;
};

struct Vec3f {
    float x;
    float y;
    float z;
};

float clampf(float val, float min, float max);