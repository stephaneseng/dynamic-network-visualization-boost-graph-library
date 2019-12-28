#ifndef GRAPH_EVENT_QUEUE_HPP_
#define GRAPH_EVENT_QUEUE_HPP_

#include <boost/date_time/gregorian/gregorian.hpp>
#include <queue>
#include <string>
#include <vector>

#include "graph.hpp"

class GraphEventQueue
{
public:
    GraphEventQueue(std::string vertices_file_path, std::string edges_file_path);
    std::vector<Vertex> pop_vertices(boost::gregorian::date date);
    std::vector<Edge> pop_edges(boost::gregorian::date date);

private:
    std::queue<Vertex> vertices_;
    std::queue<Edge> edges_;
    void load_vertices(std::string file_path);
    void load_edges(std::string file_path);
};

#endif
