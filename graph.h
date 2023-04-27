#ifndef JAK_DOJADE_GRAPH_H
#define JAK_DOJADE_GRAPH_H

#include "vector.hxx"
#include "pair.hxx"
#include "vstring.h"
#include "linkedList.hxx"
#include "hashMap.h"
#include "priorityQueue.hxx"

using my_stl::vector;
using my_stl::pair;
using my_stl::vstring;
using my_stl::linkedList;

class vertex;

class edge {
public:

    int length = 0;
    int destinationIndex = -1;
    int sourceIndex = -1;

    edge(int sourceIndex, int destinationIndex, int length) : sourceIndex(sourceIndex),
                                                              destinationIndex(destinationIndex),
                                                              length(length) {}

    edge() = default;
};

class vertex {

public:
    vstring name;
    vector<edge> edges;

    vertex() = default;

    explicit vertex(vstring name) : name(std::move(name)) {}

    vertex(vertex &&other) noexcept: name(std::move(other.name)), edges(std::move(other.edges)) {}

    vertex &operator=(const vertex &other) {
        if (this != &other) {
            name = other.name;
            edges = other.edges;
        }
        return *this;
    }

    void addEdge(edge &newEdge);

};

class graph {

public:
    vector<vertex> vertices;

    hashMap hashMap;

    void addVertex(vstring name);

    void addEdge(const vstring &source, const vstring &destination, int length);

    void findShortestPath(const vstring &startingCity, const vstring &destinationCity, int option);

};


#endif //JAK_DOJADE_GRAPH_H
