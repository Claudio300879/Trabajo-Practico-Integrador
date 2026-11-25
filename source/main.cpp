#include "Game.h"

int main() {
    Game juego;       // Inicializa todo
    juego.Run();      // Ejecuta el bucle del juego
    return 0;         // Al salir, el destructor limpia la memoria automáticamente
}