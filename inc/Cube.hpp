#pragma once
#include "raylib.h"

enum Arrow {
    Up,
    Down,
    Left,
    Right,
    None
};

class Cube{

private:
    Vector2 pos;
    Arrow arr;
public:
    Cube(Vector2 _pos);
    ~Cube();

    void Draw();
    void Move();
    void Update();
    Arrow getArr();
    void setArr(Arrow __arr);
    Vector2 getPosition() const;
    void setPosition(Vector2 _pos);

};