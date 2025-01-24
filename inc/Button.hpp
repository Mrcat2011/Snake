#pragma once
#include "raylib.h"

class Button {
    public:
        Button(const char* image_path, Vector2 image_pos, float scale);
        ~Button();
        void Draw();
        bool isclick(Vector2 mouse_pos, bool mousePressed);
    private:
        Texture2D texture2d;
        Vector2 pos;

};