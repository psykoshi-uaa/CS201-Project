/*
 */
#include <iostream>
#include "star.h"
#include "raylib.h"
#include <string>
using namespace std;

int main(){
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "Raylib basic window");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
   

	//stuff go here


    EndDrawing();
  }
  CloseWindow();
  return 0;
}
