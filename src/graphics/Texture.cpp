#include "Texture.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* path) : renderer_id(0), filepath(path), pixel_buffer(nullptr), width(0), height(0), bpp(0){
    stbi_set_flip_vertically_on_load(1);
    pixel_buffer = stbi_load(path, &width, &height, &bpp, 4);
    
    glGenTextures(1, &renderer_id);
    glBindTexture(GL_TEXTURE_2D, renderer_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(pixel_buffer)
        stbi_image_free(pixel_buffer);
    else
        std::cout << "FAILED TO LOAD IMAGE '" << path << "'" << std::endl;
}

Texture::~Texture() {
    glDeleteTextures(1, &renderer_id);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, renderer_id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}