#ifndef GRAPH_ANIMATOR_HPP_
#define GRAPH_ANIMATOR_HPP_

#include <boost/date_time/gregorian/gregorian.hpp>

#include "graph.hpp"
#include "graph_event_queue.hpp"

class GraphAnimator
{
public:
    void update(Graph& graph, GraphEventQueue& graph_event_queue, boost::gregorian::date date);
};

#endif
