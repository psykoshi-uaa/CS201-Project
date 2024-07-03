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
static int hubBtnGrid[MAXBTNS];
static int boardBtnGrid[MAXBTNS];

//module function prototypes
static void InitMainMenu();
static void InitHub();
static void InitBoard();
static void UpdateCurrentScreen();
static void DrawScreen();
static void CheckBtnCollision();
static void CheckBtnPressed();

//declaring global
GameScreen currentScreen = LOGO;
Buttons btnHovered = NOBTN;

//main program
int main(){
	InitMainMenu();
	InitHub();
	InitBoard();

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
	sagaFont	= LoadFont("resources/saga-font.ttf");
	
	currentScreen = LOGO;

	btnHovered = NOBTN;

	newGameBtn.origin = (Vector2) {screenWidth/5, screenHeight - screenHeight/4};
	newGameBtn.position = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 90, 25};

	exitBtn.origin = (Vector2) {screenWidth/5, newGameBtn.origin.y + 25};
	exitBtn.position = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 90, 25};
}


//initialize Hub
static void InitHub() {
	btnHovered = NOBTN;

	hubBtnGrid[0] = Buttons::MISSIONBOARD;
	hubBtnGrid[1] = Buttons::STATUS;
	hubBtnGrid[2] = Buttons::MARKET;
	hubBtnGrid[3] = Buttons::GIVEUP;
	for (int i=4; i<MAXBTNS; i++) {
		hubBtnGrid[i] = NOBTN;
	}

	boardBtn.origin = (Vector2) { 50, 100+(MISSIONBOARD - 10) * 50};
	boardBtn.position = (Rectangle) {boardBtn.origin.x, boardBtn.origin.y, 200, 50};
}


//initiliaze Board
static void InitBoard() {
	btnHovered = NOBTN;

	boardBtnGrid[0] = Buttons::ODDJOB;
	boardBtnGrid[1] = Buttons::GATHER;
	boardBtnGrid[2] = Buttons::SALVAGE;
	boardBtnGrid[3] = Buttons::BOUNTY;
	boardBtnGrid[4] = Buttons::RAID;
	for (int i=5; i<MAXBTNS; i++) {
		boardBtnGrid[i] = NOBTN;
	}
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
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				currentScreen = MAINMENU;
				screenTimer.Reset();
			}
		}
		break;

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
			DrawTextEx(sagaFont, "<click anywhere>", (Vector2){screenWidth/2 - 70, 340}, 30, 0, WHITE);
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
		 
		case HUB: {
			DrawTextEx(sagaFont, "MISSIONS", boardBtn.origin, 50, 0, WHITE);
		}

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
						currentScreen = HUB;
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