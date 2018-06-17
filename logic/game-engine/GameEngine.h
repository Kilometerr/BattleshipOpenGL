//
// Created by barno on 30.05.2018.
//

#ifndef UNTITLED7_GAMEENGINE_H
#define UNTITLED7_GAMEENGINE_H


#include "../model/Player.h"
#include "../model/Point.h"
#include "../model/Game.h"

class GameEngine {
public:
     int action(Point *move, Game *game);
private:
     bool isAllShipsDrowned(Player *player);
     void swap(Game *game);
     void setWinner(Game *game);
     int makeMove(Player *actual, Player *enemy, Point *move);
     int changeShipStatus(Ship *pShip, Point *currentPoint);
};


#endif //UNTITLED7_GAMEENGINE_H
