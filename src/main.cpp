#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "graph.hpp"
#include "graph_animator.hpp"
#include "graph_event_queue.hpp"
#include "graph_renderer.hpp"

const double ANIMATOR_STEPS_PER_MONTH = 60.0;
const float RENDERER_EYE_Z = 500.0f;
const double TOPOLOGY_SCALING = 100.0;

int main(int argc, char *argv[])
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
    GraphRenderer graph_renderer(RENDERER_EYE_Z, TOPOLOGY_SCALING);
    boost::rectangle_topology<> topology = boost::rectangle_topology<>(-TOPOLOGY_SCALING, -TOPOLOGY_SCALING, TOPOLOGY_SCALING, TOPOLOGY_SCALING);

    for (
        boost::gregorian::month_iterator month_iterator(boost::gregorian::from_simple_string(start_date), 1);
        *month_iterator < boost::gregorian::from_simple_string(end_date);
        ++month_iterator)
    {
        boost::gregorian::date date = *month_iterator;

        graph_animator.add_vertices_edges(graph, graph_event_queue, date, topology);
        graph_animator.evaluate_target_layout(graph, topology);

        std::cout
            << "Date: " << date
            << ", Vertices: " << boost::num_vertices(graph)
            << ", Edges: " << boost::num_edges(graph)
            << std::endl;

        for (int i = 0; i < ANIMATOR_STEPS_PER_MONTH; i++)
        {
            graph_animator.update_layout(graph, topology, 1 / ANIMATOR_STEPS_PER_MONTH);
            graph_renderer.render(graph);
        }
    }

    sleep(1);
    return EXIT_SUCCESS;
}
