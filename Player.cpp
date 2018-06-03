//
// Created by barno on 30.05.2018.
//

#include "Player.h"

Player::Player(int _id) {
    life = 14;
    id = _id;
    myMap = new int *[10];
    enemyMap = new int *[10];

    //Inicjalizacja map
    for(int i = 0; i < 10; i++) {
        myMap[i] = new int[10];
        enemyMap[i] = new int[10];
    }
    clearMaps();

    //Inicjalizacja statkow
    *&ships = new Ship[5];
    for(int i = 0; i < 5; i++) {
        auto *ship = new Ship();
        ships[i] = *ship;
    }
}

int **Player::getMyMap() const {
    return myMap;
}

int **Player::getEnemyMap() const {
    return enemyMap;
}

Ship *Player::getShips() const {
    return ships;
}

Player::~Player() {
    for(int i = 0; i < 10; i++) {
        delete[] myMap[i];
        delete[] enemyMap[i];
    }

    delete [] *myMap;
    delete [] *enemyMap;
    delete [] ships;

}

void Player::clearMaps() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0 ; j < 10; j++) {
            myMap[i][j] = 0;
            enemyMap[i][j] = 0;
        }
    }
}

int Player::getId() const {
    return id;
}

int Player::getLife() const {
    return life;
}

void Player::setLife(int life) {
    Player::life = life;
}
