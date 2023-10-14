#pragma once
#include <iostream>
#include <unordered_map>
#include "util/math.h"
#include "glm/glm.hpp"

class Shader {
public:
    Shader(const std::string& vertex_shader,  const std::string& fragmet_shader);
    ~Shader();
    void bind() const;
    void unbind() const;

    void set_uniform(const char* name, const float x, const float y, const float z, const float w);
    void set_uniform(const char* name, const Vec4f value);
    void set_uniform(const char* name, const int value);
    void set_uniform(const char* name, const glm::mat4& value);
private:
    const std::string vs_path;
    const std::string fs_path;
    unsigned int renderer_id;
    std::unordered_map<const char*, int> uniform_location_cache;
    int get_uniform_location(const char* name);
};