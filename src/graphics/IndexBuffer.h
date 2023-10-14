#pragma once

#include <GL/glew.h>

class IndexBuffer {
private:
    unsigned int renderer_id;
    unsigned short count;
public:
    IndexBuffer(const unsigned short* data, unsigned short count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned short get_count() const { return count; }
};