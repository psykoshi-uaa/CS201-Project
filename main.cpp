/*
 */
#include "star.h"
//#include "raylib.h"


GameScreen currentScreen = LOGO;
Texture2D titleCard 		= { 0 };
Texture2D logo 			= { 0 };
Texture2D particle		= { 0 };
static GUIbtn newGameBtn	= { 0 };
static GUIbtn exitBtn		= { 0 };
Timer screenTimer;

const int screenWidth	= 800;
const int screenHeight	= 600;


void initMainMenu();
void UpdateCurrentScreen();
void DrawScreen();


int main(){
	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Starcaller");


	currentScreen = LOGO;


	titleCard	= LoadTexture("resources/title.png");
	logo 		= LoadTexture("resources/logo.png");
	initMainMenu();


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


void initMainMenu() {
	newGameBtn.origin = (Vector2) {screenWidth/5, screenHeight - screenHeight/4};
	newGameBtn.position = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 90, 25};
	newGameBtn.hovered = false;
	newGameBtn.selected = false;

	exitBtn.origin = (Vector2) {screenWidth/5, newGameBtn.origin.y + 25};
	exitBtn.position = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 90, 25};
	exitBtn.hovered = false;
	exitBtn.selected = false;
}


void UpdateCurrentScreen(){
	switch (currentScreen)
	{
		case LOGO: {
			screenTimer.Run();

			if (screenTimer.Wait(3)) {
				currentScreen = TITLE;
				screenTimer.Reset();
			}
		}
		break;
		
		case TITLE: {
			screenTimer.Run();

			if (screenTimer.Wait(4) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				currentScreen = MAINMENU;
				screenTimer.Reset();
			}
		}
		break;

		case MAINMENU: {
		}

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
			DrawTexture(titleCard, screenWidth/2 - titleCard.width/2, screenHeight/5, WHITE);
			DrawText("<click anywhere>", screenWidth/2 - 70, 340, 20, WHITE);
		}
		break;

		case MAINMENU: {
			DrawTexture(titleCard, screenWidth/2 - titleCard.width/2, screenHeight/5, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), newGameBtn.position)) {
				DrawTextEx(GetFontDefault(), "new game", newGameBtn.origin, 20, 0, BLUE);
			}
			else {
				DrawTextEx(GetFontDefault(), "new game", newGameBtn.origin, 20, 0, WHITE);
			}

			if (CheckCollisionPointRec(GetMousePosition(), exitBtn.position)) {
				DrawTextEx(GetFontDefault(), "exit", exitBtn.origin, 20, 0, BLUE);
			}
			else {
				DrawTextEx(GetFontDefault(), "exit", exitBtn.origin, 20, 0, WHITE);
			}
		}
		break;

		default:break; 
	}

	EndDrawing();
}

