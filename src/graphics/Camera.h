#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

static const glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f,  0.0f);

class Camera {
public:
    Camera(float fov);

    float fov;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;
    float speed = 20.0f;

    glm::mat4 get_view_matrix() const;
    glm::mat4 get_projection_matrix(float aspect_ratio) const;

    void move_backward(float d);
    void move_forward(float d);

    glm::vec3 camera_pos;
    glm::vec3 camera_rot;
    glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);

};