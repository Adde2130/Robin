#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>
#include "util/math.h"
#include "glm/glm.hpp"


class Shader {
public:
    Shader(const std::string& shader);
    ~Shader();
    void bind() const;
    void unbind() const;

    bool use_camera() const { return uses_camera; }
    bool is_3D() const { return is_3d; }
    bool use_ortho() const { return using_ortho; }

    int* param_sizes() const { return additional_param_sizes; }
    int  va_size() const { return total_vertex_array_size; }

    unsigned int r_id() const { return renderer_id; }

    void set_uniform(const char* name, const float x, const float y, const float z, const float w);
    void set_uniform(const char* name, const Vec4f value);
    void set_uniform(const char* name, const int value);
    void set_uniform(const char* name, const glm::mat4& value);
private:
    void read_shader_data(const std::string& data);
    const std::string shader_path;
    const std::string shader_name;

    bool uses_camera;
    bool is_3d;
    bool using_ortho;
    int  total_vertex_array_size;
    int* additional_param_sizes;


    unsigned int renderer_id;
    std::unordered_map<const char*, int> uniform_location_cache;
    int get_uniform_location(const char* name);
};