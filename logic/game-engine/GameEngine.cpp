//
// Created by barno on 30.05.2018.
//

#include <cstdio>
#include <iostream>
#include "GameEngine.h"

int const SHIP_STATE_ALIVE = 0;
int const SHIP_STATE_DEAD = 1;

int const ROUND_STATE_ERROR = -1;
int const ROUND_STATE_MISS = 0;
int const ROUND_STATE_HIT = 1;
int const ROUND_STATE_HIT_AND_DROWNED = 3;

int const MAP_FIELD_STATE_EMPTY = 0;
int const MAP_FIELD_STATE_SHIP = 1;
int const MAP_FIELD_STATE_HIT = 2;
int const MAP_FIELD_STATE_MISS = 3;

int GameEngine::action(Point *move, Game *game) {
    //Wykonanie ruchu
    int state = makeMove(game->getActual(), game->getNextPlayer(), move);

    //Jezeli nie ma bledu, dzialamy dalej
    if (state != ROUND_STATE_ERROR) {
        //Ustawianie nastepnego gracza
        swap(game);

        //Ustawianie/badz nie, wygranego
        setWinner(game);
    }

    return state;
}

bool GameEngine::isAllShipsDrowned(Player *player) {
    return player->getLife() == 0;
    /*bool isAllShipsDrowned = true;
    Ship *ships = player->getShips();
    for (int i = 0; i < 5; i++) {
        isAllShipsDrowned &= isShipDrowned(ships[i]);
    }
    return isAllShipsDrowned;*/
}

void GameEngine::swap(Game *game) {
    Player *player1 = game->getActual();
    Player *player2 = game->getNextPlayer();
    game->setActual(player2);
    game->setNextPlayer(player1);
}

void GameEngine::setWinner(Game *game) {
    Player *winner = nullptr;
    if (isAllShipsDrowned(game->getActual())) {
        winner = game->getNextPlayer();
    } else if (isAllShipsDrowned(game->getNextPlayer())) {
        winner = game->getActual();
    }
    game->setWinner(winner);
}

int GameEngine::makeMove(Player *actual, Player *enemy, Point *move) {
    int x = move->getX();
    int y = move->getY();

    int** playerMap = actual->getEnemyMap();
    int** enemyMap = enemy->getMyMap();

    //Strzelalismy juz w to pole, blad
    if (playerMap[x][y] != MAP_FIELD_STATE_EMPTY) {
        return ROUND_STATE_ERROR;
    }

    int fieldState = enemyMap[x][y];

    switch (fieldState) {
        case MAP_FIELD_STATE_EMPTY : // pudlo
            playerMap[x][y] = MAP_FIELD_STATE_MISS;
            enemyMap[x][y] = MAP_FIELD_STATE_MISS;
            return ROUND_STATE_MISS;
        case MAP_FIELD_STATE_SHIP : // trafienie
            playerMap[x][y] = MAP_FIELD_STATE_HIT;
            enemyMap[x][y] = MAP_FIELD_STATE_HIT;
            enemy->setLife(enemy->getLife() - 1);
            // zmieniamy status statku
            return changeShipStatus(enemy->getShips(), move);
        default: // blad
            return ROUND_STATE_ERROR;
    }
}

int GameEngine::changeShipStatus(Ship *ships, Point *currentPoint) {
    bool marked = false;
    for (int i = 0; i < 5; i++) {
        Point *points = ships[i].getPositions();
        for (int j = 0; j < ships[i].getSize(); j++) {
           if ((points[j].getY() == currentPoint->getY()) && (points[j].getX() == currentPoint->getX())) {
               std::cout << "dupa";
               // ustawiamy trafienie dla pola statku
               ships[i].setLife(ships[i].getLife() - 1);
               marked = true;
               // jezeli trafiony zatopiony to zwracamy odpowiedni kod
               if (isShipDrowned(ships[i])) {
                   return ROUND_STATE_HIT_AND_DROWNED;
               }
               break;
           } else {

           }
        }
        // jezeli juz oznaczylismy statek wychodzimy z petli
        if (marked) {
            break;
        }
    }
    return ROUND_STATE_HIT;
}

bool GameEngine::isShipDrowned(Ship ship) {
    return ship.getLife() == 0;
    /*bool isDrowned = true;
    Point *points = ship.getPositions();
    for (int i = 0; i < ship.getSize(); i++) {
        isDrowned &= points[i].getState() == SHIP_STATE_DEAD;
    }
    return isDrowned;*/
}

