#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

int main() {
  // std::cout << "Hello\n";
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 450, "Window Name");

  rlImGuiSetup(true);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    rlImGuiBegin();

    // DrawText("Bien hecho, primera ventana usando raylib.", 190, 200, 20,
    // RED);
    DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});

    DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});
    ImGui::Begin("Test");
    ImGui::Text("Hola");
    ImGui::Button("Boton");
    ImGui::End();

    rlImGuiEnd();

    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();

  return 0;
}
