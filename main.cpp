/*
 */
#include "star.h"
#include "raylib.h"


GameScreen currentScreen = LOGO;
Texture2D titleCard 	= { 0 };
Texture2D logo 		= { 0 };
Timer timer;

const int screenWidth	= 800;
const int screenHeight	= 600;


void UpdateCurrentScreen();
void DrawScreen();


int main(){
	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Starcaller");


	currentScreen = LOGO;

	Vector2 center = (Vector2){screenWidth/2, screenHeight/2};

	titleCard	= LoadTexture("resources/title.png");
	logo 		= LoadTexture("resources/logo.png");


	SetTargetFPS(FPS);

	while (!WindowShouldClose()) {

		UpdateCurrentScreen();
		
		DrawScreen();
	}

	UnloadTexture(titleCard);
	UnloadTexture(logo);


	CloseWindow();

	return 0;
}


void UpdateCurrentScreen(){
	switch (currentScreen)
	{
		case LOGO:
		{
			timer.Run();

			if (timer.Wait(3)) {
				currentScreen = TITLE;
			}
		} 
		break;

		case TITLE:
		{
		} 
		break;

		default:break;
	}
}


void DrawScreen() {
	BeginDrawing();

	ClearBackground(BLACK);

	switch (currentScreen) {
		case LOGO: {
			DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, WHITE);
		}
		break;
		
		case TITLE: {
			DrawTexture(titleCard, screenWidth/2 - titleCard.width/2, screenHeight/4, WHITE);
		}
	}

	EndDrawing();
}
