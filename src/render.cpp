#define GLFW_INCLUDE_GLU

#define WIDTH 1080.0f
#define HEIGHT 720.0f
#define RATIO WIDTH / HEIGHT

#include <cstdlib>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

typedef struct {
    float x;
    float y;
} Node;

typedef struct {
    Node *source;
    Node *target;
} Edge;

class Graph {
    public:
        std::vector<Node *> nodes;
        std::vector<Edge *> edges;
};

Graph *generate()
{
    Graph *graph;
    Node *node;

    graph = new Graph();

    for (int i = 0; i < 50000; i++) {
        node = new Node();
        node->x = -100.0f + static_cast<float> (rand()) /(static_cast <float>(RAND_MAX/(100.0f+100.0f)));
        node->y = -100.0f + static_cast<float> (rand()) /(static_cast <float>(RAND_MAX/(100.0f+100.0f)));

        graph->nodes.push_back(node);
    }

    return graph;
}

void draw(Graph *graph_)
{
    Graph *graph = generate();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, RATIO, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < graph->nodes.size(); i++) {
        Node *node = graph->nodes.at(i);

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(node->x, node->y);
        glEnd();
    }

    delete graph;
}

int main(void)
{
    Graph *graph;
    GLFWwindow *window;
    double time;

    graph = generate();

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, "", NULL, NULL);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        time = glfwGetTime();

        draw(graph);
        while (glfwGetTime() < time + 1.0/60.0) {
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
