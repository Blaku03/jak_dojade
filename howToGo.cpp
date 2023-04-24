#include "howToGo.h"
#include <iostream>

void howToGo::start() {

//    std::cout << "Reading board:";
//    auto start = std::chrono::steady_clock::now();
//    readBoard();
//    auto end = std::chrono::steady_clock::now();
//    std::cout << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

//    std::cout << "Traversing board:";
//    start = std::chrono::steady_clock::now();
//    traverseBoard();
//    end = std::chrono::steady_clock::now();
//    std::cout << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
//
//    std::cout << "Reading airports:";
//    start = std::chrono::steady_clock::now();
//    readAirports();
//    end = std::chrono::steady_clock::now();
//    std::cout << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
//
//    start = std::chrono::steady_clock::now();
//    findPaths();
//    std::cout << "Finding paths:";
//    end = std::chrono::steady_clock::now();
//    std::cout << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    readBoard();
    traverseBoard();
    readAirports();
    findPaths();
//    printCities();
//    printBoard();

//    graph.printGraph();
}

bool howToGo::isLetter(char character) {
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9');
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
//            temp = getchar();
//            while (temp == '\n') {
//                temp = getchar();
//            }
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

    vstring airportNameDestination, airportNameSource;
    int length;

    for (int i = 0; i < numberOfAirports; i++) {
        std::cin >> airportNameSource >> airportNameDestination;
        scanf("%d", &length);
        graph.addEdge(airportNameSource, airportNameDestination, length);
    }
}

void howToGo::traverseBoard() {
    pair<int, int> coordinatesPosition{0, 0};

    //make double char board instead of vector char board
    visitedTiles = new bool[boardHeight * boardWidth];
    memset(visitedTiles, false, boardHeight * boardWidth);

    vstring foundCity;

    for (; coordinatesPosition.first < boardHeight; coordinatesPosition.first++) {
        for (coordinatesPosition.second = 0; coordinatesPosition.second < boardWidth; coordinatesPosition.second++) {
            if (board[coordinatesPosition.first][coordinatesPosition.second] == '*') {
//                for (int i = 0; i < cities.size(); i++) {
//                    if (coordinatesPosition == cities[i].second) {
//                        if (!graph.hashMap.contains(cities[i].first)) graph.addVertex(cities[i].first);
//                        goPath(coordinatesPosition, cities[i].first);
//                        board = copyBoard;
//                        break;
//                    }
//                }
//            }
                foundCity = getCity(coordinatesPosition);
                if (!graph.hashMap.contains(foundCity)) graph.addVertex(foundCity);
                goPath(coordinatesPosition, foundCity);
                memset(visitedTiles, false, boardHeight * boardWidth);
            }
        }
    }

    delete visitedTiles;

}

void howToGo::goPath(const pair<int, int> &startingCoordinates, const vstring &startingCity) {
    //first pair is coordinates, second is distance
    priorityQueue<pair<pair<int, int>, int>, compare> path;
    path.push(pair<pair<int, int>, int>(startingCoordinates, 0));
    pair<int, int> currentCoordinates{};
    int pathDistance = 0;


    while (!path.empty()) {
        currentCoordinates = path.top().first;
        pathDistance = path.top().second;
        path.pop();
        visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second] = true;
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
                         priorityQueue<pair<pair<int, int>, int>, compare> &path) {

    if (visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second]) return;
    if (board[currentCoordinates.first][currentCoordinates.second] == '#') {
        path.push(pair<pair<int, int>, int>(currentCoordinates, currentDistance + 1));
        visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second] = true;
    } else if (board[currentCoordinates.first][currentCoordinates.second] == '*') {
        addCityVertex(currentDistance + 1, startingCity, getCity(currentCoordinates));
        visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second] = true;
    }
}

void
howToGo::addCityVertex(int currentDistance, const vstring &startingCity, const vstring &destinationCity) {
    if (!graph.hashMap.contains(destinationCity)) graph.addVertex(destinationCity);
    graph.addEdge(startingCity, destinationCity, currentDistance);
    graph.addEdge(destinationCity, startingCity, currentDistance);
}

vstring &howToGo::getCity(const pair<int, int> &coordinates) {

    auto *city = new vstring();
    //check from top left corner to bottom right corner in range of 3x3
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            if (dx + coordinates.second < 0 || dx + coordinates.second >= boardWidth) continue;
            if (dy + coordinates.first < 0 || dy + coordinates.first >= boardHeight) continue;
            if (isLetter(board[coordinates.first + dy][coordinates.second + dx])) {
                int offset = 0;
                while (offset + dx + coordinates.second >= 0 &&
                       isLetter(board[coordinates.first + dy][coordinates.second + dx + offset]))
                    offset--;
                offset++;
                while (offset + dx + coordinates.second < boardWidth &&
                       isLetter(board[coordinates.first + dy][coordinates.second + dx + offset])) {
                    city->push_back(board[coordinates.first + dy][coordinates.second + dx + offset]);
                    offset++;
                }
                return *city;
            }
        }
    }
    return *city;
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
