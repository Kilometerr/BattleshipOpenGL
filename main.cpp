#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/SDL2/SDL_ttf.h"

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
SDL_Surface* button3;
SDL_Surface* endScreen1;
SDL_Surface* endScreen2;
SDL_Surface* message = NULL;

SDL_Texture* menuTexture;
SDL_Texture* button_0_Texture;
SDL_Texture* button_1_Texture;
SDL_Texture* button_2_Texture;
SDL_Texture* button_3_Texture;
SDL_Texture* endScreen1_Texture;
SDL_Texture* endScreen2_Texture;

SDL_Rect dprst[7];
SDL_Color textColor = { 0, 0, 0 };

void aiHelper(Game *pGame, int state, Point point);

void showAvalibleShips(int x, int y, int len, int nr);

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
    if( TTF_Init() == -1 ) {
       return false;
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
    button3 = SDL_LoadBMP( "button3.bmp" );
    endScreen1 = SDL_LoadBMP( "endScreen1.bmp" );
    endScreen2 = SDL_LoadBMP( "endScreen2.bmp" );
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
void showMesh(int x, int y, int nX, int nY, int lenX, int lenY) {
    //linia pozioma
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
    for (int  i = 0; i < nY; i++) {
        SDL_RenderDrawLine( gRenderer, x, y + i * 40, x + lenX, y + i *40);
    }
    //linia pionowa
    for (int  i = 0; i < nX; i++) {
        SDL_RenderDrawLine( gRenderer, x + i * 40, y, x + i * 40, y + lenY);
    }
}

/**
 * Aktualizacja ekranu
 */
void updateView() {
    SDL_RenderPresent( gRenderer );
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
    showMesh(x,y,11,11,MAX_LEN,MAX_LEN);
    updateView();
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

    dprst[0].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[0].y = 200;
    dprst[0].w = BUTTON_WIDTH;
    dprst[0].h = BUTTON_HEIGHT;

    dprst[2].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[2].y = 200 + BUTTON_HEIGHT + 10;
    dprst[2].w = BUTTON_WIDTH;
    dprst[2].h = BUTTON_HEIGHT;

    dprst[4].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[4].y = 200 + 2 * BUTTON_HEIGHT + 20;
    dprst[4].w = BUTTON_WIDTH;
    dprst[4].h = BUTTON_HEIGHT;

    dprst[3].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[3].y = 200 + 3 * BUTTON_HEIGHT + 30;
    dprst[3].w = BUTTON_WIDTH;
    dprst[3].h = BUTTON_HEIGHT;

    dprst[1].x = SCREEN_WIDTH / 2 - BUTTON_WIDTH/2;
    dprst[1].y = 200 + 4 * BUTTON_HEIGHT + 40;
    dprst[1].w = BUTTON_WIDTH;
    dprst[1].h = BUTTON_HEIGHT;

    dprst[5].x = 0;
    dprst[5].y = 0;
    dprst[5].w = SCREEN_WIDTH;
    dprst[5].h = SCREEN_HEIGHT;

    dprst[6].x = 0;
    dprst[6].y = 0;
    dprst[6].w = SCREEN_WIDTH;
    dprst[6].h = SCREEN_HEIGHT;

    //Tworzenie textur do wyswietlania
    menuTexture = SDL_CreateTextureFromSurface(gRenderer, menu);
    button_0_Texture = SDL_CreateTextureFromSurface(gRenderer, button0);
    button_1_Texture = SDL_CreateTextureFromSurface(gRenderer, button1);
    button_2_Texture = SDL_CreateTextureFromSurface(gRenderer, button2);
    button_3_Texture = SDL_CreateTextureFromSurface(gRenderer, button3);

    //Dodatkowe wyczytywanie tekstur konca gry
    endScreen1_Texture = SDL_CreateTextureFromSurface(gRenderer, endScreen1);
    endScreen2_Texture = SDL_CreateTextureFromSurface(gRenderer, endScreen2);
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
    SDL_RenderCopy(gRenderer, button_3_Texture, NULL, &dprst[4]);
}

/**
 * Pokazuje ekran koncowy gry
 * @param winnerPlayerNr
 */
void showEndScreen(int winnerPlayerNr) {
    clearView();
    if (winnerPlayerNr == 1) {
        SDL_RenderCopy(gRenderer, endScreen1_Texture, NULL, &dprst[5]);
    } else {
        SDL_RenderCopy(gRenderer, endScreen2_Texture, NULL, &dprst[6]);
    }
    updateView();
}

/**
 * Menu gry
 * 0 -  wyjscie
 * 1 -  gra czlowiek vs komputer
 * 2 -  gra czlowiek vs komputer (z automatycznym ustawianiem mapy)
 * 3 -  gra kompuer vs komputer
 * @return wybor z menu
 */
int menuAction() {
    const int QUIT = -1;
    const int NEW_GAME = 1;
    const int NEW_GAME_AUTO_MAP = 2;
    const int NEW_AUTO_GAME = 3;
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
                        return NEW_GAME_AUTO_MAP;
                    case SDLK_3:
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
                    for (int i = 1 ; i < 5; i++) {
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
                                case 4:
                                    return NEW_GAME_AUTO_MAP;
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
bool setHumanShipsAction(Player *pPlayer) {
    SDL_Event e;
    int x = -1, y = -1;
    int lastX = -1, lastY = -1;

    /**
     * -2 - pierwszy punkt
     * -1 - brak wyboru
     * 0 - horyzontalnie
     * 1 - wertykalnie
     */
    int state = -2;
    int shipTab[5] = {4,3,3,2,2};
    int shipNr = 0;
    int pointNr = 0;

    int **map = pPlayer->getMyMap();
    Ship *ship;
    Point* points;

    showAvalibleShips(0,440,shipTab[shipNr],pointNr);

    while (true) {
        while (SDL_PollEvent(&e) != 0) {

            if (state == -2) {
                ship = &pPlayer->getShips()[shipNr];
                ship->setSize(shipTab[shipNr]);
                points = new Point[shipTab[shipNr]];
                ship->setPositions(points);
                ship->setLife(shipTab[shipNr]);
            }

            //Wyjscie z aplikacji
            if (e.type == SDL_QUIT) {
                return false;
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
                    if (x > 0 && x < 400 && y > 0 && y < 400) {
                        x /= 40;
                        y /= 40;
                        if (map[x][y] != 0) {
                            //sprawdzamy czy gracz nie zaznaczal
                            //danego pola
                            break;
                        }

                        if (state == -1 && !(
                                    (x == (lastX + 1) && y == lastY) ||
                                    (x == (lastX - 1) && y == lastY) ||
                                    (x == lastX && y == (lastY + 1)) ||
                                    (x == lastX && y == (lastY - 1))
                                )) {
                            break;
                        } else if (state == 0 && lastX != x){
                            break;
                        } else if (state == 1 && lastY != y) {
                            break;
                        }

                        if (state == -2) { //pierwszy strzal
                            state = -1;
                        } else if (state == -1) {
                            if (lastX == x) { //horyznotalnie
                                state = 0;
                            } else { //wertykalnie
                                state = 1;
                            }
                        }

                        points[pointNr].setX(x);
                        points[pointNr].setY(y);
                        map[x][y] = 1;
                        lastX = x;
                        lastY = y;
                        ++pointNr;

                        clearView();
                        showMap(0,0,map);
                        showAvalibleShips(0,440,shipTab[shipNr],pointNr);

                        //zerujemy dane dla kolejnego statku
                        if (shipTab[shipNr] == pointNr) {
                            state = -2;
                            ++shipNr;
                            pointNr = 0;
                            lastX = -1;
                            lastY = -1;

                            clearView();
                            showMap(0,0,map);
                            showAvalibleShips(0,440,shipTab[shipNr],pointNr);

                            if (shipNr == 5) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Pokazywanie akualny statkow do ustaiwenia
 * @param x
 * @param y
 * @param i2
 * @param nr
 */
void showAvalibleShips(int x, int y, int len, int nr) {
    for (int i = 0; i < len; i++) {
        SDL_Rect fillRect = {x + i * 40, y, 40, 40};
        if (i < nr) {//statek czerowny
            SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
        } else {//statek zielony
            SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
        }
        SDL_RenderFillRect( gRenderer, &fillRect);
    }
    showMesh(x, y, len + 1, 2, len * 40, 40);
    updateView();
}

/**
 * Pobieranie ruchu od gracza
 * @param pPlayer
 * @return
 */
Point *getHumanPointAction(Player *pPlayer) {
    SDL_Event e;
    int x = -1, y = -1;

    while (true) {
        while (SDL_PollEvent(&e) != 0) {

            //Wyjscie z aplikacji
            if (e.type == SDL_QUIT) {
                return NULL;
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
                    x -= 600;
                    if (x > 0 && x < 400 && y > 0 && y < 400) {
                        x /= 40;
                        y /= 40;
                        if (pPlayer->getEnemyMap()[x][y] != 0) {
                            //sprawdzamy czy gracz nie zaznaczal
                            //danego pola
                            continue;
                        }
                        Point *point;
                        point = new Point(x, y);
                        return point;
                    }
                }
            }
        }
    }
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

int main(int argc, char **argv) {

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
            } else if (selection == 1 || selection == 2) { //gra z czlowiekiem
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
                if (selection == 1) { // dla manualnego ustawiania statkow
                    clearView();
                    showMap(0, 0, player1->getMyMap());
                    //showMap(600, 0, player1->getEnemyMap());

                    bool setIsDone = setHumanShipsAction(player1);
                    if (!setIsDone) { //gracz wychodzi z gry
                        close();
                        return 0;
                    }
                } else {
                    aiEngine->setShips(player1);
                }
            } else {
                aiEngine->setShips(player1);
            }
            aiEngine->setShips(player2);

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
                    showMap(600,0,player1->getEnemyMap());
                } else { //Wyswietlanie mapy gracza komputerowego
                    showMap(0,0,game->getActual()->getMyMap());
                    showMap(600,0,game->getActual()->getEnemyMap());
                }
                //Wykonywane ruchu
                Point* move;
                if (gameWithHuman && playerNr == 1) { //gracz czlowiek
                    move = getHumanPointAction(player1);
                } else {
                    move = aiEngine->getPoint(game->getActual());
                }

                //Stan akcji ruchu
                int state = gameEngine->action(move, game);

                if (playerNr == 2 || !gameWithHuman) {
                    aiHelper(game, state, *move);
                }

                showConsoleMove(*move, playerNr);
                showConsoleState(state);

                //Wystapil blad - zakoncz petle gry
                if (state == ROUND_STATE_ERROR) {
                    quit = true;
                }

                //Ustawianie wygranego
                if (!quit) {
                    quit = setWinner(game);
                    if (quit) {
                        showEndScreen(game->getWinner()->getId());
                    }
                }

                //Opoznienie 500ms
                if (!gameWithHuman) {
                    SDL_Delay(500);
                }
            }
        }
    }

    SDL_Delay( 5000 );
    close();
    return 0;
}

/**
 * Pomocnik AI - zbieranie danych do wykonania ruchu
 * @param pGame
 * @param state
 */
void aiHelper(Game *pGame, int state, Point point) {
    switch (state) {
        case ROUND_STATE_MISS:
            if (pGame->getNextPlayer()->getHitCounter() >= 2){
                pGame->getNextPlayer()->increaseMissCounter();
            }
            break;
        case ROUND_STATE_HIT:
            pGame->getNextPlayer()->increaseHitCounter();
            if((pGame->getNextPlayer()->getdecpoints() == 0) && ( pGame->getNextPlayer()->getHitCounter() == 1)){
                pGame->getNextPlayer()->setdecpoints();
            }
            pGame->getNextPlayer()->setTempXY(point.getX(),point.getY());
            break;
        case ROUND_STATE_HIT_AND_DROWNED:
            pGame->getNextPlayer()->zerodecpoints();
            pGame->getNextPlayer()->zeroHitCounter();
            pGame->getNextPlayer()->zeroMissCounter();
            break;
    }
}