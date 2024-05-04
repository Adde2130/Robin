#include "Camera.h"

Camera::Camera(float fov) : fov(fov) { 
    camera_pos = glm::vec3(0.0f, 0.0f, 0.0f); 

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(front);
}

glm::mat4 Camera::get_view_matrix() const {
    return glm::lookAt(camera_pos, camera_pos + camera_front, CAMERA_UP);
}

glm::mat4 Camera::get_projection_matrix(float aspect_ratio) const {
    return glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
}