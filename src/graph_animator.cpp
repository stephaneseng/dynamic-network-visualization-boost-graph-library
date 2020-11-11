#include <boost/graph/fruchterman_reingold.hpp>
#include <vector>

#include "graph_animator.hpp"

void GraphAnimator::add_vertices_edges(Graph &graph, GraphEventQueue &graph_event_queue, boost::gregorian::date date, boost::circle_topology<> topology)
{
    std::vector<Vertex> vertices = graph_event_queue.pop_vertices(date);
    std::vector<Edge> edges = graph_event_queue.pop_edges(date);

    // Add vertices.
    for (
        std::vector<Vertex>::iterator vertex_iterator = vertices.begin();
        vertex_iterator != vertices.end();
        ++vertex_iterator)
    {
        Vertex vertex = *vertex_iterator;
        vertex.position = topology.center();
        vertex.target_position = topology.center();

        boost::add_vertex(vertex.id, vertex, graph);
    }

    // Add edges.
    for (
        std::vector<Edge>::iterator edge_iterator = edges.begin();
        edge_iterator != edges.end();
        ++edge_iterator)
    {
        Edge edge = *edge_iterator;

        boost::add_edge_by_label(edge.source, edge.target, edge, graph);
    }
}

void GraphAnimator::evaluate_target_layout(Graph &graph, boost::circle_topology<> topology)
{
    boost::fruchterman_reingold_force_directed_layout(
        graph,
        boost::get(&Vertex::target_position, graph),
        topology,
        boost::repulsive_force(custom_repulsive_force()));
}

void GraphAnimator::update_layout(Graph &graph, boost::circle_topology<> topology, double step)
{
    VertexIterator vertex_iterator, vertex_iterator_end;
    for (
        boost::tie(vertex_iterator, vertex_iterator_end) = boost::vertices(graph);
        vertex_iterator != vertex_iterator_end;
        ++vertex_iterator)
    {
        Vertex *vertex = &graph.graph()[*vertex_iterator];
        vertex->position = topology.move_position_toward(vertex->position, step, vertex->target_position);
    }
}
