#include "assetManager.h"
#include "gameMake.h"
#include <cassert>
#include <gameMap.h>
#include <raylib.h>

struct GameData {
  GameMap gameMap;
  Camera2D camera;
} gameData;

AssetManager assetManager;

bool initGame() {
  assetManager.loadAll();
  gameData.gameMap.create(30, 20);

  gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
  gameData.gameMap.getBlockUnsafe(1, 1).type = Block::dirt;
  gameData.gameMap.getBlockUnsafe(2, 2).type = Block::dirt;
  gameData.gameMap.getBlockUnsafe(3, 3).type = Block::dirt;
  gameData.gameMap.getBlockUnsafe(4, 4).type = Block::dirt;

  gameData.camera.target = {0, 0};
  gameData.camera.rotation = 0.0f;
  gameData.camera.zoom = 1.0f;

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
    gameData.camera.target.x -= 300.f * deltaTime;
  if (IsKeyDown(KEY_RIGHT))
    gameData.camera.target.x += 300.f * deltaTime;
  if (IsKeyDown(KEY_UP))
    gameData.camera.target.y -= 300.f * deltaTime;
  if (IsKeyDown(KEY_DOWN))
    gameData.camera.target.y += 300.f * deltaTime;

  BeginMode2D(gameData.camera);

  for (int y = 0; y < gameData.gameMap.h; y++) {
    for (int x = 0; x < gameData.gameMap.w; x++) {
      auto &b = gameData.gameMap.getBlockUnsafe(x, y);

      if (b.type != Block::air) {
        float size = 32;
        float posX = x * size;
        float posY = y * size;

        DrawTexturePro(assetManager.dirt,
                       Rectangle{0.f, 0.f, (float)assetManager.dirt.width,
                                 (float)assetManager.dirt.height},
                       {posX, posY, size, size}, {0, 0}, 0.0f, WHITE);
      }
    }
  }

  EndMode2D();
  return true;
}

bool closeGame() { return true; }
