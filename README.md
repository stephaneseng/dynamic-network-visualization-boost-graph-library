# Installation

## Requirements

* OpenGL 2
* libboost-date-time-dev
* libboost-graph-dev
* libboost-program-options-dev
* libglfw3
* libglfw3-dev

# Reference

## CSV time-series files

* The file MUST start with an header
* Entries MUST be sorted by time, by chronological order
* Lines MUST end with "\n" (UNIX line endings, not "\r\n")

# Vocabulary

## Graph

| Product | Vocabulary | References |
| ------- | ---------- | ---------- |
| Gephi | Nodes, Edges, <[2019-01-01, Infinity]> | https://gephi.org/gexf/format/index.html |
| Neo4j | Nodes, Relationships | https://neo4j.com/docs/getting-started/current/ |
| sigma.js | Nodes, Edges | https://github.com/jacomyal/sigma.js/wiki/Graph-API |
| KeyLines | Nodes, Links | https://cambridge-intelligence.com/keylines/ |
| GraphViz | Nodes, Edges | https://graphviz.gitlab.io/_pages/doc/info/lang.html |
| pm, ngraph.graph | Nodes, Links, Edges | https://github.com/anvaka/ngraph.graph |
| vis-network | Nodes, Edges | https://github.com/visjs/vis-network |
| Boost | Vertices, Edges | https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/Graph.html |
| GraphStream | Nodes, Edges | http://graphstream-project.org/doc/Advanced-Concepts/The-DGS-File-Format/ |
| graph-tool| Vertices, Nodes, Edges | https://graph-tool.skewed.de/static/doc/gt_format.html |

## Stream

| Product | Vocabulary | References |
| ------- | ---------- | ---------- |
| C++ | read | http://www.cplusplus.com/reference/istream/istream/read/ |
| Java | read | https://docs.oracle.com/javase/7/docs/api/java/io/InputStream.html |
| Python | read | https://docs.python.org/3/library/io.html#io.BufferedReader.read |
| .NET | read | https://docs.microsoft.com/en-us/dotnet/api/system.io.stream.read?view=netframework-4.8 |
| Cypher | consume | https://neo4j.com/docs/labs/neo4j-streams/3.5/procedures/#_streams_consume |
| RabbitMQ | get | https://www.rabbitmq.com/api-guide.html#getting |

# Literature

| Authors | Vocabulary | References |
| ------- | ---------- | ---------- |
| Jure Leskovec | Nodes, Edges | https://web.stanford.edu/class/cs224w/ |
| David Easley, Jon Kleinberg | Nodes, Edges | http://www.cs.cornell.edu/home/kleinber/networks-book/ |

# Boost Quick Start

* [Documentation](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/table_of_contents.html)
* [adjacency_list](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/adjacency_list.html), [Using adjacency_list](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/using_adjacency_list.html)
* [labeled_graph](https://stackoverflow.com/a/2248090)
