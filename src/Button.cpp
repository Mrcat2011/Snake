#include "../inc/Button.hpp"

Button::Button(const char* image_path, Vector2 imagepos, float scale) {
    Image image = LoadImage(image_path);
    
    int orginalwidth = image.width;
    int orginalheight = image.height;

    int newwidth = static_cast<int>(orginalwidth * scale);
    int newheight = static_cast<int>(orginalheight * scale);

    ImageResize(&image, newwidth, newheight);

    texture2d = LoadTextureFromImage(image);
    UnloadImage(image);
    pos = imagepos;
}

Button::~Button() {
    UnloadTexture(texture2d);
}

void Button::Draw() {
    DrawTexture(texture2d, pos.x, pos.y, WHITE);
}

bool Button::isclick(Vector2 mouse_pos, bool mousePressed)
{
    Rectangle rect = {pos.x, pos.y, static_cast<float>(texture2d.width), static_cast<float>(texture2d.height)};

    if(CheckCollisionPointRec(mouse_pos, rect) && mousePressed) {
        return true;
    }
    return false;
}