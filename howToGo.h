#ifndef JAK_DOJADE_HOWTOGO_H
#define JAK_DOJADE_HOWTOGO_H

#include "graph.h"

class howToGo {
    int boardWidth;
    int boardHeight;
    vector<vector<char>> board;
    bool *visitedTiles;
    graph graph;

    static bool isLetter(char character);

    void readBoard();

    void readAirports();

    void findPaths();

    void parseBoard();

    void traverseBoard();

    void goPath(const pair<int, int> &startingCoordinates, const vstring &startingCity);

    vstring &getCity(const pair<int, int> &coordinates);

    void addCityVertex(int currentDistance, const vstring &startingCity, const vstring &destinationCity);

    struct compare {
        bool operator()(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
            return a.second < b.second;
        }
    };

    void handleGraphTile(const pair<int, int> &currentCoordinates, int currentDistance, const vstring &startingCity,
                         priorityQueue<pair<pair<int, int>, int>, compare> &path);


    void printBoard();

public:
    void start();

};


#endif //JAK_DOJADE_HOWTOGO_H
