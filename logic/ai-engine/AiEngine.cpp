//
// Created by barno on 30.05.2018.
//

#include <random>
#include <ctime>
#include <windows.h>
#include "AiEngine.h"

int const MAP_FIELD_STATE_EMPTY = 0;
int const MAP_FIELD_STATE_SHIP = 1;

 void AiEngine::setShips(Player *player) {
    setShip(player, 0, 4);
    setShip(player, 1, 3);
    setShip(player, 2, 3);
    setShip(player, 3, 2);
    setShip(player, 4, 2);
}

 Point AiEngine::getPoint(Player *player) {
    bool pointIsInValid = true;
    auto *point = new Point();
    int x = 0, y = 0;
    int** map = player->getEnemyMap();
    while (pointIsInValid) {
        x = getRandomNumber(0,9);
        y = getRandomNumber(0,9);
        if (map[x][y] == MAP_FIELD_STATE_EMPTY) {
            point->setX(x);
            point->setY(y);
            pointIsInValid = false;
        }
    }
    return *point;
}

 void AiEngine::setShip(Player *player, int shipNr, int size) {
    bool isShipSetProperly = false;
    int **map = player->getMyMap();
    int x = 0, y = 0;
    int h = 0, v = 0;
    Ship *ship = &player->getShips()[shipNr];
    ship->setSize(size);
    auto* points = new Point[size];
    ship->setPositions(points);

    while (!isShipSetProperly) {
        v = 0;
        h = getRandomNumber(0,1);
        if (h == 0) {
            v = 1;
        }

        x = getRandomNumber(0,9);
        y = getRandomNumber(0,9);

        if (map[x][y] != MAP_FIELD_STATE_EMPTY) {
            continue;
        }

        if ((size > 1)) { //1+
            if (x + h > 9 || y + v > 9 || map[x + h][y + v] != MAP_FIELD_STATE_EMPTY) {
                continue;
            }
        }

        if ((size > 2)) { //2+
            if (x + 2*h > 9 || y + 2*v > 9 || map[x + 2*h][y + 2*v] != MAP_FIELD_STATE_EMPTY) {
                continue;
            }
        }
        if ((size > 3)) { //3+
            if (x + 3*h > 9 || y + 3*v > 9 || map[x + 3*h][y + 3*v] != MAP_FIELD_STATE_EMPTY) {
                continue;
            }
        }

        isShipSetProperly = true;
        ship->setLife(size);
        map[x][y] = MAP_FIELD_STATE_SHIP;
        points[0].setX(x);
        points[0].setY(y);

        if (size > 1) { //1+
            map[x + h][y + v] = MAP_FIELD_STATE_SHIP;
            points[1].setX(x + h);
            points[1].setY(y + v);
        }
        if (size > 2) { //2+
            map[x + 2*h][y + 2*v] = MAP_FIELD_STATE_SHIP;
            points[2].setX(x + 2*h);
            points[2].setY(y + 2*v);
        }
        if (size > 3) { //3+
            map[x + 3*h][y + 3*v] = MAP_FIELD_STATE_SHIP;
            points[3].setX(x + 3*h);
            points[3].setY(y + 3*v);
        }
    }
}

int AiEngine::getRandomNumber(unsigned int a, unsigned int b) {
    std::uniform_int_distribution<int> distribution(a,b);
    return distribution(generator);
}

AiEngine::AiEngine() : generator(generator) {
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
 }
