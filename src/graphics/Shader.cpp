#include "graphics/Shader.h"
#include "file.h"
#include <GL/glew.h>
#include <stdint.h>
#include "glm/glm.hpp"

static unsigned int compile_shader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile the " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader) : vs_path(vertex_shader), fs_path(fragment_shader), renderer_id(0) {
    unsigned int program = glCreateProgram();

    std::string vertex_shader_source = readfile(vertex_shader);
    std::string fragment_shader_source = readfile(fragment_shader);
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    this->renderer_id = program;
}

Shader::~Shader(){
    glDeleteProgram(renderer_id);
    std::cout << "SHADER DELETED" << std::endl;
}

void Shader::bind() const {
    glUseProgram(renderer_id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

int Shader::get_uniform_location(const char* name) {
    if(uniform_location_cache.find(name) != uniform_location_cache.end())
        return uniform_location_cache[name];
    int location = glGetUniformLocation(renderer_id, name);
    if(location != -1)
        uniform_location_cache[name] = location;
    else
        std::cout << "WARNING! COULD NOT FIND LOCATION OF '" << name << "'" << std::endl;
    return location;
}

void Shader::set_uniform(const char* name, Vec4f value){
    int location = get_uniform_location(name);
    if(location != -1)
        glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::set_uniform(const char* name, float x, float y, float z, float w) {
    int location = get_uniform_location(name);
    if(location != -1)
        glUniform4f(location, x, y, z, w);
}

void Shader::set_uniform(const char* name, int value){
    int location = get_uniform_location(name);
    if(location != -1)
        glUniform1i(location, value);
}

void Shader::set_uniform(const char* name, const glm::mat4& value) {
    int location = get_uniform_location(name);
    if(location != -1)
        glUniformMatrix4fv(location, 1, false, &value[0][0]);
}