#include "howToGo.h"
#include <iostream>
#include <cstring>

void howToGo::start() {

    //DEBUG
//    std::cout << "Reading board:";
//    auto start = std::chrono::steady_clock::now();
//    readBoard();
//    auto end = std::chrono::steady_clock::now();
//    std::cout << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
//
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
//    printCities();
//    printBoard();

//    graph.printGraph();

//main
    readBoard();
    traverseBoard();
//    readAirports();
//    findPaths();

}

bool howToGo::isLetter(char character) {
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9');
}

void howToGo::printBoard() {
    std::cout << "\nBoard:\n";
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            std::cout << board[i * boardWidth + j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void howToGo::readBoard() {

//    std::cin >> boardWidth >> boardHeight;
    scanf("%d %d", &boardWidth, &boardHeight);
    char *lineBoard = new char[boardWidth + 1];
    char tempChar;
    board = new char[boardHeight * boardWidth];
    getchar();

    for (int i = 0; i < boardHeight; ++i) {
        fgets(lineBoard, boardWidth + 2, stdin);
        if (lineBoard[0] == '\n') fgets(lineBoard, boardWidth + 2, stdin);
        for (int j = 0; j < boardWidth; ++j) {
            board[i * boardWidth + j] = lineBoard[j];
        }
    }
}

void howToGo::readAirports() {
    int numberOfAirports;
//    std::cin >> numberOfAirports;
    scanf("%d", &numberOfAirports);

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
    visitedTiles = new bool[boardHeight * boardWidth + 1];

//    memset(visitedTiles, false, boardHeight * boardWidth);

    vstring *foundCity;
//    long long totalTimeCity = 0;
//    long long totalTimeAddVertex = 0;
//    long long totalTimeGoPath = 0;
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            memset(visitedTiles, false, boardHeight * boardWidth);
        }
    }

//    for (; coordinatesPosition.first < boardHeight; ++coordinatesPosition.first) {
//        for (coordinatesPosition.second = 0; coordinatesPosition.second < boardWidth; ++coordinatesPosition.second) {
//            if (board[coordinatesPosition.first * boardWidth + coordinatesPosition.second] == '*') {
//                //time each of the following
////                auto start = std::chrono::steady_clock::now();
////                foundCity = getCity(coordinatesPosition);
////                auto end = std::chrono::steady_clock::now();
////                totalTimeCity += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
////                start = std::chrono::steady_clock::now();
////                graph.addVertex(*foundCity);
////                end = std::chrono::steady_clock::now();
////                totalTimeAddVertex += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
////                start = std::chrono::steady_clock::now();
////                goPath(coordinatesPosition, *foundCity);
////                end = std::chrono::steady_clock::now();
////                totalTimeGoPath += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//                std::memset(visitedTiles, false, boardWidth * boardHeight);
//            }
//        }
//    }

//    std::cout << "Total time city: " << totalTimeCity << "ms\n";
//    std::cout << "Total time add vertex: " << totalTimeAddVertex << "ms\n";
//    std::cout << "Total time go path: " << totalTimeGoPath << "ms\n";


    delete visitedTiles;

}

bool howToGo::checkIfAnyPathExists(const pair<int, int> &startingCoordinates) {
    if (startingCoordinates.first - 1 >= 0) {
        if (board[(startingCoordinates.first - 1) * boardWidth + startingCoordinates.second] == '#') return true;
    }
    if (startingCoordinates.first + 1 < boardHeight) {
        if (board[(startingCoordinates.first + 1) * boardWidth + startingCoordinates.second] == '#') return true;
    }
    if (startingCoordinates.second - 1 >= 0) {
        if (board[startingCoordinates.first * boardWidth + startingCoordinates.second - 1] == '#') return true;
    }
    if (startingCoordinates.second + 1 < boardWidth) {
        if (board[startingCoordinates.first * boardWidth + startingCoordinates.second + 1] == '#') return true;
    }
    return false;
}

void howToGo::goPath(const pair<int, int> &startingCoordinates, const vstring &startingCity) {
    if (!checkIfAnyPathExists(startingCoordinates)) return;
    //first pair is coordinates, second is distance
    priorityQueue<tile, compare> path;
    path.push(tile(startingCoordinates.first, startingCoordinates.second, 0));
    pair<int, int> currentCoordinates{};
    int pathDistance = 0;

    while (!path.empty()) {
        currentCoordinates = pair<int, int>(path.top().first, path.top().second);
        pathDistance = path.top().distance;
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
                         priorityQueue<tile, compare> &path) {

    if (visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second]) return;
    if (board[currentCoordinates.first * boardWidth + currentCoordinates.second] == '#') {
        path.push(tile(currentCoordinates.first, currentCoordinates.second, currentDistance + 1));
        visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second] = true;
    } else if (board[currentCoordinates.first * boardWidth + currentCoordinates.second] == '*') {
        addCityVertex(currentDistance + 1, startingCity, *getCity(currentCoordinates));
        visitedTiles[currentCoordinates.first * boardWidth + currentCoordinates.second] = true;
    }
}

void
howToGo::addCityVertex(int currentDistance, const vstring &startingCity, const vstring &destinationCity) {
    graph.addVertex(destinationCity);
    graph.addEdge(startingCity, destinationCity, currentDistance);
}

vstring *howToGo::getCity(const pair<int, int> &coordinates) {

    auto *city = new vstring();
    //check from top left corner to bottom right corner in range of 3x3
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            if (dx + coordinates.second < 0 || dx + coordinates.second >= boardWidth) continue;
            if (dy + coordinates.first < 0 || dy + coordinates.first >= boardHeight) continue;
            if (isLetter(board[(coordinates.first + dy) * boardWidth + coordinates.second + dx])) {
                int offset = 0;
                while (offset + dx + coordinates.second >= 0 &&
                       isLetter(board[(coordinates.first + dy) * boardWidth + coordinates.second + dx + offset]))
                    offset--;
                offset++;
                while (offset + dx + coordinates.second < boardWidth &&
                       isLetter(board[(coordinates.first + dy) * boardWidth + coordinates.second + dx + offset])) {
                    city->push_back(board[(coordinates.first + dy) * boardWidth + coordinates.second + dx + offset]);
                    offset++;
                }
                return city;
            }
        }
    }
    return city;
}

void howToGo::findPaths() {
    int numberOfPaths;
//    std::cin >> numberOfPaths;
    scanf("%d", &numberOfPaths);
    int option;

    for (int i = 0; i < numberOfPaths; i++) {
        vstring startingCity, destinationCity;
        std::cin >> startingCity >> destinationCity;
//        std::cin >> option;
        scanf("%d", &option);
        graph.findShortestPath(startingCity, destinationCity, option);
    }
}
