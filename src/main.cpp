#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/Shader.h"
#include "debug/opengl_debug.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "util/Math.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "Model.h"
#include "Window.h"
#include "Camera.h"
#include "Surface.h"

const Vec4f COLOR_DARK   = { 45.9f / 255, 48.0f  / 255, 61.0f / 255, 1 };
const Vec4f COLOR_RED    = { 1          , 119.0f / 255, 121.0f / 255, 1 };
const Vec4f COLOR_YELLOW = { 1, 238.0f / 255, 139.0f / 255, 1};
const Vec4f COLOR_GREEN  = { 123.0f / 255, 1, 113.0f / 255, 1};
const Vec4f COLOR_PINK   = { 1, 143.0f / 255, 1, 1 };
const Vec4f COLOR_BLUE   = { 133.0f / 255, 182.0f / 255, 1, 1};

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

void update(GLFWwindow* window, Camera* camera) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->camera_pos += camera->speed * camera->camera_front;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->camera_pos -= camera->speed * camera->camera_front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->camera_pos -= glm::normalize(glm::cross(camera->camera_front, CAMERA_UP)) * camera->speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->camera_pos += glm::normalize(glm::cross(camera->camera_front, CAMERA_UP)) * camera->speed;
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    Camera camera(45.0f);

    camera.camera_pos.x -= 2;

    GLFWwindow* window = window_init(WINDOW_WIDTH, WINDOW_HEIGHT, &camera, false, 240);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    enable_opengl_callbacks();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    float size = 0.5f;

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        size, 0.0f, 0.0f, 1.0f, 0.0f,
        size, size, 0.0f, 1.0f, 1.0f,
        0.0f, size, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size, 0.0f, 0.0f,
        size, 0.0f, size, 1.0f, 0.0f,
        size, size, size, 1.0f, 1.0f,
        0.0f, size, size, 0.0f, 1.0f
    };

    unsigned short indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        2, 3, 7, 7, 6, 2,
        0, 3, 7, 7, 4, 0,
        1, 2, 6, 6, 5, 1 
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.add_buffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned short));

    Shader shader("shader/solid_color.vs", "shader/solid_color.fs");

    Model cube(va, ib, shader);

    cube.get_shader().bind();
    cube.get_shader().set_uniform("u_Color", COLOR_RED);

    Renderer renderer;
    renderer.set_clear_color(COLOR_DARK);

    float angle = 0.0f;

    Surface surface(-1, -1, -1, 1, 1);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        update(window, &camera);

        renderer.clear();
        glm::mat4 view = camera.get_view_matrix();
        glm::mat4 projection = camera.get_projection_matrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(size / 2, size / 2, size / 2));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-size / 2, -size / 2, -size / 2));

        cube.get_shader().bind();
        cube.get_shader().set_uniform("model", model);
        cube.get_shader().set_uniform("view", view);
        cube.get_shader().set_uniform("projection", projection);

        surface.draw(&camera);
        renderer.draw(cube);

        angle += 0.01f;

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}