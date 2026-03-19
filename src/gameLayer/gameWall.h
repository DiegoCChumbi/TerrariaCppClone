// #include <blocks.h>
#include <vector>
#include <wall.h>

struct GameWall {
  int w = 0;
  int h = 0;

  std::vector<Wall> mapData;
  void create(int w, int h);
  Wall &getWallUnsafe(int x, int y);
  Wall *getWallSafe(int x, int y);
};
