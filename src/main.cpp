#include "../inc/Button.hpp"
#include "../inc/Food.hpp"
#include "../inc/Snake.hpp"
#include "raylib.h"
#include <algorithm>
#include <cctype>
#include <csignal>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

const int window_height = 800;
const int windows_width = 900;
bool isgameover = false;

void Read(std::ofstream &file, int k) {
  if (file.is_open()) {
    file << k << "\n";
  } else {
    std::cerr << "Error: File is not open.\n";
  }
}

int GetEndHighScore() {
  std::ifstream file("Data/score.txt", std::ios::app);
  std::string line;
  std::string high_score;
  while (getline(file, line)) {
    high_score = line;
  }
  file.close();
  return !high_score.empty() ? std::stoi(high_score) : 0;
}

int GetMaxScore(const std::string &filePath) {
  std::ifstream inFile(filePath);
  if (!inFile.is_open()) {
    std::cerr << "Error: File is not open!\n";
    return 0;
  }

  int maxScore = 0, score;
  while (inFile >> score) {
    maxScore = std::max(maxScore, score);
  }

  inFile.close();
  return maxScore;
}

int GetCoin(const std::string &filePath) {
  std::ifstream inFile(filePath);
  if (!inFile.is_open()) {
    std::cerr << "Error: File is not open!\n";
    return 0;
  }

  int coin = 0, score;
  while (inFile >> score) {
    coin = score;
  }

  inFile.close();
  return coin;
}

void Exit() { CloseWindow(); }
void Munu() { ClearBackground(DARKGREEN); }


void GameOver() {
  DrawText("Game Over", 200, 400, 100, GREEN);
}

std::vector<std::string> GetAllScore() {
  std::ifstream data("Data/all_score.txt", std::ios::app);
  std::vector<std::string> scores;
  std::string line;
  while (std::getline(data, line)) {
    scores.emplace_back(line);
  }
  return scores;
}

int main() {
  SetTraceLogLevel(LOG_NONE);
  InitWindow(windows_width, window_height, "Snake");
  InitAudioDevice();
  Image img = LoadImage("images/music-on.png");
  Texture2D txt = LoadTextureFromImage(img);
  UnloadImage(img);

  Image img2 = LoadImage("images/music-off.png");
  Texture2D txt2 = LoadTextureFromImage(img2);
  UnloadImage(img2);

  Image img3 = LoadImage("images/shop_button.png");
  int orginalwidth = img3.width;
  int orginalheight = img3.height;
  float scale = 0.10;
  int newwidth = static_cast<int>(orginalwidth * scale);
  int newheight = static_cast<int>(orginalheight * scale);

  ImageResize(&img3, newwidth, newheight);
  Texture2D txt3 = LoadTextureFromImage(img3);
  UnloadImage(img3);

  Image img4 = LoadImage("images/speed_icon.png");
  orginalwidth = img3.width;
  orginalheight = img3.height;
  scale = 4.0;
  newwidth = static_cast<int>(orginalwidth * scale);
  newheight = static_cast<int>(orginalheight * scale);

  ImageResize(&img4, newwidth, newheight);
  Texture2D txt4 = LoadTextureFromImage(img4);
  UnloadImage(img4);

  Music music = LoadMusicStream("images/music.wav");
  Sound sound = LoadSound("images/kill.wav");
  Sound sound_eat = LoadSound("images/eat.mp3");

  Food food("images/food.png", 0.23);
start:
  Snake snake({120, 120});
  int score = 0;

  if (!FileExists("Data/score.txt")) {
    std::ofstream initFile("Data/score.txt");
    if (initFile.is_open()) {
      initFile << "0\n";
      initFile.close();
    }
  }

  std::ofstream score_data("Data/score.txt", std::ios::app);
  if (!score_data.is_open()) {
    std::cerr << "Error: Could not open 'Data/score.txt' for writing!\n";
    return -1;
  }

  int coin = GetCoin("Data/coin.txt");
  bool StartGame = false;
  int high_score = GetEndHighScore();
  SetTargetFPS(60);
  srand(time(0));

  bool inmenu = true;
  bool inscore_table = false;
  bool isgameplay = false;
  bool play_music = true;
  bool is_pouse = false;
  bool pause_to_menu_to_score = false;
  bool in_shop = false;
  time_t now;
  PlayMusicStream(music);
  while (!WindowShouldClose()) {
    if (play_music) {
      UpdateMusicStream(music);

      if (GetMusicTimePlayed(music) >= GetMusicTimeLength(music)) {
        StopMusicStream(music);
        PlayMusicStream(music);
      }
    }

    ClearBackground(DARKBLUE);
    BeginDrawing();

    if (inmenu) {
      time(&now);
      char *time = std::ctime(&now);
      std::string str_time = time;
      std::string sub_time = str_time.substr(11, 8);
      DrawText(sub_time.c_str(), 305, 750, 50, WHITE);
      DrawText("SNAKE", 200, 150, 150, WHITE);
      Vector2 posMouse = GetMousePosition();
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if ((posMouse.x > 300 && posMouse.x < 500) &&
            (posMouse.y > 400 && posMouse.y < 450)) {
          inmenu = false;
          play_music = false;
        } else if ((posMouse.x > 300 && posMouse.x < 500) &&
                   (posMouse.y > 470 && posMouse.y < 520)) {
          inscore_table = true;
          inmenu = false;
          // std::cout << "Score" << std::endl;
        } else if ((posMouse.x > 300 && posMouse.x < 500) &&
                   (posMouse.y > 540 && posMouse.y < 590)) {
          std::ofstream all_score_data("Data/all_score.txt", std::ios::app);
          Read(all_score_data, score);
          int d = GetMaxScore("Data/score.txt");
          score = std::max(score, d);
          Read(score_data, score);
          std::ofstream coins("Data/coin.txt", std::ios::app);
          Read(all_score_data, score);
          Read(coins, coin);
          Exit();
        } else if ((posMouse.x > 20 && posMouse.x < 60) &&
                   (posMouse.y > 740 && posMouse.y < 800)) {
          if (play_music) {
            play_music = false;
          } else {
            play_music = true;
          }
          // std::cout << "Music stop or on" << std::endl;
        } else if ((posMouse.x > 850 && posMouse.x < 900) &&
                   (posMouse.y > 750 && posMouse.y < 800)) {
          // std::cout << "Shop is active" << std::endl;
          in_shop = true;
          inmenu = false;
        }
      }
      Color Button_BACK_GROUND1 = BLACK;
      Color Button_BACK_GROUND2 = BLACK;
      Color Button_BACK_GROUND3 = BLACK;
      Color Button_BACK_GROUND4 = BLACK;
      if ((posMouse.x > 300 && posMouse.x < 500) &&
          (posMouse.y > 400 && posMouse.y < 450)) {
        Button_BACK_GROUND1 = RED;
      } else if ((posMouse.x > 300 && posMouse.x < 500) &&
                 (posMouse.y > 470 && posMouse.y < 520)) {
        Button_BACK_GROUND2 = RED;
        // std::cout << "Score" << std::endl;
      } else if ((posMouse.x > 300 && posMouse.x < 500) &&
                 (posMouse.y > 540 && posMouse.y < 590)) {
        Button_BACK_GROUND3 = RED;
      }
      if (play_music) {
        DrawTexture(txt, 10, 750, WHITE);
      } else {
        DrawTexture(txt2, 10, 750, WHITE);
      }

      DrawTexture(txt3, 850, 750, WHITE);

      std::string coin_massage = "Coin : " + std::to_string(coin);
      DrawText(coin_massage.c_str(), 750, 20, 30, YELLOW);

      DrawRectangle(300, 400, 200, 50, Button_BACK_GROUND1);
      DrawText("Start", 350, 415, 30, WHITE);

      DrawRectangle(300, 470, 200, 50, Button_BACK_GROUND2);
      DrawText("Scores", 350, 485, 30, WHITE);

      DrawRectangle(300, 540, 200, 50, Button_BACK_GROUND3);
      DrawText("QUIT", 350, 555, 30, WHITE);
    } else if (in_shop) {
      std::string coin_massage = "Coin : " + std::to_string(coin);
      DrawText(coin_massage.c_str(), 750, 20, 30, YELLOW);
      Color Back_Ground = BLACK;
      Vector2 mousePos = GetMousePosition();
      if (mousePos.x > 0 && mousePos.x < 130 && mousePos.y > 10 &&
          mousePos.y < 210) {
        Back_Ground = RED;
        DrawText("100 COIN", 140, 105, 30, YELLOW);
      }
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mousePos.x > 0 && mousePos.x < 130 && mousePos.y > 10 &&
            mousePos.y < 210) {
          if (coin > 100) {
            coin -= 100;
            Back_Ground = GREEN;
          } else {
            PlaySound(sound);
          }
        }
      }
      DrawRectangle(0, 750, 200, 50, BLACK);
      DrawText("BACK", 50, 765, 30, WHITE);
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
          (mousePos.x > 0 && mousePos.x < 200) &&
          (mousePos.y > 750 && mousePos.y < 800)) {
        inmenu = true;
        std::ofstream coins("Data/coin.txt", std::ios::app);
        Read(coins, coin);
        in_shop = false;
      }
      DrawRectangle(0, 10, 130, 200, Back_Ground);
      DrawTexture(txt4, -35, 30, WHITE);
    } else if (inscore_table && !pause_to_menu_to_score) {
      Vector2 mousePos = GetMousePosition();
      std::vector<std::string> scores = GetAllScore();
      std::string massage_high_score =
          "HIGH SCORE : " + std::to_string(GetMaxScore("Data/score.txt"));
      DrawText(massage_high_score.c_str(), 85, 20, 75, YELLOW);
      int x, y;
      x = 100;
      y = 150;
      for (std::string score : scores) {
        DrawText(score.c_str(), x, y, 20, WHITE);
        y += 20;
        if (y >= 840) {
          y = 150;
          x += 40;
        }
      }
      DrawRectangle(0, 750, 200, 50, BLACK);
      DrawText("BACK", 50, 765, 30, WHITE);
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
          (mousePos.x > 0 && mousePos.x < 200) &&
          (mousePos.y > 750 && mousePos.y < 800)) {
        inmenu = true;
        inscore_table = false;
      }
    } else if (isgameover) {
      Vector2 mousePos = GetMousePosition();
      GameOver();
      // if (IsKeyPressed(KEY_G)) {
      //   isgameover = false;
      //   snake.setHeadCor({120, 120});
      //   score = 0;
      // }
      DrawRectangle(0, 750, 200, 50, BLACK);
      DrawText("BACK", 50, 765, 30, WHITE);
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
          (mousePos.x > 0 && mousePos.x < 200) &&
          (mousePos.y > 750 && mousePos.y < 800)) {
        inmenu = true;
        isgameover = false;
        std::ofstream all_score_data("Data/all_score.txt", std::ios::app);
        std::ofstream coins("Data/coin.txt", std::ios::app);
        Read(all_score_data, score);
        int d = GetMaxScore("Data/score.txt");
        score = std::max(score, d);
        Read(score_data, score);
        Read(coins, coin);
        goto start;
      }
    } else if (is_pouse) {
      ClearBackground(DARKBLUE);
      Vector2 mousePos = GetMousePosition();

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if ((mousePos.x > 300 && mousePos.x < 500) &&
            (mousePos.y > 400 && mousePos.y < 450)) {
          is_pouse = false;
        } else if ((mousePos.x > 300 && mousePos.x < 500) &&
                   (mousePos.y > 470 && mousePos.y < 520)) {
          is_pouse = false;
          pause_to_menu_to_score = true;
          goto start;
        }
      }

      DrawRectangle(300, 400, 200, 50, BLACK);
      DrawText("RESUME", 340, 415, 30, WHITE);

      DrawRectangle(300, 470, 200, 50, BLACK);
      DrawText("MENU", 340, 485, 30, WHITE);
    } else {
      isgameplay = true;
      if (IsKeyPressed(KEY_E)) {
        is_pouse = true;
      }

      std::string Score = "Score : " + std::to_string(score);
      std::string Highscore = "High Score : " + std::to_string(high_score);
      DrawText(Score.c_str(), 50, 50, 25, WHITE);
      DrawText(Highscore.c_str(), 50, 80, 25, WHITE);

      food.Draw();
      snake.snakeUpdate();
      snake.SnakeDraw();

      int snake_x = snake.getHeadCor().x;
      int snake_y = snake.getHeadCor().y;
      int food_x = food.getPos().x;
      int food_y = food.getPos().y;

      if ((snake_x >= food_x - 20 && snake_x <= food_x + 20) &&
          (snake_y >= food_y - 20 && snake_y <= food_y + 20)) {
        food.SetPos(food.generateRandomPos());
        snake.Add({120, 125});
        PlaySound(sound_eat);
        ++score;
        ++coin;
      }

      if (snake_x > windows_width || snake_y > window_height || snake_x < 0 ||
          snake_y < 0) {
        PlaySound(sound);
        isgameover = true;
      }
    }

    EndDrawing();
  }

  if (isgameplay) {
    std::ofstream all_score_data("Data/all_score.txt", std::ios::app);
    Read(all_score_data, score);
    int d = GetMaxScore("Data/score.txt");
    score = std::max(score, d);
    Read(score_data, score);
    std::ofstream coins("Data/coin.txt", std::ios::app);
    Read(coins, coin);
  }
  CloseAudioDevice();
  Exit();
}
