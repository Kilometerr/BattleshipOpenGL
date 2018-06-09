#include <iostream>
#include <conio.h>
#include <windows.h>
#include "logic/game-engine/GameEngine.h"
#include "logic/ai-engine/AiEngine.h"

int const ROUND_STATE_ERROR = -1;
int const ROUND_STATE_MISS = 0;
int const ROUND_STATE_HIT = 1;
int const ROUND_STATE_HIT_AND_DROWNED = 3;


void showMap(Player *pPlayer);

int main() {
    bool isEnd = false;
    auto *gameEngine = new GameEngine();
    auto *aiEngine = new AiEngine();

    // Ustawianie graczy
    auto *player1 = new Player(1);
    auto *player2 = new Player(2);
    aiEngine->setShips(player1);
    aiEngine->setShips(player2);

    // Ustawianie gry
    auto *game = new Game();
    game->setWinner(nullptr);
    game->setActual(player1);
    game->setNextPlayer(player2);

    showMap(player1);
    showMap(player2);

    while (!isEnd) {
        int playerNr = game->getActual()->getId();
        Point move = aiEngine->getPoint(game->getActual());
        int state = gameEngine->action(&move, game);

        //char c;
        //std::cin.get( c );
        int x = move.getX();
        int y = move.getY();
        std::cout << "Gracz " << playerNr << " wykonal strzal na pole: x:" << x << " y:" << y << std::endl;
        switch (state) {
            case ROUND_STATE_MISS:
                std::cout << "Status: PUDLO" << std::endl;
                break;
            case ROUND_STATE_HIT:
                std::cout << "Status: TRAFIONY" << std::endl;
                break;
            case ROUND_STATE_HIT_AND_DROWNED:
                std::cout << "Status: TRAFIONY ZATOPIONY" << std::endl;
                break;
            default:
                std::cout << "Wystapil blad" << std::endl;
                isEnd = true;
                break;
        }
        //Sleep(1);
        Player* winner = game->getWinner();
        if (winner != nullptr) {
            isEnd = true;
            std::cout << "Wygral gracz " << winner->getId();
        }
    }
    showMap(player1);
    showMap(player2);
    return 0;
}

void showMap(Player *player) {
    std::cout << "\n";
    std::cout << "\n";
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k <10; k++){
           std::cout <<  player->getMyMap()[i][k] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k <10; k++){
            std::cout <<  player->getEnemyMap()[i][k] << " ";
        }
        std::cout << "\n";
    }
}