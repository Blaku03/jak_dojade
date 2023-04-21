#ifndef JAK_DOJADE_HOWTOGO_H
#define JAK_DOJADE_HOWTOGO_H

#include "graph.h"

class howToGo {
    int boardWidth;
    int boardHeight;
    vector<vector<char>> board;
    vector<pair<vstring, pair<int, int>>> cities;
    graph graph;

    static bool isLetter(char character);

    bool checkForStar(pair<int, int> &startingCoordinates);

    void readBoard();

    void readAirports();

    void parseBoard();

    void traverseBoard();

    void goPath(const pair<int, int> &startingCoordinates, const vstring &startingCity);

    void getCity(pair<int, int> &coordinates);

    void addCityVertex(const pair<int, int> &currentCoordinates, int currentDistance, const vstring &startingCity);

    void handleGraphTile(const pair<int, int> &currentCoordinates, int currentDistance, const vstring &startingCity,
                         LinkedList<pair<pair<int, int>, int>> &path);

    void printCities();

    void printBoard();

public:
    void start();

};


#endif //JAK_DOJADE_HOWTOGO_H
