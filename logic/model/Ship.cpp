//
// Created by barno on 30.05.2018.
//

#include "Ship.h"
#include "Point.h"

void Ship::setSize(int size) {
    Ship::size = size;
}

int Ship::getSize() {
    return size;
}

Ship::~Ship() {
    delete [] positions;
}

Point* Ship::getPositions() {
    return positions;
}

Ship::Ship() {
    size = 0;
    positions = nullptr;
}

void Ship::setPositions(Point *positions) {
    Ship::positions = positions;
}

int Ship::getLife() {
    return life;
}

void Ship::setLife(int life) {
    Ship::life = life;
}
