#include "../inc/Food.hpp"
#include <random>
#include <time.h>

Food::Food(const char *path, float scale) {
  Image image = LoadImage(path);

  int orginal_width = image.width;
  int orginal_height = image.height;

  int newwidth = static_cast<int>(orginal_width * scale);
  int newheight = static_cast<int>(orginal_height * scale);

  tex = LoadTextureFromImage(image);
  UnloadImage(image);
  pos = generateRandomPos();
}

Food::~Food() { UnloadTexture(tex); }

Vector2 Food::generateRandomPos() {
  Vector2 v_p;
  srand(time(0));
  int x = rand() % 880 + 1;
  int y = rand() % 780 + 1;
  v_p.x = float(x);
  v_p.y = float(y);

  return v_p;
}

void Food::Draw() { DrawTexture(tex, pos.x, pos.y, WHITE); }

Vector2 Food::getPos() const { return pos; }

void Food::SetPos(Vector2 _pos) { pos = _pos; }
