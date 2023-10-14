#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type){
        switch (type) {
        case GL_FLOAT:          return 4;
        case GL_UNSIGNED_INT:   return 4;
        case GL_UNSIGNED_BYTE:  return 1;
        }
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
public:
    VertexBufferLayout() : stride(0) {}

    template<typename T>
    void push(unsigned int count);

    inline const std::vector<VertexBufferElement>& get_elements() const { return elements; };
    inline unsigned int get_stride() const { return stride; };
};

