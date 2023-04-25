#ifndef JAK_DOJADE_HOWTOGO_H
#define JAK_DOJADE_HOWTOGO_H

#include "graph.h"

struct tile {
    int first;
    int second;
    int distance;

    tile(int first, int second, int distance) : first(first), second(second), distance(distance) {}

    tile() = default;
};

struct compare {
    bool operator()(const tile &a, const tile &b) {
        return a.distance < b.distance;
    }
};


class howToGo {
    int boardWidth;
    int boardHeight;
    char *board;
    bool *visitedTiles;
    graph graph;

    static bool isLetter(char character);

    void readBoard();

    void readAirports();

    void findPaths();

    void traverseBoard();

    void goPath(const pair<int, int> &startingCoordinates, const vstring &startingCity);

    bool checkIfAnyPathExists(const pair<int, int> &startingCoordinates);

    vstring *getCity(const pair<int, int> &coordinates);

    void addCityVertex(int currentDistance, const vstring &startingCity, const vstring &destinationCity);


    void handleGraphTile(const pair<int, int> &currentCoordinates, int currentDistance, const vstring &startingCity,
                         priorityQueue<tile, compare> &path);


    void printBoard();

public:
    void start();

};


#endif //JAK_DOJADE_HOWTOGO_H
