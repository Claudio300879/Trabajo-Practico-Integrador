#include "Enemy.h"

Enemy::Enemy(float startX, float startY, float minX, float maxX, float speed, const char* texturePath) {
    position = { startX, startY };
    this->minX = minX;
    this->maxX = maxX;
    this->speed = speed;
    direction = 1;
    texture = LoadTexture(texturePath);
}

Enemy::~Enemy() {
    UnloadTexture(texture);
}

void Enemy::Update() {
    // Movimiento horizontal de lado a lado
    position.x += speed * direction;

    // Si llega al borde derecho o izquierdo, invierte la dirección
    if (position.x >= maxX) {
        position.x = maxX;
        direction = -1;
    }
    else if (position.x <= minX) {
        position.x = minX;
        direction = 1;
    }
}

void Enemy::Draw() {
    // Centra la textura 
    int drawX = (int)position.x - (texture.width / 2);
    int drawY = (int)position.y - texture.height;
    DrawTexture(texture, drawX, drawY, WHITE);
}

Rectangle Enemy::GetRect() const {
    // Rectángulo de colisión 
    return { position.x - 15.0f, position.y - 30.0f, 30.0f, 30.0f };
}

void Enemy::Reset(float startX) {
    position.x = startX;
    direction = 1;
}