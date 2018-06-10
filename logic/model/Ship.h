//
// Created by barno on 30.05.2018.
//

#ifndef UNTITLED7_SHIP_H
#define UNTITLED7_SHIP_H

#include "Point.h"

class Ship {
public:
    Ship();

    Point *getPositions() const;

    int getSize() const;

    void setSize(int size);

    virtual ~Ship();

    void setPositions(Point *positions);

private:
    Point* positions;
    int size;
    int life;
public:
    int getLife() const;

    void setLife(int life);
};


#endif //UNTITLED7_SHIP_H
