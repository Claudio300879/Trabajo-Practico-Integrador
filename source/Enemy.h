#pragma once
#include "raylib.h"

class Enemy {
private:
    Vector2 position;
    float speed;
    float minX;
    float maxX;
    int direction; // 1 = derecha, -1 = izquierda
    Texture2D texture;

public:
    Enemy(float startX, float startY, float minX, float maxX, float speed, const char* texturePath);
    ~Enemy();

    void Update();
    void Draw();
    Rectangle GetRect() const;
    void Reset(float startX);
};
