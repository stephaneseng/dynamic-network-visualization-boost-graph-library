#ifndef GRAPH_ANIMATOR_HPP_
#define GRAPH_ANIMATOR_HPP_

#include <boost/date_time/gregorian/gregorian.hpp>

#include "graph.hpp"
#include "graph_event_queue.hpp"

class GraphAnimator
{
public:
    void add_vertices_edges(Graph &graph, GraphEventQueue &graph_event_queue, boost::gregorian::date date, boost::rectangle_topology<> topology);
    void update_target_layout(Graph &graph, boost::rectangle_topology<> topology);
    void update_layout(Graph &graph, boost::rectangle_topology<> topology, double step);
};

#endif
