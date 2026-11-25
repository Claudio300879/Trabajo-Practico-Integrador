#pragma once
#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

//Estados del juego
enum GameState {
    MENU = 0,
    PLAYING,
    VICTORY
};

class Game {
private:
    const int screenWidth = 800;
    const int screenHeight = 600;
    Player* jugador;

    GameState currentState;
    Rectangle buttonRect;
    Rectangle doorRect;
    bool doorOpen;

    std::vector<Rectangle> platforms;
    std::vector<Enemy*> enemies; // Lista de enemigos 

public:
    Game();
    ~Game();
    void Run();
};