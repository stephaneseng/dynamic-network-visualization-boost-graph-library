BUILDDIR := build
CXX := g++
CXXFLAGS := -O0 $(shell pkg-config --cflags gl glfw3 glu)
LDFLAGS := $(shell pkg-config --libs gl glfw3 glu) -lboost_date_time -lboost_program_options
SRCDIR := src

DEPS := $(SRCDIR)/graph.hpp $(SRCDIR)/graph_animator.hpp $(SRCDIR)/graph_event_queue.hpp $(SRCDIR)/graph_renderer.hpp
OBJECTS := $(BUILDDIR)/graph_animator.o $(BUILDDIR)/graph_event_queue.o $(BUILDDIR)/graph_renderer.o $(BUILDDIR)/main.o
TARGET := $(BUILDDIR)/main

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(BUILDDIR)/*

run:
	./build/main --vertices_file_path doc/vertices.csv --edges_file_path doc/edges.csv --start_date 2010-11-01 --end_date 2011-04-01
