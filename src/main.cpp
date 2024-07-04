#include "star.h"

//constants
const int screenWidth = 800;
const int screenHeight = 800;

//declaring structs and other init stuff
Texture2D titleCard 		= { 0 };
Texture2D logo 			= { 0 };
Texture2D particle		= { 0 };
Font sagaFont			= { 0 };
static GUIbtn newGameBtn	= { 0 };
static GUIbtn exitBtn		= { 0 };
static GUIbtn hubBtn[HUBNUMBTNS];
static GUIbtn oddjobMissionBtn	= { 0 };
static GUIbtn gatherMissionBtn	= { 0 };
static GUIbtn salvageMissionBtn = { 0 };
static GUIbtn bountyMissionBtn	= { 0 };
static GUIbtn raidMissionBtn	= { 0 };
static Timer screenTimer;
static int boardBtnGrid[MAXBTNS];
static Vector2 sbar[3];

//module function prototypes
static void InitMainMenu();
static void InitHub();
static void InitBoard();
static void UpdateCurrentScreen();
static void DrawScreen();
static void DrawStatusBar();
static void DrawBtn(Rectangle);
static void CheckBtnCollision();

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
	sagaFont	= LoadFontEx("resources/saga.ttf", 72, NULL, 0);
	
	currentScreen = LOGO;

	btnHovered = NOBTN;

	newGameBtn.origin = (Vector2) {screenWidth/5, screenHeight - screenHeight/4};
	newGameBtn.position = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 95, 25};

	exitBtn.origin = (Vector2) {screenWidth/5, newGameBtn.origin.y + 25};
	exitBtn.position = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 35, 25};
}


//initialize Hub
static void InitHub() {
	float sbarH = 5;

	btnHovered = NOBTN;

	sbar[0] = (Vector2) {15, sbarH};
	sbar[1] = (Vector2) {SBARSEG[0] + 15, sbarH};
	sbar[2] = (Vector2) {SBARSEG[1] + 15, sbarH};

	for (int i=0; i<HUBNUMBTNS; i++) {
		hubBtn[i].origin = (Vector2) { MARGIN, 200 + MARGIN + 100 * i };
		hubBtn[i].position = (Rectangle) { hubBtn[i].origin.x, hubBtn[i].origin.y, HUBBTNWIDTH, HUBBTNHEIGHT };
	}
}


//initiliaze Board
static void InitBoard() {
	btnHovered = NOBTN;
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

		case MAINMENU: {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				switch (btnHovered) {
					case NEWGAMEBTN: {
						currentScreen = HUB;
					} break;
	
					case EXITBTN: {
						CloseWindow();
					} break;
				}
			}
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
			DrawTextEx(sagaFont, "<click anywhere>", (Vector2){screenWidth/2 - 80, 340}, 30, 0, WHITE);
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
			DrawStatusBar();

			DrawTextEx(sagaFont, "MISSIONS", hubBtn[0].origin, HUBMAINFONTSIZE, 0, WHITE);

			DrawTextEx(sagaFont, "MARKET", hubBtn[1].origin, HUBMAINFONTSIZE, 0, WHITE);

			DrawTextEx(sagaFont, "STATUS", hubBtn[2].origin, HUBMAINFONTSIZE, 0, WHITE);

			DrawTextEx(sagaFont, "GIVE UP", hubBtn[3].origin, HUBMAINFONTSIZE, 0, WHITE);
		}

		default:break; 
	}

	EndDrawing();
}


static void DrawBtn(Rectangle rct) {
	DrawRectangleRoundedLines(rct, 0.1, 1, 5, WHITE);
}


static void DrawStatusBar() {
	DrawRectangleLinesEx((Rectangle) {0, 0, screenWidth, SBARHEIGHT}, 3, WHITE);

	for (int i=0; i<SBARNUMSEGS; i++) {
		DrawLine(SBARSEG[i], 0, SBARSEG[i], SBARHEIGHT, WHITE);
	}

	DrawTextEx(sagaFont, "PILOT: xyz", sbar[0], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "CURRENCY: xyz", sbar[1], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "TIME LEFT TIL REPO: xyz", sbar[2], SBARFONTSIZE, 0, WHITE);
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

