// #include "CollisionHandler.h"

// void CollisionHandler::add(PhysicsComponent& c_physics) {
//     cv_physics.push_back(c_physics);
// }

// void CollisionHandler::update() {
//     for(PhysicsComponent& first : cv_physics) {
//         for(PhysicsComponent& second : cv_physics) {
//             if(first == second)
//                 continue;

//             AABB aabb_1 = first.aabb;
//             aabb_1.min_point += first.pos;
//             aabb_1.max_point += first.pos;

//             AABB aabb_2 = second.aabb;
//             aabb_2.min_point += second.pos;
//             aabb_2.max_point += second.pos;
            
//             if(aabb_1.intersects(aabb_2)) {
//                 Vec3f separation = aabb_1.get_overlap(aabb_2);

//                 // Separate along X-axis
//                 if (overlap.x < 0) {
//                     float moveX = std::abs(overlap.x);
//                     float centerDistanceX = (max_point.x + min_point.x - other.max_point.x - other.min_point.x) / 2.0f;
//                     float move = std::abs(centerDistanceX) < moveX ? centerDistanceX : moveX * (centerDistanceX < 0 ? -1 : 1);
//                     first.pos.x += move;
//                 }

//                 // Separate along Y-axis
//                 if (overlap.y < 0) {
//                     float moveY = std::abs(overlap.y);
//                     float centerDistanceY = (max_point.y + min_point.y - other.max_point.y - other.min_point.y) / 2.0f;
//                     float move = std::abs(centerDistanceY) < moveY ? centerDistanceY : moveY * (centerDistanceY < 0 ? -1 : 1);
//                     first.pos.y += move;
//                 }

//                 // Separate along Z-axis
//                 if (overlap.z < 0) {
//                     float moveZ = std::abs(overlap.z);
//                     float centerDistanceZ = (max_point.z + min_point.z - other.max_point.z - other.min_point.z) / 2.0f;
//                     float move = std::abs(centerDistanceZ) < moveZ ? centerDistanceZ : moveZ * (centerDistanceZ < 0 ? -1 : 1);
//                     first.pos.z += move;
//                 }
//             }
//         }
//     }
// }