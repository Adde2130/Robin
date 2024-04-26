#include "graphics/Shader.h"
#include <GL/glew.h>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "file.h"
#include "glm/glm.hpp"
#include "ResourceManager.h"

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

void Shader::read_shader_data(const std::string& data) {
    std::istringstream iss(data);
    std::string line;
    
    bool is_3d = false;
    bool uses_camera = false;
    bool using_ortho = false;
    std::vector<int> param_sizes;

    // Read each line from the file
    while (std::getline(iss, line)) {
        std::istringstream iss(line);
        std::string key;

        // Get the first word from the line (assuming it's the key)
        if (iss >> key) {
            if (key == "3d") {
                is_3d = true;
            } else if (key == "uses_camera") {
                std::string value;
                if (iss >> value && value == "true") {
                    uses_camera = true;
                }
            } else if (key == "param_sizes") {
                int num;
                while (iss >> num) {
                    param_sizes.push_back(num);
                }
            } else if (key == "mode") {
                std::string value;
                if(iss >> value && (value == "pixels" || value == "pixel"))
                    using_ortho = true;
            }
        }
    }

    this->is_3d = is_3d;
    this->uses_camera = uses_camera;
    this->using_ortho = using_ortho;

    this->total_vertex_array_size = 2 + is_3d;

    int* arr = new int[param_sizes.size()];
    for(size_t i = 0; i < param_sizes.size(); i++) {
        arr[i] = param_sizes[i];
        this->total_vertex_array_size += param_sizes[i];
    }

    this->additional_param_sizes = arr;

    std::cout << "Shader data - Is 3d: " << this->is_3D() << ", using camera: " << this->use_camera() << ", vertex array size: " << this->total_vertex_array_size << ", asd: " << this->additional_param_sizes << std::endl;
}

Shader::Shader(const std::string& shader) 
: shader_name(shader), additional_param_sizes(nullptr), renderer_id(0) {
    unsigned int program = glCreateProgram();

    std::string data, vs_s, fs_s;
    data = readfile("shader/" + shader + ".data");
    vs_s = readfile("shader/" + shader + ".vs");
    fs_s = readfile("shader/" + shader + ".fs");

    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vs_s);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fs_s);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    this->renderer_id = program;

    LoadedShaders.emplace(shader, this);
    this->read_shader_data(data);
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