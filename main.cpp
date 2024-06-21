/*
 */
#include <iostream>
#include "star.h"
#include "raylib.h"


void mainMenu();


int main(){
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Starcaller");

  Image image = LoadImage("resources/titlecard.png");
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  image = LoadImageFromTexture(texture);
  UnloadTexture(texture);

  texture = LoadTextureFromImage(image);
  UnloadImage(image);


  while (!WindowShouldClose()) {
    BeginDrawing();
	
    	ClearBackground(BLACK);
	
	DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/4, WHITE);

    EndDrawing();
  }

  UnloadTexture(texture);

  CloseWindow();

  return 0;
}

void mainMenu() {

}
