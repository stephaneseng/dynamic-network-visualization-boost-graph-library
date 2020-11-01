#ifndef GRAPH_RENDERER_HPP_
#define GRAPH_RENDERER_HPP_

#include <GLFW/glfw3.h>

#include "graph.hpp"

class GraphRenderer
{
public:
    GraphRenderer(float eye_z, float topology_scaling);
    ~GraphRenderer();
    void render(Graph graph);

private:
    GLFWwindow *window_;
    float eye_z_;
    float topology_scaling_;
    void initialize_glfw();
    void deinitialize_glfw();
};

#endif
