#pragma once

#include <unordered_map>
#include <iostream>
#include <string>

#include "Shader.h"

extern std::unordered_map<std::string, Shader*> LoadedShaders;

void AddLoadedShader(Shader* shader);
void InitResources();