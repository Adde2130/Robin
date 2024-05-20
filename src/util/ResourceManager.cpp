#include "ResourceManager.h"

std::unordered_map<std::string, std::shared_ptr<Shader>> LoadedShaders;
std::unordered_map<std::string, unsigned int> LoadedTextures;

std::shared_ptr<Shader> LoadShader(const std::string& s_shader) {
    std::cout << "Loading shader '" << s_shader << "'" << std::endl;
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(s_shader);
    LoadedShaders.emplace(s_shader, shader);
    return shader;
}

void InitResources() {

}