#define GLFW_INCLUDE_GLU

#define WIDTH 1080.0f
#define HEIGHT 720.0f
#define RATIO WIDTH / HEIGHT

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/topology.hpp>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

struct Vertex {
    boost::rectangle_topology<>::point_type position;
};
struct Edge {
};

typedef boost::labeled_graph<boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, Vertex, Edge>, std::string> Graph;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

void
generateGraph(Graph& graph)
{
    for (int i = 1; i < 3; i++) {
        Vertex v;
        // v.position[0] = -100.0f + static_cast<float> (rand()) /(static_cast <float>(RAND_MAX/(100.0f+100.0f)));
        // v.position[1] = -100.0f + static_cast<float> (rand()) /(static_cast <float>(RAND_MAX/(100.0f+100.0f)));

        boost::add_vertex(std::to_string(i), v, graph);
    }

    boost::add_edge_by_label("1", "2", graph);
    boost::add_edge_by_label("2", "1", graph);
}

void
updateGraph(Graph& graph)
{
    boost::rectangle_topology<> t = boost::rectangle_topology<>(-100, -100, 100, 100);
    boost::random_graph_layout(graph, boost::get(&Vertex::position, graph), t);
    boost::fruchterman_reingold_force_directed_layout(graph, boost::get(&Vertex::position, graph), t);
}

void
renderGraph(Graph graph)
{
    std::pair<VertexIterator, VertexIterator> vertex_pair;
    EdgeIterator edge_iterator, edge_iterator_end;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, RATIO, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Vertices.
    for (vertex_pair = boost::vertices(graph); vertex_pair.first != vertex_pair.second; ++vertex_pair.first) {
        Vertex vertex = graph.graph()[*vertex_pair.first];

        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(vertex.position[0], vertex.position[1]);
        glEnd();
    }

    // Edges.
    for (boost::tie(edge_iterator, edge_iterator_end) = boost::edges(graph); edge_iterator != edge_iterator_end; ++edge_iterator) {
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
}

void
drawGraph(Graph graph)
{
    GLFWwindow* window;
    double time;

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, "", NULL, NULL);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        time = glfwGetTime();
        renderGraph(graph);

        while (glfwGetTime() < time + 1.0/60.0) {
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

int
main(void)
{
    Graph graph;

    generateGraph(graph);
    updateGraph(graph);
    drawGraph(graph);

    return EXIT_SUCCESS;
}
