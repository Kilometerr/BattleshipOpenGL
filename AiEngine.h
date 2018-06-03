//
// Created by barno on 30.05.2018.
//

#ifndef UNTITLED7_AIENGINE_H
#define UNTITLED7_AIENGINE_H


#include "../model/Point.h"
#include "../model/Player.h"
#include <chrono>
#include <random>

class AiEngine {

public:
    AiEngine();
    Point getPoint(Player* player);
    void setShips(Player* player);

private:
     void setShip(Player* player, int shipNr, int size);
     int getRandomNumber(unsigned int a, unsigned int b);
     std::default_random_engine generator;
};


#endif //UNTITLED7_AIENGINE_H
