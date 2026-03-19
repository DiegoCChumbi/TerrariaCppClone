#include "assetManager.h"
#include "gameMake.h"
#include "helpers.h"
#include "randomStuff.h"
#include <cassert>
#include <gameMap.h>
#include <gameWall.h>
#include <imgui.h>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <string>

struct GameData {
  GameMap gameMap;
  GameWall gameWall;
  Camera2D camera;
  int selectedBlock;
  std::string selectedBlockName;
  bool isBlock;
  std::ranlux24_base rng;
} gameData;

AssetManager assetManager;

bool initGame() {
  assetManager.loadAll();
  gameData.gameMap.create(30, 20);
  gameData.gameWall.create(30, 20);

  gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
  gameData.gameMap.getBlockUnsafe(1, 1).type = Block::bookShelf;
  gameData.gameMap.getBlockUnsafe(2, 2).type = Block::sandChest;
  gameData.gameMap.getBlockUnsafe(3, 3).type = Block::rubyBlock;
  gameData.gameMap.getBlockUnsafe(4, 4).type = Block::dirt;

  gameData.camera.target = {0, 0};
  gameData.camera.rotation = 0.0f;
  gameData.camera.zoom = 100.0f;

  gameData.selectedBlock = 1;
  gameData.selectedBlockName = "Dirt";
  gameData.isBlock = true;
  gameData.rng.seed(123456789);

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

  // update blok selector
  if (IsKeyDown(KEY_ONE)) {
    gameData.selectedBlockName = "Dirt";
    gameData.selectedBlock = 1;
    gameData.isBlock = true;
  } else if (IsKeyDown(KEY_TWO)) {
    gameData.selectedBlockName = "Grass Block";
    gameData.selectedBlock = 2;
    gameData.isBlock = true;
  } else if (IsKeyDown(KEY_THREE)) {
    gameData.selectedBlockName = "Stone";
    gameData.selectedBlock = 3;
    gameData.isBlock = true;
  } else if (IsKeyDown(KEY_FOUR)) {
    gameData.selectedBlock = 11;
    gameData.selectedBlockName = "WoodLog";
    gameData.isBlock = true;
  } else if (IsKeyDown(KEY_FIVE)) {
    gameData.selectedBlockName = "Leaf";
    gameData.selectedBlock = 12;
    gameData.isBlock = true;
  } else if (IsKeyDown(KEY_SIX)) {
    gameData.selectedBlockName = "Wall 1";
    gameData.selectedBlock = 54;
    gameData.isBlock = false;
  } else if (IsKeyDown(KEY_SEVEN)) {
    gameData.selectedBlockName = "Wall 2";
    gameData.selectedBlock = 55;
    gameData.isBlock = false;
  } else if (IsKeyDown(KEY_EIGHT)) {
    gameData.selectedBlockName = "Wall 3";
    gameData.selectedBlock = 56;
    gameData.isBlock = false;
  } else if (IsKeyDown(KEY_NINE)) {
    gameData.selectedBlockName = "Wall 4";
    gameData.selectedBlock = 57;
    gameData.isBlock = false;
  }

  // Mouser position
  Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
  int blockX = (int)floor(worldPos.x);
  int blockY = (int)floor(worldPos.y);

  // delete block
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
    if (b->type)
      *b = {};
    else {
      auto w = gameData.gameWall.getWallSafe(blockX, blockY);
      *w = {};
    }
  }

  // create block
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    if (gameData.isBlock) {
      auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
      if (b) {
        b->type = gameData.selectedBlock;
        b->variant = getRandomInt(gameData.rng, 0, 3);
      }
    } else {
      auto w = gameData.gameWall.getWallSafe(blockX, blockY);
      if (w) {
        w->type = gameData.selectedBlock;
        w->variant = getRandomInt(gameData.rng, 0, 3);
      }
    }
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

  Vector2 topLeftView = GetScreenToWorld2D({0, 0}, gameData.camera);
  Vector2 bottonRightView = GetScreenToWorld2D(
      {(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);

  int startXView = (int)floorf(topLeftView.x - 1);
  int endXView = (int)ceilf(bottonRightView.x + 1);
  int startYView = (int)floorf(topLeftView.y - 1);
  int endYView = (int)ceilf(bottonRightView.y + 1);

  startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
  endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);
  startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
  endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);

  for (int y = startYView; y < endYView; y++) {
    for (int x = startXView; x < endXView; x++) {
      auto &b = gameData.gameMap.getBlockUnsafe(x, y);
      auto &w = gameData.gameWall.getWallUnsafe(x, y);

      // first render the wall

      DrawTexturePro(assetManager.walls,
                     getTextureAtlas(w.type, w.variant, 32, 32),
                     {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);

      // second render the blocks
      if (b.type != Block::air) {

        if (b.type == Block::woodLog) {
          auto &top = gameData.gameMap.getBlockUnsafe(x, y - 1);
          auto &down = gameData.gameMap.getBlockUnsafe(x, y + 1);
          if (top.type == Block::air && down.type == Block::grassBlock) {
            DrawTexturePro(assetManager.tree,
                           getTextureAtlas(7, b.variant, 32, 32),
                           {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);
          } else if (top.type == Block::leaves) {
            DrawTexturePro(assetManager.tree,
                           getTextureAtlas(5, b.variant, 32, 32),
                           {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);
          } else if (top.type == Block::woodLog &&
                     down.type == Block::grassBlock) {

            DrawTexturePro(assetManager.tree,
                           getTextureAtlas(4, b.variant, 32, 32),
                           {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);
          } else {

            DrawTexturePro(assetManager.textures,
                           getTextureAtlas(b.type, b.variant, 32, 32),
                           {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);
          }
        } else {

          DrawTexturePro(assetManager.textures,
                         getTextureAtlas(b.type, b.variant, 32, 32),
                         {(float)x, (float)y, 1, 1}, {0, 0}, 0.0f, WHITE);
        }
      }
    }
  }

  DrawTexturePro(
      assetManager.frame,
      {0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height},
      {(float)blockX, (float)blockY, 1, 1}, {0, 0}, 0.0f, WHITE);
  EndMode2D();

  // print selected block information
  DrawText(gameData.selectedBlockName.c_str(), 5, 5, 20, BLACK);

  return true;
}

bool closeGame() { return true; }
