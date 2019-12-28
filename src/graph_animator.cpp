#include <boost/graph/fruchterman_reingold.hpp>
#include <vector>

#include "graph_animator.hpp"

void
GraphAnimator::update(Graph& graph, GraphEventQueue& graph_event_queue, boost::gregorian::date date)
{
    std::vector<Vertex> vertices = graph_event_queue.pop_vertices(date);
    std::vector<Edge> edges = graph_event_queue.pop_edges(date);

    // Update vertices.
    for (
        std::vector<Vertex>::iterator vertex_iterator = vertices.begin();
        vertex_iterator != vertices.end();
        ++vertex_iterator
    ) {
        Vertex vertex = *vertex_iterator;

        boost::add_vertex(vertex.id, vertex, graph);
    }

    // Update edges.
    for (
        std::vector<Edge>::iterator edge_iterator = edges.begin();
        edge_iterator != edges.end();
        ++edge_iterator
    ) {
        Edge edge = *edge_iterator;

        boost::add_edge_by_label(edge.source, edge.target, edge, graph);
    }

    // Update layout.
    boost::rectangle_topology<> t = boost::rectangle_topology<>(-200, -200, 200, 200);
    boost::fruchterman_reingold_force_directed_layout(graph, boost::get(&Vertex::position, graph), t);
}
