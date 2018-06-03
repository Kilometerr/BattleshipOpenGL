//
// Created by barno on 30.05.2018.
//

#include "Ship.h"
#include "Point.h"

void Ship::setSize(int size) {
    Ship::size = size;
}

int Ship::getSize() const {
    return size;
}

Ship::~Ship() {
    delete [] positions;
}

Point* Ship::getPositions() const {
    return positions;
}

Ship::Ship() {
    size = 0;
    positions = nullptr;
}

void Ship::setPositions(Point *positions) {
    Ship::positions = positions;
}

int Ship::getLife() const {
    return life;
}

void Ship::setLife(int life) {
    Ship::life = life;
}
