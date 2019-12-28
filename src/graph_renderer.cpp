#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "graph_renderer.hpp"

const float EYE_Z = 500.0f;
const int HEIGHT = 720;
const int WIDTH = 1080;
const float Z_FAR = EYE_Z + 1.0f;

const float RATIO = (float)WIDTH / (float)HEIGHT;

GraphRenderer::GraphRenderer()
{
    initialize_glfw();
}

GraphRenderer::~GraphRenderer()
{
    deinitialize_glfw();
}

void
GraphRenderer::render(Graph graph)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, RATIO, 0.1f, Z_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, EYE_Z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render vertices.
    for (
        std::pair<VertexIterator, VertexIterator> vertex_iterator_pair = boost::vertices(graph);
        vertex_iterator_pair.first != vertex_iterator_pair.second;
        ++vertex_iterator_pair.first
    ) {
        Vertex vertex = graph.graph()[*vertex_iterator_pair.first];

        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(vertex.position[0], vertex.position[1]);
        glEnd();
    }

    // Render edges.
    EdgeIterator edge_iterator, edge_iterator_end;
    for (
        boost::tie(edge_iterator, edge_iterator_end) = boost::edges(graph);
        edge_iterator != edge_iterator_end;
        ++edge_iterator
    ) {
        Vertex vertex_source = graph.graph()[source(*edge_iterator, graph)];
        Vertex vertex_target = graph.graph()[target(*edge_iterator, graph)];

        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(vertex_source.position[0], vertex_source.position[1]);
        glVertex2f(vertex_target.position[0], vertex_target.position[1]);
        glEnd();
    }

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-100.0f, -100.0f);
    glVertex2f(100.0f, -100.0f);
    glVertex2f(100.0f, 100.0f);
    glVertex2f(-100.0f, 100.0f);
    glEnd();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void
GraphRenderer::initialize_glfw()
{
    glfwInit();
    window_ = glfwCreateWindow(WIDTH, HEIGHT, "", NULL, NULL);
    glfwMakeContextCurrent(window_);
    glViewport(0, 0, WIDTH, HEIGHT);
}

void
GraphRenderer::deinitialize_glfw()
{
    glfwTerminate();
}
