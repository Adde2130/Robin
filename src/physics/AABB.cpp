#include "AABB.h"

// AABB::AABB(Vec3f min_point, Vec3f max_point)
// :min_point(min_point), max_point(max_point) {
//     static_assert(
//         min_point.x < max_point.x &&
//         min_point.y < max_point.y && 
//         min_point.z < max_point.z,
//         "Failed constructing AABB: min_point is not strictly smaller than max_point"
//     );
// }

// AABB::AABB(const Vec3f& pos, float width, float height, float depth)
// : min_point(Vec3f(pos.x - width / 2, pos.y - height / 2, pos.z - depth / 2)),
//   max_point(Vec3f(pos.x + width / 2, pos.y + height / 2, pos.z + depth / 2)) {

// }

// bool AABB::contains(const Vec3f& point) {
//     return min_point.x < point.x &&
//            min_point.y < point.y &&
//            min_point.z < point.z &&
//            max_point.x > point.x &&
//            max_point.y > point.y &&
//            max_point.z > point.z;
// }

// bool AABB::intersects(const AABB& other) {
//     return this.min_point.x <= b.max_point.x &&
//            this.max_point.x >= b.min_point.x &&
//            this.min_point.y <= b.max_point.y &&
//            this.max_point.y >= b.min_point.y &&
//            this.min_point.z <= b.max_point.z &&
//            this.max_point.z >= b.min_point.z;
// }

// Vec3f get_overlap(const AABB& other) {
//     const float left_overlap = other.max_point.x - min_point.x;
//     const float right_overlap = max_point.x - other.min_point.x;

//     const float top_overlap = other.max_point.y - min_point.y;
//     const float bottom_overlap = max_point.y - other.min_point.y;

//     const float front_overlap = other.max_point.z - min_point.z;
//     const float back_overlap = max_point.z - other.min_point.z;

//     return Vec3f(std::min(left_overlap, right_overlap), std::min(top_overlap, bottom_overlap), std::min(front_overlap, back_overlap));
// }