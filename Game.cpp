//
// Created by barno on 30.05.2018.
//

#include "Game.h"

Player *Game::getWinner() const {
    return winner;
}

void Game::setWinner(Player *winner) {
    Game::winner = winner;
}

Player *Game::getActual() const {
    return actual;
}

void Game::setActual(Player *actual) {
    Game::actual = actual;
}

Player *Game::getNextPlayer() const {
    return nextPlayer;
}

void Game::setNextPlayer(Player *nextPlayer) {
    Game::nextPlayer = nextPlayer;
}
