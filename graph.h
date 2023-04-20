#ifndef JAK_DOJADE_GRAPH_H
#define JAK_DOJADE_GRAPH_H

#include <utility>

#include "my-stl/stl_lib/vector.hxx"
#include "my-stl/stl_lib/pair.hxx"
#include "my-stl/stl_lib/vstring.h"
#include "my-stl/stl_lib/LinkedList.hxx"

using my_stl::vector;
using my_stl::pair;
using my_stl::vstring;
using my_stl::LinkedList;

class vertex;

class edge {
public:

    int length = 0;
    vertex *destination = nullptr;
    vertex *source = nullptr;

    edge(vertex *source, vertex *destination, int length) : source(source), destination(destination),
                                                            length(length) {}

    edge() = default;
};

class vertex {

public:
    vstring name;
    LinkedList<edge> edges;

    vertex() = default;

    explicit vertex(vstring &&name) : name(std::move(name)) {}

    void addEdge(edge &newEdge);

    void printEdges() const;

};

class graph {

    vector<vertex> vertices;

public:
    void addVertex(vstring name);

    void addEdge(const vstring &source, const vstring &destination, int length);

    void printGraph();

};


#endif //JAK_DOJADE_GRAPH_H
