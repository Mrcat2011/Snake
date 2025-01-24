#pragma once
#include "raylib.h"

class Food{
private:
    Vector2 pos;
    Texture2D tex;
public:
    Food(const char* image_path, float scale);
    ~Food();
    
    void Draw();
    bool isAte();
    Vector2 generateRandomPos();
    Vector2 getPos() const;
    void SetPos(Vector2 _pos);

};