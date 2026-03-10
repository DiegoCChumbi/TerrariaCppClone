#include "assetManager.h"
#include "gameMake.h"
#include "helpers.h"
#include <cassert>
#include <gameMap.h>
#include <imgui.h>
#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>

struct GameData {
  GameMap gameMap;
  Camera2D camera;
} gameData;

AssetManager assetManager;

bool initGame() {
  assetManager.loadAll();
  gameData.gameMap.create(30, 20);

  gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
  gameData.gameMap.getBlockUnsafe(1, 1).type = Block::bookShelf;
  gameData.gameMap.getBlockUnsafe(2, 2).type = Block::sandChest;
  gameData.gameMap.getBlockUnsafe(3, 3).type = Block::rubyBlock;
  gameData.gameMap.getBlockUnsafe(4, 4).type = Block::dirt;

  gameData.camera.target = {0, 0};
  gameData.camera.rotation = 0.0f;
  gameData.camera.zoom = 100.0f;

  return true;
}

bool updateGame() {

  // DrawText("Bien hecho, primera ventana usando raylib.", 190, 200, 20, RED);
  // DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});
  // DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});

  float deltaTime = GetFrameTime();
  if (deltaTime > 1.f / 5) {
    deltaTime = 1 / 5.f;
  }

  gameData.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

  ClearBackground({75, 75, 150, 255});

  // Camera movement
  if (IsKeyDown(KEY_LEFT))
    gameData.camera.target.x -= 7.f * deltaTime;
  if (IsKeyDown(KEY_RIGHT))
    gameData.camera.target.x += 7.f * deltaTime;
  if (IsKeyDown(KEY_UP))
    gameData.camera.target.y -= 7.f * deltaTime;
  if (IsKeyDown(KEY_DOWN))
    gameData.camera.target.y += 7.f * deltaTime;

  // Mouser position
  Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
  int blockX = (int)floor(worldPos.x);
  int blockY = (int)floor(worldPos.y);

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
    if (b)
      *b = {};
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
    if (b)
      b->type = Block::gold;
  }
  // rlImGuiBegin();
  //
  // ImGui::Begin("Test");
  // ImGui::Text("Hola");
  // // ImGui::Text((char *)blockX);
  // // ImGui::Text((char *)blockY);
  // ImGui::End();
  //
  // ImGui::ShowDemoWindow();
  //
  // rlImGuiEnd();

  BeginMode2D(gameData.camera);

  for (int y = 0; y < gameData.gameMap.h; y++) {
    for (int x = 0; x < gameData.gameMap.w; x++) {
      auto &b = gameData.gameMap.getBlockUnsafe(x, y);

      if (b.type != Block::air) {

        DrawTexturePro(assetManager.textures,
                       getTextureAtlas(b.type, 0, 32, 32),
                       {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);
      }
    }
  }

  DrawTexturePro(
      assetManager.frame,
      {0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height},
      {(float)blockX, (float)blockY, 1, 1}, {0, 0}, 0.0f, WHITE);
  EndMode2D();
  return true;
}

bool closeGame() { return true; }
