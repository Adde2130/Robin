#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "EventHandler.h"

void set_input_window(std::shared_ptr<Window> p_window);
void set_event_handler(std::shared_ptr<EventHandler> ph_event);

void keyboard_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow*, double, double);

bool key_pressed(const char key);
bool key_released(const char key);

double mouse_x();
double mouse_y();
double mouse_dx();
double mouse_dy();

void update();