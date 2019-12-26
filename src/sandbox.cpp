#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/topology.hpp>
#include <stdio.h>

struct Vertex {
    boost::rectangle_topology<>::point_type position;
};
struct Edge {
};
typedef boost::labeled_graph<boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, Vertex, Edge>, std::string> Graph;

int main()
{
    Graph g;

    boost::add_vertex("1", g);
    boost::add_vertex("2", g);
    boost::add_edge_by_label("1", "2", g);
    boost::add_edge_by_label("2", "1", g);

    printf("%lu\n", boost::num_vertices(g));
    printf("%lu\n", boost::num_edges(g));

    printf("%f, %f", g["1"].position[0], g["1"].position[1]);

    boost::rectangle_topology<> t = boost::rectangle_topology<>(0, 0, 10, 10);
    boost::fruchterman_reingold_force_directed_layout(g, boost::get(&Vertex::position, g), t);

    printf("%f, %f", g["1"].position[0], g["1"].position[1]);
}
