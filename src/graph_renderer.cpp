#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "graph_renderer.hpp"

const float WINDOW_HEIGHT = 720.0f;
const float WINDOW_WIDTH = 1280.0f;
const float WINDOW_RATIO = WINDOW_WIDTH / WINDOW_HEIGHT;

GraphRenderer::GraphRenderer(float eye_z, float topology_scaling) : eye_z_(eye_z), topology_scaling_(topology_scaling)
{
    initialize_glfw();
}

GraphRenderer::~GraphRenderer()
{
    deinitialize_glfw();
}

void GraphRenderer::render(Graph graph)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, WINDOW_RATIO, 0.1f, eye_z_ + 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, eye_z_, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render vertices.
    VertexIterator vertex_iterator, vertex_iterator_end;
    for (
        boost::tie(vertex_iterator, vertex_iterator_end) = boost::vertices(graph);
        vertex_iterator != vertex_iterator_end;
        ++vertex_iterator)
    {
        Vertex *vertex = &graph.graph()[*vertex_iterator];

        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(vertex->position[0], vertex->position[1]);
        glEnd();
    }

    // Render edges.
    EdgeIterator edge_iterator, edge_iterator_end;
    for (
        boost::tie(edge_iterator, edge_iterator_end) = boost::edges(graph);
        edge_iterator != edge_iterator_end;
        ++edge_iterator)
    {
        Vertex *vertex_source = &graph.graph()[source(*edge_iterator, graph)];
        Vertex *vertex_target = &graph.graph()[target(*edge_iterator, graph)];

        glBegin(GL_LINES);
        glColor4f(0.0f, 0.0f, 0.0f, 0.2f);
        glVertex2f(vertex_source->position[0], vertex_source->position[1]);
        glVertex2f(vertex_target->position[0], vertex_target->position[1]);
        glEnd();
    }

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void GraphRenderer::initialize_glfw()
{
    glfwInit();
    window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "", NULL, NULL);
    glfwMakeContextCurrent(window_);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GraphRenderer::deinitialize_glfw()
{
    glfwTerminate();
}
