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

    /*  if (player->getMissCounter() == 3 ){
          player->decreasedecpoints()
      }*/

    if (player->getHitCounter() >= 2) {


        int missComp = 0;
        int decPoints = player->getdecpoints();
        if (player->getMissCounter() >= 4){
            player->zeroMissCounter();
            player->zerodecpoints();
            player->zeroHitCounter();
            decPoints = 5;
        }

        if (player->getMissCounter() == 1){
            switch (decPoints)
            {
                case(4):
                    missComp = player->getHitCounter() -1 ;
                    decPoints = decPoints - 2;
                    player->increaseMissCounter(); // podwyższamy ilosc by gra nie weszła w to samo razy po trafieniu
                    break;

                case(3):
                    missComp = player->getHitCounter() -1 ;
                    decPoints = decPoints - 2;
                    player->increaseMissCounter();
                    break;

                case(2):
                    missComp = player->getHitCounter() - 1;
                    decPoints = decPoints + 2;
                    player->increaseMissCounter();
                    break;

                case(1):
                    missComp = player->getHitCounter() -1 ;
                    decPoints = decPoints + 2;
                    player->increaseMissCounter();
                    break;
            }
        }
        switch (decPoints){
            case (5):
                break;

            case(4):
                if (IsPositionOk(player->getTempX(), player->getTempY() + 1 + missComp, player)){
                    point->setX(player->getTempX());
                    point->setY(player->getTempY() + 1 + missComp);
                    return *point;
                }
                break;

            case (3):
                if (IsPositionOk(player->getTempX() + 1 + missComp, player->getTempY(),player)){
                    point->setX(player->getTempX()+ 1 + missComp);
                    point->setY(player->getTempY());
                    return *point;
                }
                break;

            case (2):
                if (IsPositionOk(player->getTempX(), player->getTempY()-1 - missComp, player)){
                    point->setX(player->getTempX());
                    point->setY(player->getTempY() -1 - missComp);
                    return *point;
                }
                break;

            case (1):
                if (IsPositionOk(player->getTempX()- 1 - missComp, player->getTempY(), player)){
                    point->setX(player->getTempX()- 1 - missComp);
                    point->setY(player->getTempY());
                    return *point;
                }
                break;
        }

    }


    if ((player->getdecpoints() > 0)  && (player->getHitCounter() == 1 ) ){
        int decPoints = player->getdecpoints();
        switch (decPoints){
            case(4):
            {
                player->decreasedecpoints();
                if (IsPositionOk(player->getTempX(), player->getTempY() + 1, player)){
                    point->setX(player->getTempX());
                    point->setY(player->getTempY() + 1);
                    player->increasedecpoints();
                    return *point;
                    break;
                }
            }

            case (3):
            {
                player->decreasedecpoints();
                if (IsPositionOk(player->getTempX() + 1, player->getTempY(),player)){
                    point->setX(player->getTempX()+1);
                    point->setY(player->getTempY());
                    player->increasedecpoints();
                    return *point;
                    break;
                }
            }

            case (2):
            {
                player->decreasedecpoints();
                if (IsPositionOk(player->getTempX(), player->getTempY()-1, player)){
                    point->setX(player->getTempX());
                    point->setY(player->getTempY() -1);
                    player->increasedecpoints();
                    return *point;
                    break;
                }
            }

            case (1):
            {
                player->decreasedecpoints();
                if (IsPositionOk(player->getTempX() -1, player->getTempY(), player)){
                    point->setX(player->getTempX()-1);
                    point->setY(player->getTempY());
                    player->increasedecpoints();
                    return *point;
                    break;
                }else{
                    break;
                }
            }
        }

    }


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
bool  AiEngine::IsPositionOk(int x, int y, Player *player){
    int** map = player->getEnemyMap();
    if (x > 9 || x < 0){
        return false;
    }
    else if ( y > 9 || y < 0)
    {
        return false;
    }
    else if (map[x][y] == MAP_FIELD_STATE_EMPTY)
    {
        return true;
    }else{
        return false;
    }

}

AiEngine::AiEngine() : generator(generator) {
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}
