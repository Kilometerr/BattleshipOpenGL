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

const int ROUND_STATE_ERROR = -1;
const int ROUND_STATE_MISS = 0;
const int ROUND_STATE_HIT = 1;
const int ROUND_STATE_HIT_AND_DROWNED = 3;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int BUTTON_WIDTH = 402;
const int BUTTON_HEIGHT = 69;
const int MAX_LEN = 400;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Surface* menu;
SDL_Surface* button0;
SDL_Surface* button1;
SDL_Surface* button2;
SDL_Texture* menuTexture;
SDL_Texture* button_0_Texture;
SDL_Texture* button_1_Texture;
SDL_Texture* button_2_Texture;

SDL_Rect sprst[4];
SDL_Rect dprst[4];

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

    //wczytywanie zewnetrznych plikow - menu
    menu = SDL_LoadBMP( "menu.bmp" );
    button0 = SDL_LoadBMP( "button0.bmp" );
    button1 = SDL_LoadBMP( "button1.bmp" );
    button2 = SDL_LoadBMP( "button2.bmp" );
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
 * Rysowanie siatki
 * @param x poczatkowy x (lewy gory rog)
 * @param y poczatkowy y (lewy gory rog)
 */
void showMesh(int x, int y) {
    //linia pozioma
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
    for (int  i = 0; i < 11; i++) {
        SDL_RenderDrawLine( gRenderer, x, y + i * 40, x + MAX_LEN, y + i *40);
    }
    //linia pionowa
    for (int  i = 0; i < 11; i++) {
        SDL_RenderDrawLine( gRenderer, x + i * 40, y, x + i * 40, y + MAX_LEN);
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
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    break;
            }
            SDL_RenderFillRect( gRenderer, &fillRect );
        }
    }
    showMesh(x,y);
}

/**
 * Aktualizacja ekranu
 */
void updateView() {
    SDL_RenderPresent( gRenderer );
}

/**
 * Czyszczenie ekranu
 */
void clearView() {
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
}

/**
 * Tworzenie tekstur przycikow
 */
void initMenuTextures() {
    //Definicja pozycji przyciskow

    sprst[0].x = 0;
    sprst[0].y = 0;
    sprst[0].w = BUTTON_WIDTH;
    sprst[0].h = BUTTON_HEIGHT;

    sprst[1].x = 0;
    sprst[1].y = 0;
    sprst[1].w = BUTTON_WIDTH;
    sprst[1].h = BUTTON_HEIGHT;

    sprst[2].x = 0;
    sprst[2].y = 0;
    sprst[2].w = BUTTON_WIDTH;
    sprst[2].h = BUTTON_HEIGHT;

    sprst[3].x = 0;
    sprst[3].y = 0;
    sprst[3].w = BUTTON_WIDTH;
    sprst[3].h = BUTTON_HEIGHT;

    dprst[0].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[0].y = 200;
    dprst[0].w = BUTTON_WIDTH;
    dprst[0].h = BUTTON_HEIGHT;

    dprst[2].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[2].y = 200 + BUTTON_HEIGHT + 10;
    dprst[2].w = BUTTON_WIDTH;
    dprst[2].h = BUTTON_HEIGHT;

    dprst[3].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[3].y = 200 + 2 * BUTTON_HEIGHT + 20;
    dprst[3].w = BUTTON_WIDTH;
    dprst[3].h = BUTTON_HEIGHT;

    dprst[1].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[1].y = 200 + 3 * BUTTON_HEIGHT + 30;
    dprst[1].w = BUTTON_WIDTH;
    dprst[1].h = BUTTON_HEIGHT;

    //Tworzenie textur do wyswietlania
    menuTexture = SDL_CreateTextureFromSurface(gRenderer, menu);
    button_0_Texture = SDL_CreateTextureFromSurface(gRenderer, button0);
    button_1_Texture = SDL_CreateTextureFromSurface(gRenderer, button1);
    button_2_Texture = SDL_CreateTextureFromSurface(gRenderer, button2);
}

/**
 * Rysowanie menu gry
 */
void showMenu() {
    //Wyswietlanie napisu menu
    SDL_RenderCopy(gRenderer, menuTexture, NULL, &dprst[0]);

    //Wyswietlanie przyciskow
    SDL_RenderCopy(gRenderer, button_0_Texture, NULL, &dprst[1]);
    SDL_RenderCopy(gRenderer, button_1_Texture, NULL, &dprst[2]);
    SDL_RenderCopy(gRenderer, button_2_Texture, NULL, &dprst[3]);
}

/**
 * Menu gry
 * 0 -  wyjscie
 * 1 -  gra czlowiek vs komputer
 * 2 -  gra kompuer vs komputer
 * @return wybor z menu
 */
int menuAction() {
    const int QUIT = -1;
    const int NEW_GAME = 1;
    const int NEW_AUTO_GAME = 2;
    SDL_Event e;
    initMenuTextures();
    int x,y;

    while (true) {

        //Czyszczenie widoku
        clearView();

        //Pokazywanie menu
        showMenu();

        //Aktalizacja widoku
        updateView();

        //Opoznienie
        SDL_Delay(500);

        while (SDL_PollEvent(&e) != 0) {

            //Wyjscie z aplikacji
            if (e.type == SDL_QUIT) {
                return -1;
            }

            //Akcja na klawisze
            else if (e.type == SDL_KEYDOWN) {

                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return QUIT;
                    case SDLK_1:
                        return NEW_GAME;
                    case SDLK_2:
                        return NEW_AUTO_GAME;
                    case SDLK_0:
                        return QUIT;
                }
            }

            //akcja na myszke
            //ruch myszy
            if( e.type == SDL_MOUSEMOTION ) {
                x = e.motion.x;
                y = e.motion.y;
            }

            //klikniecie myszy
            if( e.type == SDL_MOUSEBUTTONDOWN ) {
                if( e.button.button == SDL_BUTTON_LEFT) {
                    //Sprawdzamy kazdy z przycikow
                    for (int i = 1 ; i < 4; i++) {
                        if ((x >= dprst[i].x && x <= dprst[i].x + BUTTON_WIDTH)
                            &&( y >= dprst[i].y && y <= dprst[i].y + BUTTON_HEIGHT ) ){
                            //Akcja na przycisk
                            switch (i) {
                                case 1:
                                    return QUIT;
                                case 2:
                                    return NEW_GAME;
                                case 3:
                                    return NEW_AUTO_GAME;
                                default:
                                    break;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

/**
 * Ustaiwanie statkow przez gracza
 * @param pPlayer
 */
void setHumanShipsAction(Player *pPlayer) {
    //TODO
}

/**
 * Pobieranie ruchu od gracza
 * @param pPlayer
 * @return
 */
Point getHumanPointAction(Player *pPlayer) {
    //TODO
    return Point();
}

/**
 * Ustaiwanie wygranego
 * @param pGame
 * @return
 */
bool setWinner(Game *pGame) {
    bool weHaveWinner = false;
    Player* winner = pGame->getWinner();
    if (winner != nullptr) {
        weHaveWinner = true;
        std::cout << "Wygral gracz " << winner->getId();
    }
    return weHaveWinner;
}

/**
 * Wypisywanie do konsoli informacji o stanie wykonanego ruchu
 * @param state
 */
void showConsoleState(int state) {
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
            break;
    }
}

/**
 * Wypisywanie do konsoli wykonanej akcji
 * @param move
 * @param playerNr
 */
void showConsoleMove(Point move, int playerNr) {
    int x = move.getX();
    int y = move.getY();
    std::cout << "Gracz " << playerNr << " wykonal strzal na pole: x:" << x << " y:" << y << std::endl;
}

/**
 * Pokazywanie mapy w konsoli
 * @param player
 */
void showConsoleMap(Player *player) {
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

int main( int argc, char* args[] ) {

    if( !init() ) {
        std::cout << "Blad poczas inicjalizacji gry!\n";
    } else {
        if( !loadMedia() ) {
            std::cout << "Blad podczas wczytywania plikow!\n";
        } else {
            bool gameWithHuman = false;

            //Wybor typu gry
            int selection =  menuAction();
            if (selection == -1) { // wyjscie z gry
                return 0;
            } else if (selection == 1) { //gra z czlowiekiem
                gameWithHuman = true;
            } // w innym przypadku gra automatyczna

            //Ustawianie gry i silnika
            GameEngine *gameEngine = new GameEngine();
            AiEngine *aiEngine = new AiEngine();

            //Ustawianie graczy
            Player *player1 = new Player(1);
            Player *player2 = new Player(2);

            //Ustaiwanie statkow
            if (gameWithHuman) {
                setHumanShipsAction(player1);
                aiEngine->setShips(player2);
            } else {
                aiEngine->setShips(player1);
                aiEngine->setShips(player2);
            }

            //Ustawianie gry
            Game *game = new Game();
            game->setWinner(nullptr);
            game->setActual(player1);
            game->setNextPlayer(player2);

            //Glowna petla gry
            SDL_Event e;
            bool quit = false;
            while( !quit ) {

                //Oczekiwanie na event wyscia z ekranu
                while( SDL_PollEvent( &e ) != 0 ) {
                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }

                //Czyszczenie ekranu
                clearView();

                //Numer aktalnego gracza
                int playerNr = game->getActual()->getId();

                //Wyswietlanie mapy gracza ludziego
                if (gameWithHuman) {
                    showMap(0,0,player1->getMyMap());
                    showMap(600,0,player2->getEnemyMap());
                } else { //Wyswietlanie mapy gracza komputerowego
                    showMap(0,0,game->getActual()->getMyMap());
                    showMap(600,0,game->getActual()->getEnemyMap());
                }
                //Wykonywane ruchu
                Point move;
                if (gameWithHuman && playerNr == 1) { //gracz czlowiek
                    move = getHumanPointAction(game->getActual());
                } else {
                    move = aiEngine->getPoint(game->getActual());
                }

                //Stan akcji ruchu
                int state = gameEngine->action(&move, game);

                showConsoleMove(move, playerNr);
                showConsoleState(state);

                //Wystapil blad - zakoncz petle gry
                if (state == ROUND_STATE_ERROR) {
                    quit = true;
                }

                //Ustawianie wygranego
                if (!quit) {
                    quit = setWinner(game);
                }

                //Aktalizacja widoku
                updateView();

                //Opoznienie 500ms
                SDL_Delay( 500 );
            }
        }
    }

    close();
    return 0;
}