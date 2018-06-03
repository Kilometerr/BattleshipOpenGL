//
// Created by barno on 30.05.2018.
//

#ifndef UNTITLED7_GAME_H
#define UNTITLED7_GAME_H


#include "Player.h"

class Game {
public:
    Player *getWinner() const;

    void setWinner(Player *winner);

    Player *getActual() const;

    void setActual(Player *actual);

    Player *getNextPlayer() const;

    void setNextPlayer(Player *nextPlayer);

private:
    Player *winner;
    Player *actual;
    Player *nextPlayer;
};


#endif //UNTITLED7_GAME_H
