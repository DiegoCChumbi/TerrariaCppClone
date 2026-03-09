#include <iostream>
#include <raylib.h>

int main() {
  // std::cout << "Hello\n";
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 450, "Window Name");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Bien hecho, primera ventana usando raylib.", 190, 200, 20, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
