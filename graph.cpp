#include "graph.h"

void vertex::addEdge(edge &newEdge) {

    edges.push_back(newEdge);
}

void vertex::printEdges() const {

    for (int i = 0; i < edges.number_of_nodes; i++) {
        std::cout << edges[i]->destination->name << " " << edges[i]->length << " , ";
    }
}

void graph::addVertex(const vstring &name) {

    vertex newVertex(name);

    vertices.push_back(newVertex);
}

void graph::addEdge(const vstring &source, const vstring &destination, int length) {

    edge newEdge;
    newEdge.length = length;

    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == source) {
            newEdge.source = &vertices[i];
        }
        if (vertices[i].name == destination) {
            newEdge.destination = &vertices[i];
        }
    }

    newEdge.source->addEdge(newEdge);
}

void graph::printGraph() {

    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i].name << " | ";
        vertices[i].printEdges();
        std::cout << "\n";
    }
}
