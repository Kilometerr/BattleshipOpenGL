//
// Created by barno on 30.05.2018.
//

#include "Point.h"

int Point::getX() {
    return x;
}

void Point::setX(int x) {
    Point::x = x;
}

int Point::getY() {
    return y;
}

void Point::setY(int y) {
    Point::y = y;
}

Point::Point() {}

Point::Point(int x, int y) : x(x), y(y) {}
