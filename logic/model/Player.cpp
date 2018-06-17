//
// Created by barno on 30.05.2018.
//

#include "Player.h"

Player::Player(int _id) {
    life = 14;
    missCounter = 0;
    aidecisionPoints = 0;
    hitCounter = 0;
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

int **Player::getMyMap() {
    return myMap;
}

int **Player::getEnemyMap() {
    return enemyMap;
}

Ship *Player::getShips() {
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

int Player::getId() {
    return id;
}

int Player::getLife() {
    return life;
}

void Player::setLife(int life) {
    Player::life = life;
}

void Player::setdecpoints() {
    Player::aidecisionPoints = 4;

}
void Player::setTempXY(int x, int y){
    Player::tempX = x;
    Player::tempY = y;
}

int Player::getTempX() {
    return tempX;
}

int Player::getTempY() {
    return tempY;
}

void Player::zerodecpoints() {
    Player::aidecisionPoints = 0;
}
int Player::getdecpoints() {
    return aidecisionPoints;
}
void Player::decreasedecpoints(){
    Player::aidecisionPoints--;
}
void Player::increasedecpoints(){
    Player::aidecisionPoints++;
}

int Player::getHitCounter() {
    return hitCounter;
}
void Player::increaseHitCounter(){
    hitCounter++;
}
void Player::zeroHitCounter(){
    hitCounter = 0;
}

int Player::getMissCounter() {
    return missCounter;
}
void Player::increaseMissCounter(){
    missCounter++;
}
void Player::zeroMissCounter(){
    missCounter = 0;
}
