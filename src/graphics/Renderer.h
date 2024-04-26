#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>
#include "ResourceManager.h"
#include "Shader.h"
#include "RenderComponent.h"
#include "util/math.h"
#include "Camera.h"
#include "Texture.h"

#define ASSERT(x) if(!x) __debugbreak();

struct RenderBatch {
    RenderBatch(RenderComponent& c_render);
    ~RenderBatch();
    Shader* shader;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    std::vector<float> vertices;
    std::vector<int> indices;

    bool new_data = false;

    void update();
};

class Renderer {
public:
    Renderer(int window_width, int window_height);

    void clear();
    void set_clear_color(const Vec4f& color);
    void draw(Camera* camera);
    void set_window_dimensions(int window_width, int window_height);
    
    void push_render_component(RenderComponent& c_render);
private:
    int window_width;
    int window_height;

    std::map<std::string, RenderBatch*> render_batches;
};

