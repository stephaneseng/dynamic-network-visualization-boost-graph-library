#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/topology.hpp>
#include <string>

struct Vertex
{
    boost::gregorian::date date;
    std::string id;
    boost::rectangle_topology<>::point_type position;
    boost::rectangle_topology<>::point_type target_position;
};

struct Edge
{
    boost::gregorian::date date;
    std::string source;
    std::string target;
};

typedef boost::labeled_graph<boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, Vertex, Edge>, std::string> Graph;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

#endif
