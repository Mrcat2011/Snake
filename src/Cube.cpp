#include "../inc/Cube.hpp"
#include "raylib.h"

Cube::Cube(Vector2 _pos) : pos(_pos), arr(None) {}
Cube::~Cube() {}

void Cube::Move() {
  if (arr == Up) {
    pos.y -= 10;
  } else if (arr == Down) {
    pos.y += 10;
  } else if (arr == Left) {
    pos.x -= 10;
  } else if (arr == Right) {
    pos.x += 10;
  }
}

void Cube::Draw() {
   Rectangle segment = Rectangle{pos.x, pos.y, 20, 20};
   //DrawRectangle(pos.x, pos.y, 20, 20, BLACK);
   DrawRectangleRounded(segment, 0.5, 6, BLACK);
}

void Cube::Update() {
  if (IsKeyPressed(KEY_W)) {
    arr = Up;
  } else if (IsKeyPressed(KEY_S)) {
    arr = Down;
  } else if (IsKeyPressed(KEY_D)) {
    arr = Right;
  } else if (IsKeyPressed(KEY_A)) {
    arr = Left;
  }
}

Arrow Cube::getArr() { return arr; }

void Cube::setArr(Arrow __arr) { arr = __arr; }

Vector2 Cube::getPosition() const { return pos; }

void Cube::setPosition(Vector2 _pos) { pos = _pos; }
