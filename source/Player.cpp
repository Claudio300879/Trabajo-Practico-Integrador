#include "Player.h"

Player::Player(float startX, float startY) {
    position = { startX, startY };
    velocityY = 0.0f;
    speedX = 4.0f;
    gravity = 0.5f;
    isJumping = false;

    saltoSound = LoadSound("resources/Salto.wav");
    texture = LoadTexture("resources/player.png");
}

Player::~Player() {
    UnloadSound(saltoSound);
    UnloadTexture(texture);
}

void Player::Update(const std::vector<Rectangle>& platforms) {
    //Movimiento horizontal
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        position.x -= speedX;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        position.x += speedX;
    }

    // Límites laterales de la ventana
    if (position.x < 30) position.x = 30;
    if (position.x > 770) position.x = 770;

    // Guardamos la posición Y previa para la colisión milimétrica
    float prevY = position.y;

    //Aplicar gravedad preliminar
    position.y += velocityY;
    velocityY += gravity;

    // Detección exacta de colisión con plataformas
    bool grounded = false;

    for (const auto& plat : platforms) {
        Rectangle playerRect = { position.x - 15.0f, position.y - 40.0f, 30.0f, 40.0f };

        if (CheckCollisionRecs(playerRect, plat)) {
            if (velocityY >= 0.0f && prevY <= plat.y) {
                position.y = plat.y;
                velocityY = 0.0f;
                isJumping = false;
                grounded = true;
                break;
            }
        }
    }

    if (!grounded) {
        isJumping = true;
    }

    // Control de salto 
    // Usamos IsKeyPressed pero aseguramos que responda al primer frame si está en tierra.
    
    if ((IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) && !isJumping) {
        velocityY = -11.0f;
        isJumping = true;
        PlaySound(saltoSound);
    }

    // Si cae al vacío, se reinicia
    if (position.y > 620.0f) {
        Reset(100.0f, 440.0f);
    }
}

void Player::Reset(float startX, float startY) {
    position = { startX, startY };
    velocityY = 0.0f;
    isJumping = false;
}

void Player::Draw() {
    int drawX = (int)position.x - (texture.width / 2);
    int drawY = (int)position.y - texture.height;

    DrawTexture(texture, drawX, drawY, WHITE);
}