#include "star.h"

//constants
const int screenWidth = 800;
const int screenHeight = 600;

//declaring structs and other init stuff
Texture2D titleCard 		= { 0 };
Texture2D logo 			= { 0 };
Texture2D particle		= { 0 };
Font sagaFont			= { 0 };
static GUIbtn newGameBtn	= { 0 };
static GUIbtn exitBtn		= { 0 };
static GUIbtn boardBtn		= { 0 };
static GUIbtn statusBtn		= { 0 };
static GUIbtn marketBtn		= { 0 };
static GUIbtn giveupBtn		= { 0 };
static GUIbtn oddjobMissionBtn	= { 0 };
static GUIbtn gatherMissionBtn	= { 0 };
static GUIbtn salvageMissionBtn = { 0 };
static GUIbtn bountyMissionBtn	= { 0 };
static GUIbtn raidMissionBtn	= { 0 };
static Timer screenTimer;
static int btnGrid[8];

//module function prototypes
static void InitMainMenu();
static void InitGameLoop();
static void UpdateCurrentScreen();
static void DrawScreen();
static void CheckBtnCollision();
static void CheckBtnPressed();

//declaring global
GameScreen currentScreen = LOGO;
Buttons btnHovered = NOBTN;

//main program
int main(){
		//need to figure out how to initialize these based on gamescreen, not at once...
	InitMainMenu();
	InitGameLoop();

	SetTargetFPS(FPS);

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


//initiliaze main menu
static void InitMainMenu() {
	InitWindow(screenWidth, screenHeight, "Starcaller");
	titleCard	= LoadTexture("resources/title.png");
	logo 		= LoadTexture("resources/logo.png");
	sagaFont	= LoadFont("resources/saga-regular.ttf");
	
	currentScreen = LOGO;

	btnHovered = NOBTN;

	newGameBtn.origin = (Vector2) {screenWidth/5, screenHeight - screenHeight/4};
	newGameBtn.position = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 90, 25};

	exitBtn.origin = (Vector2) {screenWidth/5, newGameBtn.origin.y + 25};
	exitBtn.position = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 90, 25};
}


//initialize game loop
static void InitGameLoop() {
	

	btnHovered = NOBTN;

	btnGrid[0] = Buttons::MISSIONBOARD;
	btnGrid[1] = Buttons::STATUS;
	btnGrid[2] = Buttons::MARKET;
	btnGrid[3] = Buttons::GIVEUP;

	//boardBtn.origin = (Vector2) {
}


//update screen based on events
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


//draw screen elements
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


//check to see if cursor is colliding with any buttons
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
				btnHovered = NOBTN;
			}
		} break;

		default: break;
	}
}


//check to see if a button is pressed
static void CheckBtnPressed() {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && btnHovered != NOBTN) {
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
