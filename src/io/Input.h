#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "ComponentHandler.h"

void set_input_window(std::shared_ptr<Window> p_window);
void subscribe_mouse_event(UpdateComponent<double, double, double, double>& c_update);
void subscribe_keyboard_event(UpdateComponent<int, int, int>& c_update);

void keyboard_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow*, double, double);

bool key_pressed(const char key);
bool key_released(const char key);

double mouse_x();
double mouse_y();
double mouse_dx();
double mouse_dy();

void update();