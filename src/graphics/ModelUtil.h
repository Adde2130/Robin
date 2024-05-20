#pragma once

#include <memory>
#include "util/Math.h"

struct Quad{
    Quad(const float x, const float y, const float width, const float height) {
        top_left.x = x;
        top_left.y = y;

        top_right.x = x + width;
        top_right.y = y;

        bot_left.x = x;
        bot_left.y = y + height;

        bot_right.x = x + width;
        bot_right.y = y + height;
    };
    Vec2f top_left;
    Vec2f top_right;
    Vec2f bot_left;
    Vec2f bot_right;
};

