#ifndef JAK_DOJADE_HOWTOGO_H
#define JAK_DOJADE_HOWTOGO_H

#include "graph.h"

class howToGo {
    int boardWidth;
    int boardHeight;
    char *board;
    bool *visitedTiles;
    graph graph;
    vstring foundCityBegin;
    vstring foundCityEnd;
    vector<pair<int, int>> positionsOfStars;
    int anyRoadLength = 0;

    static bool isLetter(char character);

    void readBoard();

    void readAirports();

    void findPaths();

    void traverseBoard();

    bool checkIfAnyPathExists(const pair<int, int> &startingCoordinates);

    void goPath(const pair<int, int> &startingCoordinates);

    void getCity(const pair<int, int> &coordinates, vstring &city);

    void addCityVertex(int currentDistance);

    struct compare {
        bool operator()(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
            return a.second < b.second;
        }
    };

    void handleGraphTile(const pair<int, int> &currentCoordinates, int currentDistance,
                         priorityQueue<pair<pair<int, int>, int>, compare> &path);


    void printBoard();

public:
    void start();

};


#endif //JAK_DOJADE_HOWTOGO_H
