#include "graph.h"

void vertex::addEdge(edge &newEdge) {

    edges.push_back(newEdge);
}

//void vertex::printEdges() const {
//    for (int i = 0; i < edges.size(); i++) {
////        std::cout << edges[i].destination->name << " " << edges[i].length << " , ";
//    }
//}

void graph::addVertex(vstring name) {

    if (!hashMap.insertIfNotExists(name, (int) vertices.size())) return;

    vertex newVertex(name);

    vertices.push_back(newVertex);
}

void graph::addEdge(const vstring &source, const vstring &destination, int length) {

    edge newEdge;
    newEdge.length = length;
    newEdge.sourceIndex = hashMap.get(source);
    newEdge.destinationIndex = hashMap.get(destination);

    vertices[newEdge.sourceIndex].addEdge(newEdge);
}

//void graph::printGraph() {
//
//    for (int i = 0; i < vertices.size(); i++) {
//        std::cout << vertices[i].name << " | ";
//        vertices[i].printEdges();
//        std::cout << "\n";
//    }
//}

void graph::findShortestPath(const vstring &startingCity, const vstring &destinationCity, int option) {

    int startingCityIndex = hashMap.get(startingCity);
    int destinationCityIndex = hashMap.get(destinationCity);

    //index of vector is index of vertex, value int is distance to vertex
    vector<int> distanceToVertex(vertices.size());

    //index of vector is index of vertex, value int is previous vertex
    vector<int> previousVertex(vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
        distanceToVertex.push_back(INT_MAX);
        previousVertex.push_back(-1);
    }

    distanceToVertex[startingCityIndex] = 0;

    //first int is index of vertex, second int is distance to vertex
    priorityQueue<pair<int, int>, bool (*)(const pair<int, int> &, const pair<int, int> &)> pq(
            [](const pair<int, int> &a, const pair<int, int> &b) {
                return a.second < b.second;
            });

    pq.push(pair<int, int>(startingCityIndex, 0));

    int approxNumberOfEdges = 0;

    while (!pq.empty()) {

        approxNumberOfEdges++;
        pair<int, int> currentVertex = pq.top();
        pq.pop();

        if (currentVertex.first == destinationCityIndex) break;

        for (int i = 0; i < vertices[currentVertex.first].edges.size(); i++) {

            int newDistance = distanceToVertex[currentVertex.first] + vertices[currentVertex.first].edges[i].length;
            int indexDestinationEdge = vertices[currentVertex.first].edges[i].destinationIndex;

            if (newDistance < distanceToVertex[indexDestinationEdge]) {

                distanceToVertex[indexDestinationEdge] = newDistance;
                previousVertex[indexDestinationEdge] = currentVertex.first;

                pq.push(pair<int, int>(indexDestinationEdge, newDistance));
            }
        }

    }

    if (option == 0) {
        std::cout << distanceToVertex[destinationCityIndex] << "\n";
        return;
    }

    std::cout << distanceToVertex[destinationCityIndex] << " ";
    if (distanceToVertex[destinationCityIndex] == 0) {
        std::cout << "\n";
        return;
    }


    vector<int> originalPath(approxNumberOfEdges);
    //do backtrack from destination to starting city
    int currentTraversalIndex = previousVertex[destinationCityIndex];
    while (currentTraversalIndex != startingCityIndex) {
        originalPath.push_back(currentTraversalIndex);
        currentTraversalIndex = previousVertex[currentTraversalIndex];
    }

//    return;
    for (int i = (int) originalPath.size() - 1; i >= 0; i--) {
        std::cout << vertices[originalPath[i]].name << " ";
    }

    std::cout << "\n";
}
