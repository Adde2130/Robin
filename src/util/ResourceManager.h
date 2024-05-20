#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>

#include "Shader.h"

extern std::unordered_map<std::string, std::shared_ptr<Shader>> LoadedShaders;
extern std::unordered_map<std::string, unsigned int> LoadedTextures;

std::shared_ptr<Shader> LoadShader(const std::string& s_shader);
void InitResources();