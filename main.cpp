#include "star.h"


const int screenWidth = 800;
const int screenHeight = 600;

GameScreen currentScreen = LOGO;
Texture2D titleCard 		= { 0 };
Texture2D logo 			= { 0 };
Texture2D particle		= { 0 };
Font sagaFont			= { 0 };
static int btnHovered		= { 0 };
static GUIbtn newGameBtn	= { 0 };
static GUIbtn exitBtn		= { 0 };
static Timer screenTimer;

static void initMainMenu();
static void UpdateCurrentScreen();
static void DrawScreen();
static void CheckBtnCollision();
static void CheckBtnPressed();


int main(){
	initMainMenu();

	while (!WindowShouldClose()) {

		UpdateCurrentScreen();
		
		DrawScreen();

		CheckBtnCollision();
		CheckBtnPressed();
	}

	UnloadTexture(titleCard);
	UnloadTexture(logo);

	CloseWindow();

	return 0;
}


static void initMainMenu() {
	InitWindow(screenWidth, screenHeight, "Starcaller");
	titleCard	= LoadTexture("resources/title.png");
	logo 		= LoadTexture("resources/logo.png");
	sagaFont	= LoadFont("resources/saga-regular.ttf");
	
	currentScreen = LOGO;

	btnHovered = -1;

	SetTargetFPS(FPS);

	newGameBtn.origin = (Vector2) {screenWidth/5, screenHeight - screenHeight/4};
	newGameBtn.position = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 90, 25};

	exitBtn.origin = (Vector2) {screenWidth/5, newGameBtn.origin.y + 25};
	exitBtn.position = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 90, 25};
}


static void UpdateCurrentScreen(){
	switch (currentScreen)
	{
		case LOGO: {
			screenTimer.Run();

			if (screenTimer.Wait(3) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				currentScreen = TITLE;
				screenTimer.Reset();
			}
		}
		break;
		
		case TITLE: {
			screenTimer.Run();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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


static void DrawScreen() {
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
			if (btnHovered == NEWGAMEBTN) {
				DrawTextEx(sagaFont, "new game", newGameBtn.origin, MAINMENUFONTSIZE, 0, BLUE);
			}
			else {
				DrawTextEx(sagaFont, "new game", newGameBtn.origin, MAINMENUFONTSIZE, 0, WHITE);
			}
			if (btnHovered == EXITBTN) {
				DrawTextEx(sagaFont, "exit", exitBtn.origin, MAINMENUFONTSIZE, 0, BLUE);
			}
			else {
				DrawTextEx(sagaFont, "exit", exitBtn.origin, MAINMENUFONTSIZE, 0, WHITE);
			}
		}
		break;

		default:break; 
	}

	EndDrawing();
}

static void CheckBtnCollision() {
	switch (currentScreen) {
		case MAINMENU: {
			if (CheckCollisionPointRec(GetMousePosition(), newGameBtn.position)) {
				btnHovered = NEWGAMEBTN;
			}
			else  if (CheckCollisionPointRec(GetMousePosition(), exitBtn.position)) {
				btnHovered = EXITBTN;
			}
			else {
				btnHovered = -1;
			}
		} break;

		default: break;
	}
}

static void CheckBtnPressed() {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && btnHovered != -1) {
		switch (currentScreen) {
			case MAINMENU: {
				switch (btnHovered) {
					case NEWGAMEBTN: {
						currentScreen = GAMEPLAY;
					} break;

					case EXITBTN: {
						CloseWindow();
					} break;

					default: break;
				}
			} break;
			
			default: break;
		}
	}
}
