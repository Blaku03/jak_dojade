#ifndef JAK_DOJADE_GRAPH_H
#define JAK_DOJADE_GRAPH_H

#include <utility>

#include "my-stl/stl_lib/vector.hxx"
#include "my-stl/stl_lib/pair.hxx"
#include "my-stl/stl_lib/vstring.h"
#include "my-stl/stl_lib/linkedList.hxx"
#include "my-stl/stl_lib/hashMap.h"
#include "my-stl/stl_lib/priorityQueue.hxx"

using my_stl::vector;
using my_stl::pair;
using my_stl::vstring;
using my_stl::linkedList;

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
    static bool compareTwoEdges(const edge &firstEdge, const edge &secondEdge);

    vstring name;
    priorityQueue<edge, bool (*)(const edge &, const edge &)> edges;

    vertex() : edges(compareTwoEdges) {}

    explicit vertex(vstring name) : name(std::move(name)), edges(compareTwoEdges) {}

    void addEdge(edge &newEdge);

    void printEdges();

};

class graph {

public:
    vector<vertex> vertices;

    hashMap hashMap;

    void addVertex(const vstring &name);

    void addEdge(const vstring &source, const vstring &destination, int length);

    void findShortestPath(const vstring &startingCity, const vstring &destinationCity, int option);

    void printGraph();

};


#endif //JAK_DOJADE_GRAPH_H