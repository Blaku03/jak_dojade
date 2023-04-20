#include "howToGo.h"
#include <iostream>

void howToGo::start() {

//    readBoard();
////    readAirports();
//    parseBoard();
//    printCities();

    //some random stuff just to test if graph works
    graph test;
    vstring temp_name("Warszawa");
    test.addVertex(temp_name);
    temp_name = "Krakow";
    test.addVertex(temp_name);
    temp_name = "Gdansk";
    test.addVertex(temp_name);
    vstring temp_name2("Krakow");
    test.addEdge(temp_name, temp_name2, 100);
    temp_name2 = "Warszawa";
    test.addEdge(temp_name, temp_name2, 200);
    temp_name = "Warszawa";
    test.addEdge(temp_name, temp_name2, 300);

    test.printGraph();
}

bool howToGo::isLetter(char character) {
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

bool howToGo::checkForStar(pair<int, int> &startingCoordinates) {

    for (int i = startingCoordinates.first - 1; i <= startingCoordinates.first + 1; i++) {
        for (int j = startingCoordinates.second - 1; j <= startingCoordinates.second + 1; j++) {
            if (i >= 0 && j >= 0 && i < boardHeight && j < boardWidth && board[i][j] == '*') {
                startingCoordinates.first = i;
                startingCoordinates.second = j;
                return true;
            }
        }
    }

    return false;
}

void howToGo::printCities() {
    for (int i = 0; i < cities.size(); i++) {
        std::cout << cities[i].first << " (" << cities[i].second.first << " " << cities[i].second.second << ")\n";
    }
}

void howToGo::readBoard() {

    std::cin >> boardWidth >> boardHeight;
    char temp;
    vector<char> rowData;

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            std::cin >> temp;
            rowData.push_back(temp);
        }
        board.push_back(rowData);
        rowData.clear();
    }
}

void howToGo::readAirports() {
    int numberOfAirports;
    std::cin >> numberOfAirports;
}

void howToGo::parseBoard() {
    pair<int, int> coordinatesPosition{0, 0};

    for (; coordinatesPosition.first < boardHeight; coordinatesPosition.first++) {
        for (; coordinatesPosition.second < boardWidth; coordinatesPosition.second++) {
            if (isLetter(board[coordinatesPosition.first][coordinatesPosition.second])) {
                getCity(coordinatesPosition);
            }
        }
        coordinatesPosition.second = 0;
    }
}

void howToGo::getCity(pair<int, int> &coordinates) {
    vstring readCity;
    pair<int, int> positionOfCity = coordinates;

    while (coordinates.second < boardWidth && isLetter(board[coordinates.first][coordinates.second])) {
        readCity.push_back(board[coordinates.first][coordinates.second++]);
    }

    if (checkForStar(positionOfCity)) {
        cities.push_back(pair<vstring, pair<int, int>>(readCity, positionOfCity));
        return;
    }

    int lengthOfCity = coordinates.second - positionOfCity.second;
    positionOfCity.second += lengthOfCity - 1;
    checkForStar(positionOfCity);

    cities.push_back(pair<vstring, pair<int, int>>(readCity, positionOfCity));

}
