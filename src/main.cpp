#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "graph.hpp"
#include "graph_animator.hpp"
#include "graph_event_queue.hpp"
#include "graph_renderer.hpp"

int
main(int argc, char *argv[])
{
    std::string vertices_file_path;
    std::string edges_file_path;
    std::string start_date;
    std::string end_date;

    boost::program_options::options_description options_description;
    options_description.add_options()
        ("vertices_file_path", boost::program_options::value<std::string>(&vertices_file_path)->required(), "vertices_file_path")
        ("edges_file_path", boost::program_options::value<std::string>(&edges_file_path)->required(), "edges_file_path")
        ("start_date", boost::program_options::value<std::string>(&start_date)->required(), "start_date (YYYY-MM-DD)")
        ("end_date", boost::program_options::value<std::string>(&end_date)->required(), "end_date (YYYY-MM-DD)");
    boost::program_options::variables_map variables_map;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options_description), variables_map);
    boost::program_options::notify(variables_map);

    Graph graph;
    GraphAnimator graph_animator;
    GraphEventQueue graph_event_queue(vertices_file_path, edges_file_path);
    GraphRenderer graph_renderer;

    for (
        boost::gregorian::day_iterator day_iterator(boost::gregorian::from_simple_string(start_date), 1);
        *day_iterator < boost::gregorian::from_simple_string(end_date);
        ++day_iterator)
    {
        boost::gregorian::date date = *day_iterator;

        graph_animator.update(graph, graph_event_queue, date);
        graph_renderer.render(graph);

        std::cout << "Date: " << date;
        std::cout << ", Vertices: " << boost::num_vertices(graph);
        std::cout << ", Edges: " << boost::num_edges(graph) << std::endl;
    }

    return EXIT_SUCCESS;
}
