#include "opengl_debug.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void GLAPIENTRY opengl_callback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam
) {
    std::cout << "---------------------------OPENGL CALLBACK---------------------------\n"
                 "TYPE: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "ERROR, ";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "DEPRECATED_BEHAVIOR, ";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "UNDEFINED_BEHAVIOR, ";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "PORTABILITY, ";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "PERFORMANCE, ";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "OTHER, ";
        break;
    }

    std::cout << "ID: " << id << ", ";
    std::cout << "SEVERITY: ";
    switch (severity){
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION	:
        std::cout << "NOTIFICATION";
    }
    std::cout << std::endl;
    std::cout << "MESSAGE:\n";
    if(severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        std::cout << "\033[36m";
    else 
        std::cout << "\033[31m";
    std::cout << message << "\033[0m" << std::endl; 
    std::cout << "---------------------------------------------------------------------\n" << std::endl;
}

void enable_opengl_callbacks(){
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(opengl_callback, NULL);
}