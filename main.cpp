#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "logic/game-engine/GameEngine.h"
#include "logic/ai-engine/AiEngine.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <zconf.h>

int const ROUND_STATE_ERROR = -1;
int const ROUND_STATE_MISS = 0;
int const ROUND_STATE_HIT = 1;
int const ROUND_STATE_HIT_AND_DROWNED = 3;
void showMap(Player *pPlayer);

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int MAX_LEN = 400;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( std::string path );
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

/**
 * Inicjalizacja okna
 * @return
 */
bool init() {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Tworzenie okna
        gWindow = SDL_CreateWindow( "Battleships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Tworzenie miejsca do renderowania
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ) {
                printf( "SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else {
                //Kolor tla
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Inicjalizacja wczytywania obrazkow png
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

/**
 * Wczytywanie zerwnetrzych plikow
 * @return
 */
bool loadMedia() {
    bool success = true;
    //wczytywanie zewnetrznych plikow tutaj
    return success;
}

/**
 * Zamykanie okna
 */
void close() {
    //Usuwanie okna
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

/**
 * Wczytywanie tekstur
 * @param path
 * @return
 */
SDL_Texture* loadTexture( std::string path ) {
    SDL_Texture* newTexture = NULL;

    //Wczytywanie obrazka
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "%s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Tworzenie tekstury z plixeli
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Usuwanie starego obrazu
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

/**
 * Rysowanie siatki
 * @param x poczatkowy x (lewy gory rog)
 * @param y poczatkowy y (lewy gory rog)
 */
void showMesh(int x, int y) {
    //linia pozioma
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
    for (int  i = 0; i < 11; i++) {
        SDL_RenderDrawLine( gRenderer, x, y + i *40, x + MAX_LEN, y + i *40);
    }
    //linia pionowa
    for (int  i = 0; i < 11; i++) {
        SDL_RenderDrawLine( gRenderer, x + i *40, y, x + i *40, y + MAX_LEN);
    }
}

/**
 * Rysowanie mapy
 * @param x
 * @param y
 */
void showMap(int x, int y, int** map) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            SDL_Rect fillRect = {x + i * 40 , y + j * 40, 40, 40};
            switch (map[i][j]) {
                case 0: //puste niebieski
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 0 );
                    break;
                case 1: //statek zielony
                    SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 0 );
                    break;
                case 2: //trafiony czerwony
                    SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0 );
                    break;
                case 3: //pudlo czarne
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                    break;
            }
            SDL_RenderFillRect( gRenderer, &fillRect );
        }
    }
    showMesh(x,y);
}

int main( int argc, char* args[] ) {

    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
        if( !loadMedia() ) {
            printf( "Failed to load media!\n" );
        }
        else {
            bool quit = false;

            SDL_Event e;

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

            while( !quit ) {

                //Oczekiwanie na event wyscia z ekranu
                while( SDL_PollEvent( &e ) != 0 ) {

                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }

                //Czyszczenie ekranu
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                showMap(0,0, game->getActual()->getMyMap());
                showMap(640,0, game->getActual()->getEnemyMap());

                int playerNr = game->getActual()->getId();
                Point move = aiEngine->getPoint(game->getActual());
                int state = gameEngine->action(&move, game);

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
                        quit = true;
                        break;
                }

                Player* winner = game->getWinner();
                if (winner != nullptr) {
                    quit = true;
                    std::cout << "Wygral gracz " << winner->getId();
                }

                //Aktualizacja ekranu
                SDL_RenderPresent( gRenderer );
                SDL_Delay( 500 );
            }
        }
    }

    close();

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