#ifndef GRAPH_ANIMATOR_HPP_
#define GRAPH_ANIMATOR_HPP_

#include <boost/date_time/gregorian/gregorian.hpp>

#include "graph.hpp"
#include "graph_event_queue.hpp"

class GraphAnimator
{
public:
    void add_vertices_edges(Graph &graph, GraphEventQueue &graph_event_queue, boost::gregorian::date date, boost::circle_topology<> topology);
    void evaluate_target_layout(Graph &graph, boost::circle_topology<> topology);
    void update_layout(Graph &graph, boost::circle_topology<> topology, double step);
};

// Weaker repulsive force than the default one.
// See https://www.boost.org/doc/libs/1_65_0/boost/graph/fruchterman_reingold.hpp.
struct custom_repulsive_force
{
    template<typename Graph, typename T>
    T
    operator()(typename boost::graph_traits<Graph>::vertex_descriptor,
               typename boost::graph_traits<Graph>::vertex_descriptor,
               T k,
               T d,
               const Graph&) const
    {
        return k / d;
    }
};

#endif
