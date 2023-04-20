#ifndef JAK_DOJADE_HOWTOGO_H
#define JAK_DOJADE_HOWTOGO_H

#include "graph.h"

class howToGo {
    int boardWidth;
    int boardHeight;
    vector<vector<char>> board;
    vector<pair<vstring, pair<int, int>>> cities;

    static bool isLetter(char character);

    bool checkForStar(pair<int, int> &startingCoordinates);

    void readBoard();

    void readAirports();

    void parseBoard();

    void getCity(pair<int, int> &coordinates);

    void printCities();

public:
    void start();

};


#endif //JAK_DOJADE_HOWTOGO_H
