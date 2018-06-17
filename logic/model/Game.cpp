//
// Created by barno on 30.05.2018.
//

#include "Game.h"

Player *Game::getWinner() {
    return winner;
}

void Game::setWinner(Player *winner) {
    Game::winner = winner;
}

Player *Game::getActual() {
    return actual;
}

void Game::setActual(Player *actual) {
    Game::actual = actual;
}

Player *Game::getNextPlayer() {
    return nextPlayer;
}

void Game::setNextPlayer(Player *nextPlayer) {
    Game::nextPlayer = nextPlayer;
}
