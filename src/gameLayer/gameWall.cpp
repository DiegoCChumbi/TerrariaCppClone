#include "gameWall.h"
#include <asserts.h>

void GameWall::create(int w, int h) {
  *this = {};
  mapData.resize(w * h);
  this->w = w;
  this->h = h;

  for (auto &e : mapData) {
    e = {};
  }
}

Wall &GameWall::getWallUnsafe(int x, int y) {
  permaAssertCommentDevelopement(mapData.size() == w * h,
                                 "Map data not initialized");
  permaAssertCommentDevelopement(x >= 0 && y >= 0 && x < w && y < h,
                                 "getWallUnsafe out of bounds errors");
  return mapData[x + y * w];
}

Wall *GameWall::getWallSafe(int x, int y) {
  permaAssertCommentDevelopement(mapData.size() == w * h,
                                 "Map data not initialized");
  if (x < 0 || y < 0 || x >= w || y >= h) {
    return nullptr;
  }
  return &mapData[x + y * w];
}
