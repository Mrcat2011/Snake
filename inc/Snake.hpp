#pragma once
#include "Cube.hpp"
#include "raylib.h"
#include <vector>

class Snake {
private:
  std::vector<Cube> snake;

public:
  Snake(Vector2 pos_cub1);
  ~Snake();

  void SnakeDraw();
  void Add(Vector2 _pos_);
  void snakeUpdate();
  Vector2 getHeadCor() const;
  void setHeadCor(Vector2 pos);
};
