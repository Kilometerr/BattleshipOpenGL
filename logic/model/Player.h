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
    int **getMyMap() const;
    int **getEnemyMap() const;
    void clearMaps();
    Ship *getShips() const;
    int getLife() const;
    void setLife(int life);
    int getId() const;

private:
    int **myMap;
    int **enemyMap;
    Ship *ships;
    int id;
    int life;
};


#endif //UNTITLED7_PLAYER_H
