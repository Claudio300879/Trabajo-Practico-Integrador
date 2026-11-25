#pragma once
#include "raylib.h"
#include <vector> // Libreria necesaria para recibir la lista de plataformas

class Player {
private:
    Vector2 position;
    float velocityY;
    float speedX;
    float gravity;
    bool isJumping;
    Sound saltoSound;
    Texture2D texture;

public:
    Player(float startX, float startY);
    ~Player();

    // Verifica colisiones 
    void Update(const std::vector<Rectangle>& platforms);
    void Draw();
    void Reset(float startX, float startY);

    Vector2 GetPosition() const { return position; }
};