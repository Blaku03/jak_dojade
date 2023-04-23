#include "howToGo.h"
#include <iostream>

void howToGo::start() {

    readBoard();
    parseBoard();
    traverseBoard();
    readAirports();
    findPaths();
//    printCities();
//    printBoard();

//    graph.printGraph();
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

void howToGo::printBoard() {
    std::cout << "\nBoard:\n";
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            std::cout << board[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void howToGo::readBoard() {

    std::cin >> boardWidth >> boardHeight;
    char temp;
    vector<char> rowData;

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            temp = (char) getchar();
            while (temp == '\n') {
                temp = (char) getchar();
            }
            rowData.push_back(temp);
        }
        board.push_back(rowData);
        rowData.clear();
    }
}

void howToGo::readAirports() {
    int numberOfAirports;
    std::cin >> numberOfAirports;

    vstring airportNameDestination, airportNameSource;
    int length;

    for (int i = 0; i < numberOfAirports; i++) {
        std::cin >> airportNameSource >> airportNameDestination;
        std::cin >> length;
        graph.addEdge(airportNameSource, airportNameDestination, length);
    }
}

void howToGo::parseBoard() {
    pair<int, int> coordinatesPosition{0, 0};

    for (; coordinatesPosition.first < boardHeight; coordinatesPosition.first++) {
        for (coordinatesPosition.second = 0; coordinatesPosition.second < boardWidth; coordinatesPosition.second++) {
            if (isLetter(board[coordinatesPosition.first][coordinatesPosition.second])) {
                getCity(coordinatesPosition);
            }
        }

    }
}

void howToGo::traverseBoard() {
    pair<int, int> coordinatesPosition{0, 0};

    vector<vector<char>> copyBoard = board;

    for (; coordinatesPosition.first < boardHeight; coordinatesPosition.first++) {
        for (coordinatesPosition.second = 0; coordinatesPosition.second < boardWidth; coordinatesPosition.second++) {
            if (board[coordinatesPosition.first][coordinatesPosition.second] == '*') {
                for (int i = 0; i < cities.size(); i++) {
                    if (coordinatesPosition == cities[i].second) {
                        bool isInVertex = graph.hashMap.contains(cities[i].first);
                        if (!isInVertex) graph.addVertex(cities[i].first);
                        goPath(coordinatesPosition, cities[i].first);
                        board = copyBoard;
                        break;
                    }
                }
            }
        }
    }

}

void howToGo::goPath(const pair<int, int> &startingCoordinates, const vstring &startingCity) {
    //first pair is coordinates, second is distance
    linkedList<pair<pair<int, int>, int>> path;
    path.push_back(pair<pair<int, int>, int>(startingCoordinates, 0));
    pair<int, int> currentCoordinates{};
    int pathDistance = 0;

    while (path.number_of_nodes > 0) {
        currentCoordinates = path[0]->first;
        pathDistance = path[0]->second;
        path.pop_index(0);
        board[currentCoordinates.first][currentCoordinates.second] = ' ';
//        printBoard();

        //adding to the path if #
        if (currentCoordinates.first - 1 >= 0) {
            currentCoordinates.first--;
            handleGraphTile(currentCoordinates, pathDistance, startingCity, path);
            currentCoordinates.first++;
        }
        if (currentCoordinates.second - 1 >= 0) {
            currentCoordinates.second--;
            handleGraphTile(currentCoordinates, pathDistance, startingCity, path);
            currentCoordinates.second++;
        }
        if (currentCoordinates.first + 1 < boardHeight) {
            currentCoordinates.first++;
            handleGraphTile(currentCoordinates, pathDistance, startingCity, path);
            currentCoordinates.first--;
        }
        if (currentCoordinates.second + 1 < boardWidth) {
            currentCoordinates.second++;
            handleGraphTile(currentCoordinates, pathDistance, startingCity, path);
            currentCoordinates.second--;
        }
    }
}

void
howToGo::handleGraphTile(const pair<int, int> &currentCoordinates, int currentDistance, const vstring &startingCity,
                         linkedList<pair<pair<int, int>, int>> &path) {

    if (board[currentCoordinates.first][currentCoordinates.second] == '#') {
        path.push_back(pair<pair<int, int>, int>(currentCoordinates, currentDistance + 1));
    } else if (board[currentCoordinates.first][currentCoordinates.second] == '*') {
        addCityVertex(currentCoordinates, currentDistance + 1, startingCity);
    }
}

void
howToGo::addCityVertex(const pair<int, int> &currentCoordinates, int currentDistance, const vstring &startingCity) {
    for (int i = 0; i < cities.size(); i++) {
        if (currentCoordinates == cities[i].second) {
            bool isInVertex = graph.hashMap.contains(cities[i].first);
            if (!isInVertex) graph.addVertex(cities[i].first);
            graph.addEdge(startingCity, cities[i].first, currentDistance);
            break;
        }
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

void howToGo::findPaths() {
    int numberOfPaths;
    std::cin >> numberOfPaths;
    int option;

    for (int i = 0; i < numberOfPaths; i++) {
        vstring startingCity, destinationCity;
        std::cin >> startingCity >> destinationCity;
        std::cin >> option;
        graph.findShortestPath(startingCity, destinationCity, option);
    }
}
