#include "Game.h"

Game::Game() {
    InitWindow(screenWidth, screenHeight, "Trabajo Practico Integrador");
    InitAudioDevice();
    SetTargetFPS(60);

    jugador = new Player(100.0f, 440.0f);

    currentState = MENU;

    // Puerta y botón colocado arriba de la puerta 
    doorRect = { 680.0f, 110.0f, 40.0f, 80.0f };
    buttonRect = { 685.0f, 60.0f, 30.0f, 22.0f };
    doorOpen = false;

    //Plataformas en escalera
    platforms.push_back({ 50.0f, 480.0f, 700.0f, 20.0f });  // Piso 0
    platforms.push_back({ 120.0f, 370.0f, 180.0f, 18.0f }); // Piso 1 
    platforms.push_back({ 340.0f, 280.0f, 180.0f, 18.0f }); // Piso 2 
    platforms.push_back({ 540.0f, 190.0f, 180.0f, 18.0f }); // Piso 3

    // Creación de enemigos (uno por plataforma con distintas velocidades)
    // 1. Piso 0 (rápido - caparazón rojo)
    enemies.push_back(new Enemy(200.0f, 480.0f, 80.0f, 700.0f, 3.5f, "resources/shell_rojo.png"));

    // 2. Piso 1 (velocidad media - caparazón azul)
    enemies.push_back(new Enemy(200.0f, 370.0f, 130.0f, 290.0f, 2.0f, "resources/shell_azul.png"));

    // 3. Piso 2 (velocidad moderada - caparazón amarillo)
    enemies.push_back(new Enemy(400.0f, 280.0f, 350.0f, 510.0f, 1.5f, "resources/shell_amarillo.png"));

    // 4. Piso 3 / llegada (más lento - caparazón verde)
    enemies.push_back(new Enemy(600.0f, 190.0f, 550.0f, 670.0f, 1.0f, "resources/shell_verde.png"));
}

Game::~Game() {
    delete jugador;
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    CloseAudioDevice();
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose()) {

        switch (currentState) {
        case MENU:
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentState = PLAYING;
            }
            break;

        case PLAYING:
            // Clic en el botón superior izquierdo
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePos = GetMousePosition();
                if (CheckCollisionPointRec(mousePos, buttonRect)) {
                    doorOpen = !doorOpen;
                }
            }

            // Reiniciar con R
            if (IsKeyPressed(KEY_R)) {
                jugador->Reset(100.0f, 440.0f);
                doorOpen = false;
            }

            // Actualizar jugador y enemigos
            jugador->Update(platforms);
            for (Enemy* enemy : enemies) {
                enemy->Update();
            }

            // COLISIÓN JUGADOR VS ENEMIGOS 
            {
                Vector2 pPos = jugador->GetPosition();
                Rectangle playerRect = { pPos.x - 15.0f, pPos.y - 40.0f, 30.0f, 40.0f };

                for (Enemy* enemy : enemies) {
                    if (CheckCollisionRecs(playerRect, enemy->GetRect())) {
                        jugador->Reset(100.0f, 440.0f);
                        doorOpen = false;
                    }
                }
            }

            // Condición de Victoria
            if (doorOpen) {
                Rectangle playerRect = { jugador->GetPosition().x - 20, jugador->GetPosition().y - 40, 40, 40 };
                if (CheckCollisionRecs(playerRect, doorRect)) {
                    currentState = VICTORY;
                }
            }
            break;

        case VICTORY:
            if (IsKeyPressed(KEY_R)) {
                jugador->Reset(100.0f, 440.0f);
                doorOpen = false;
                currentState = MENU;
            }
            break;
        }

        // RENDERIZADO 
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == MENU) {
            DrawText("Prototipo", 140, 180, 20, DARKBLUE);
            DrawText("Presiona [ESPACIO] o [CLIC] para comenzar", 200, 260, 16, DARKGRAY);
           // DrawText("Sube por las plataformas, haz clic arriba y entra a la puerta", 150, 340, 14, GRAY);
        }
        else if (currentState == PLAYING) {
            // Dibujar plataformas
            for (const auto& plat : platforms) {
                DrawRectangleRec(plat, DARKGRAY);
            }

            // Puerta de salida y texto SALIDA
            DrawRectangleRec(doorRect, doorOpen ? DARKGREEN : LIGHTGRAY);
            DrawText("SALIDA", (int)doorRect.x - 2, (int)doorRect.y - 20, 10, DARKGRAY);

            // Botón interactivo (arriba de la puerta)
            DrawRectangleRec(buttonRect, doorOpen ? GREEN : RED);
            DrawText(doorOpen ? "ON" : "OFF", (int)buttonRect.x + 5, (int)buttonRect.y + 5, 8, WHITE);

            // Dibujar enemigos
            for (Enemy* enemy : enemies) {
                enemy->Draw();
            }

            // Dibujar jugador
            jugador->Draw();

            // Textos y coordenadas
            DrawText("A/D: Mover | ESPACIO: Salta | R: Reiniciar", 30, 20, 14, DARKGRAY);
            Vector2 posJugador = jugador->GetPosition();
            DrawText(TextFormat("Posicion X: %.1f", posJugador.x), 40, 55, 16, DARKGRAY);
            DrawText(TextFormat("Posicion Y: %.1f", posJugador.y), 40, 80, 16, DARKGRAY);

            if (!doorOpen) {
                DrawText("Sube por la escalera, haz clic en el botón superior y toca la puerta", 140, 120, 14, RED);
            }
            else {
                DrawText("¡Puerta abierta! Entra a la puerta para ganar.", 240, 120, 14, DARKGREEN);
            }
        }
        else if (currentState == VICTORY) {
            DrawText("¡NIVEL SUPERADO CON ÉXITO!", 220, 200, 24, DARKGREEN);
            DrawText("Safaste...", 210, 250, 16, DARKGRAY);
            DrawText("Presiona [R] para volver al Menú", 260, 320, 16, DARKBLUE);
        }

        EndDrawing();
    }
}