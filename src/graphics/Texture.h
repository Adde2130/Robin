#pragma once

#include "graphics/Renderer.h"
#include <string.h>

GLuint LoadTexture(const std::string& filename);

class Texture {
private:
    unsigned int renderer_id;
    const char* filepath;
    unsigned char* pixel_buffer;
    int width;
    int height;
    int bpp;
public:
    Texture(const char* path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int get_width() const { return width; }
    inline int get_height() const { return height; }
};