#include <boost/tokenizer.hpp>
#include <fstream>

#include "graph_event_queue.hpp"

typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;

const char *CSV_SEPARATORS = ",";

GraphEventQueue::GraphEventQueue(std::string vertices_file_path, std::string edges_file_path)
{
    load_vertices(vertices_file_path);
    load_edges(edges_file_path);
}

std::vector<Vertex> GraphEventQueue::pop_vertices(boost::gregorian::date date)
{
    std::vector<Vertex> vertices;

    while ((!vertices_.empty()) && (vertices_.front().date <= date))
    {
        vertices.push_back(vertices_.front());
        vertices_.pop();
    }

    return vertices;
}

std::vector<Edge> GraphEventQueue::pop_edges(boost::gregorian::date date)
{
    std::vector<Edge> edges;

    while ((!edges_.empty()) && (edges_.front().date <= date))
    {
        edges.push_back(edges_.front());
        edges_.pop();
    }

    return edges;
}

void GraphEventQueue::load_vertices(std::string file_path)
{
    std::ifstream file(file_path);
    std::string line;

    // Ignore the first line.
    std::getline(file, line);

    while (std::getline(file, line))
    {
        Tokenizer tokenizer(line, boost::char_separator<char>(CSV_SEPARATORS));
        vertices_.push(Vertex{boost::gregorian::from_simple_string(*tokenizer.begin()), *(++tokenizer.begin())});
    }
}

void GraphEventQueue::load_edges(std::string file_path)
{
    std::ifstream file(file_path);
    std::string line;

    // Ignore the first line.
    std::getline(file, line);

    while (std::getline(file, line))
    {
        Tokenizer tokenizer(line, boost::char_separator<char>(CSV_SEPARATORS));
        edges_.push(Edge{boost::gregorian::from_simple_string(*tokenizer.begin()), *(++tokenizer.begin()), *(++++tokenizer.begin())});
    }
}
