#include "../inc/Snake.hpp"
#include "raylib.h"
#include <iostream>

Snake::Snake(Vector2 pos_cub1) {
  Cube head(pos_cub1);
  snake.push_back(head);
}

Snake::~Snake() {}

void Snake::Add(Vector2 _pos_) {
  Vector2 __pos = snake.back().getPosition();
  Cube new_cube(__pos);
  snake.push_back(new_cube);
}

void Snake::snakeUpdate() {
  if (!snake.empty()) {
    snake[0].Update();
    snake[0].Move();

    // Vector2 headPos = snake[0].getPosition();
    // for (size_t i = 1; i < snake.size(); ++i) {
    //     if (headPos.x == snake[i].getPosition().x && headPos.y ==
    //     snake[i].getPosition().y) {
    //         CloseWindow();
    //         std::cout << "It is error" << std::endl;
    //         return;
    //     }
    // }

    for (size_t i = snake.size() - 1; i > 0; --i) {
      Vector2 prevPos = snake[i - 1].getPosition();
      Arrow prevArr = snake[i - 1].getArr();
      snake[i].setPosition(prevPos);
      snake[i].setArr(prevArr);
    }
  }
}

void Snake::SnakeDraw() {
  for (Cube &cub : snake) {
    cub.Draw();
  }
}

Vector2 Snake::getHeadCor() const { return snake[0].getPosition(); }

void Snake::setHeadCor(Vector2 pos) {
  Cube new_cube(pos);
  snake.push_back(new_cube);
}
