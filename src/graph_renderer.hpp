#ifndef GRAPH_RENDERER_HPP_
#define GRAPH_RENDERER_HPP_

#include <GLFW/glfw3.h>

#include "graph.hpp"

class GraphRenderer
{
public:
    GraphRenderer();
    ~GraphRenderer();
    void render(Graph graph);

private:
    GLFWwindow* window_;
    void initialize_glfw();
    void deinitialize_glfw();
};

#endif
