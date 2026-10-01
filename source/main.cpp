#include "raylib.h"

int main() {
    //Ventanas de 1024x768 píxeles
    const int anchoVentana = 1024;
    const int altoVentana = 768;
    InitWindow(anchoVentana, altoVentana, "Esfera Viajera");
    SetTargetFPS(60);

    // Propiedades de la esfera
    float radio = 30.0f;

    // Vectores para la posición y para la velocidad
    Vector2 posicion = { (float)anchoVentana / 2, (float)altoVentana / 2 }; // Centro de la pantalla
    Vector2 velocidad = { 300.0f, 250.0f }; // Píxeles por segundo en X e Y

    // Esfera semitransparente (color con alpha)    
    Color colorEsfera = { 250, 41, 55, 128 }; // Rojo semitransparente 
    //250 Rojo
    //41 Verde
    //55 Azul
    //128 Alpha (50% de transparencia)

    // Contador de rebotes
    int contadorRebotes = 0;

    // Bucle principal
    while (!WindowShouldClose()) {

        // Actualiza la posición usando deltaTime
        float deltaTime = GetFrameTime();
        posicion.x += velocidad.x * deltaTime;
        posicion.y += velocidad.y * deltaTime;

        // Rebotes y Contador, cambios de color
       

        // Rebote en bordes Izquierdo / Derecho (Eje X)
        if ((posicion.x + radio) >= anchoVentana) {
            posicion.x = anchoVentana - radio; // Posición para que no se salga
            velocidad.x *= -1;                 // Invertimos la dirección horizontal
            contadorRebotes++;
            colorEsfera = { 0, 228, 48, 128 }; // Verde semitransparente
        }
        else if ((posicion.x - radio) <= 0) {
            posicion.x = radio;                // Posición
            velocidad.x *= -1;
            contadorRebotes++;
            colorEsfera = { 0, 121, 241, 128 }; // Azul semitransparente
        }

        // Rebote en bordes Superior / Inferior (Eje Y)
        if ((posicion.y + radio) >= altoVentana) {
            posicion.y = altoVentana - radio;  // Posición
            velocidad.y *= -1;                 // Invertimos la dirección vertical
            contadorRebotes++;
            colorEsfera = { 253, 249, 0, 128 }; // Amarillo semitransparente
        }
        else if ((posicion.y - radio) <= 0) {
            posicion.y = radio;                // Posición
            velocidad.y *= -1;
            contadorRebotes++;
            colorEsfera = { 200, 122, 255, 128 }; // Púrpura semitransparente
        }

        // --- RENDERIZADO ---
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Dibujo de esfera semitransparente
        DrawCircleV(posicion, radio, colorEsfera);

        // Muestra en pantalla la resolución, posición actual y contador de rebotes
        DrawText(TextFormat("Resolucion: %dx%d", anchoVentana, altoVentana), 20, 20, 20, DARKGRAY);
        DrawText(TextFormat("Posicion: X = %.1f, Y = %.1f", posicion.x, posicion.y), 20, 50, 20, DARKGRAY);
        DrawText(TextFormat("Rebotes: %d", contadorRebotes), 20, 80, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}