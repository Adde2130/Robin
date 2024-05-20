#pragma once

#include "util/Math.h"

class AABB {
public:
    AABB(Vec3f min_point, Vec3f max_point);
    AABB(Vec3f pos, float width, float height, float depth);
    bool contains(const Vec3f& point);
    bool intersects(const AABB& other);
    Vec3f get_overlap(const AABB& other);

    Vec3f min_point;
    Vec3f max_point;
};