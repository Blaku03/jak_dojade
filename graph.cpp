#include "graph.h"

void vertex::addEdge(edge &newEdge) {

    edges.push(newEdge);
}

void vertex::printEdges() {
    edge tempEdge;
    while (!edges.empty()) {
        tempEdge = edges.top();
        std::cout << tempEdge.destination->name << " " << tempEdge.length << " , ";
        edges.pop();
    }
}

bool vertex::compareTwoEdges(const edge &firstEdge, const edge &secondEdge) {
    return firstEdge.length < secondEdge.length;
}

void graph::addVertex(const vstring &name) {

    vertex newVertex(name);

    vertices.push_back(newVertex);
    hashMap.insert(name, (int) vertices.size() - 1);
}

void graph::addEdge(const vstring &source, const vstring &destination, int length) {

    edge newEdge;
    newEdge.length = length;
    newEdge.source = &vertices[hashMap.get(source)];
    newEdge.destination = &vertices[hashMap.get(destination)];

    newEdge.source->addEdge(newEdge);
}

void graph::printGraph() {

    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i].name << " | ";
        vertices[i].printEdges();
        std::cout << "\n";
    }
}

void graph::findShortestPath(const vstring &startingCity, const vstring &destinationCity, int option) {

}
