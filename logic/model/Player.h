//
// Created by barno on 30.05.2018.
//

#ifndef UNTITLED7_PLAYER_H
#define UNTITLED7_PLAYER_H


#include "Ship.h"

class Player {
public:
    virtual ~Player();
    explicit Player(int id);
    int **getMyMap();
    int **getEnemyMap();
    void clearMaps();
    Ship *getShips();
    int getLife();
    void setLife(int life);
    int getId();

    void setdecpoints();
    void zerodecpoints();
    int getTempX();
    int getTempY();
    void setTempXY(int x, int y);
    void decreasedecpoints();
    int getdecpoints();
    void increasedecpoints();
    int getHitCounter();
    void increaseHitCounter();
    void zeroHitCounter();
    void increaseMissCounter();
    int getMissCounter();
    void zeroMissCounter();

private:
    int **myMap;
    int **enemyMap;
    Ship *ships;
    int id;
    int life;

    int missCounter;
    int hitCounter;
    int tempX;
    int tempY;
    int aidecisionPoints;
};


#endif //UNTITLED7_PLAYER_H
