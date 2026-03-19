#include <iostream>
#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include "gameMake.h"

int main() {
// std::cout << "Hello\n";
#if PRODUCTION_BUILD == 1
  SetTraceLogLevel(LOG_NONE);
#endif

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 450, "Window Name");
  SetExitKey(KEY_NULL);
  SetTargetFPS(240);

  rlImGuiSetup(true);
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.FontGlobalScale = 1;

  if (!initGame()) {
    return 0;
  }
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!updateGame()) {
      closeGame();
    }
    // rlImGuiBegin();
    //
    // ImGui::Begin("Test");
    // ImGui::Text("Hola");
    // if (ImGui::Button("Boton")) {
    //   std::cout << "Boton presionado" << std::endl;
    // }
    // ImGui::End();
    //
    // ImGui::ShowDemoWindow();
    //
    // rlImGuiEnd();

    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();
  closeGame();

  return 0;
}
