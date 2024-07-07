#include "lib/includes/star.h"
#include <cmath>

//declaring structs and other init stuff
Texture2D titleCard 					= { 0 };
Texture2D titleGlow						= { 0 };
Texture2D titleUnderline				= { 0 };
Texture2D logo 							= { 0 };
Texture2D particle						= { 0 };
Font sagaFont							= { 0 };
static GUIbtn newGameBtn			= { 0 };
static GUIbtn exitBtn					= { 0 };
static GUIbtn hubBtn[HUBNUMBTNS];
static GUIbtn oddjobMissionBtn	= { 0 };
static GUIbtn gatherMissionBtn	= { 0 };
static GUIbtn salvageMissionBtn	= { 0 };
static GUIbtn bountyMissionBtn	= { 0 };
static GUIbtn raidMissionBtn		= { 0 };
static GUIbtn backBtn					= { 0 };
static Timer screenTimer;
static Timer animTimer;
static float alpha, alpha2;
static Vector2 sbar[3];
static bool increasing = true;

//module function prototypes
static void InitMainMenu();
static void InitHub();
static void InitBoard();
static void UpdateCurrentScreen();
static void DrawScreen();
static void DrawStatusBar();
static void DrawBtnSelected(Rectangle, int);
static void CheckBtnCollision();
float WaveAnim(float, float, float);

//declaring global
GameScreen currentScreen = LOGO;
Buttons btnHovered = NOBTN;

//-------------------------------------------------------------------------------
//			main program
//-------------------------------------------------------------------------------
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
	UnloadTexture(titleGlow);
	UnloadTexture(titleUnderline);
	UnloadTexture(logo);

	CloseWindow();

	return 0;
}


//-------------------------------------------------------------------------------
//			initializations
//-------------------------------------------------------------------------------
static void InitMainMenu() {
	InitWindow(screenWidth, screenHeight, "Starcaller");
	titleCard	= LoadTexture("resources/title.png");
	titleGlow	= LoadTexture("resources/title_glow.png");
	titleUnderline	= LoadTexture("resources/title_ship.png");
	logo 		= LoadTexture("resources/logo.png");
	sagaFont	= LoadFontEx("resources/saga.ttf", 72, NULL, 0);
	
	currentScreen = LOGO;
	btnHovered = NOBTN;
	screenTimer.Reset();
	alpha = 0.0f;
	alpha2 = -0.5f;

	newGameBtn.origin = (Vector2) {screenWidth/5, screenHeight - screenHeight/4};
	newGameBtn.border = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 100, 25};

	exitBtn.origin = (Vector2) {screenWidth/5, newGameBtn.origin.y + 25};
	exitBtn.border = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 40, 25};

	backBtn.origin = (Vector2) {(Vector2){screenWidth - MARGIN * 3, screenHeight - MARGIN * 3}};
	backBtn.border = (Rectangle) {backBtn.origin.x - 20, backBtn.origin.y - BTNPADDING, 100, 40 + BTNPADDING * 2};
}

static void InitHub() {
	float sbarH = 5;

	sbar[0] = (Vector2) {15, sbarH};
	sbar[1] = (Vector2) {SBARSEG[0] + 15, sbarH};
	sbar[2] = (Vector2) {SBARSEG[1] + 15, sbarH};

	for (int i=0; i<HUBNUMBTNS; i++) {
		if (i == HUBNUMBTNS - 1) {
			hubBtn[i].origin = (Vector2) { MARGIN, screenHeight - MARGIN * 2};
			hubBtn[i].border = (Rectangle) { hubBtn[i].origin.x - 20, hubBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
		}
		else {
			hubBtn[i].origin = (Vector2) { MARGIN, MARGIN + SBARHEIGHT + 60 * i };
			hubBtn[i].border = (Rectangle) { hubBtn[i].origin.x - 20, hubBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
		}
	}
}

static void InitBoard() {
	btnHovered = NOBTN;
}


//-------------------------------------------------------------------------------
//			update screen
//-------------------------------------------------------------------------------
static void UpdateCurrentScreen(){
	switch (currentScreen)
	{
		case LOGO: {
			screenTimer.Run();

			if (screenTimer.Wait(3) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				screenTimer.Reset();
				animTimer.Reset();
				currentScreen = TITLE;
			}
		} break;
		
		case TITLE: {
			if (alpha2 < 1.0f) {
				alpha += 0.005f;
				alpha2 += 0.005f;
			}
			else {
				if (alpha < 1.0f && increasing == true) {
					alpha += 0.01f;
				}
				else {
					increasing = false;
				}
				
				if (alpha > 0.5f && increasing == false) {
					alpha -= 0.01f;
				}
				else {
					increasing = true;
				}
			}
			
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				screenTimer.Reset();
				animTimer.Reset();
				currentScreen = MAINMENU;
			}
		} break;

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
		} break;

		case HUB: {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				switch (btnHovered) {
					case BOARDBTN: {
						currentScreen = BOARD;
					} break;



					case GIVEUPBTN: {
						CloseWindow();
					} break;
				}
			}
		} break;

		case BOARD: {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				switch (btnHovered) {
					case BACKBTN: {
						currentScreen = HUB;
					}
				}
			}
		} break;

		default:break;
	}
}


//-------------------------------------------------------------------------------
//			draw screen
//-------------------------------------------------------------------------------
static void DrawScreen() {
	BeginDrawing();

	ClearBackground(BLACK);

	switch (currentScreen) {
		case LOGO: {
			DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, WHITE);
		} break;
		
		case TITLE: {
			if (alpha2 < 1.0f) {
				DrawTexture(titleGlow, screenWidth/2 - titleCard.width/2, screenHeight/5, ColorAlpha(WHITE, alpha) );
				DrawTexture(titleCard, screenWidth/2 - titleCard.width/2, screenHeight/5, ColorAlpha(WHITE, alpha2) );
			}
			else {	
				DrawTexture(titleGlow, screenWidth/2 - titleCard.width/2, screenHeight/5, WHITE);
				DrawTexture(titleCard, screenWidth/2 - titleCard.width/2, screenHeight/5, WHITE);
				DrawTextEx(sagaFont, "<click anywhere>", (Vector2){screenWidth/2 - 80, screenHeight/2}, 30, 0, ColorAlpha(WHITE, alpha));
			}
		} break;

		case MAINMENU: {
			DrawTexture(titleGlow, screenWidth/2 - titleCard.width/2, screenHeight/5, WHITE);
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
		} break;

		case HUB: {
			DrawStatusBar();

			for (int i=0; i<HUBNUMBTNS; i++) {
				DrawBtnSelected(hubBtn[i].border, i + 3);
				DrawRectangleLinesEx(hubBtn[i].border, 2, WHITE);
			}
			DrawTextEx(sagaFont, "Mission Board", hubBtn[0].origin, HUBMAINFONTSIZE, 0, WHITE);
			DrawTextEx(sagaFont, "Market", hubBtn[1].origin, HUBMAINFONTSIZE, 0, WHITE);
			DrawTextEx(sagaFont, "Status", hubBtn[2].origin, HUBMAINFONTSIZE, 0, WHITE);
			DrawTextEx(sagaFont, "Give Up", hubBtn[3].origin, HUBMAINFONTSIZE, 0, WHITE);
		} break;

		case BOARD: {
			DrawStatusBar();

			DrawRectangle(MARGIN, SBARHEIGHT + MARGIN, screenWidth - MARGIN * 5, screenHeight - MARGIN * 3, (Color){3, 3, 3, 255} );
			DrawRectangleLines(MARGIN, SBARHEIGHT + MARGIN, screenWidth - MARGIN * 5, screenHeight - MARGIN * 3, WHITE);

			DrawTextEx(sagaFont, "missions available...", (Vector2){MARGIN * 3, SBARHEIGHT + MARGIN}, HUBSUBFONTSIZE, 0, WHITE);

			DrawBtnSelected(backBtn.border, 12);
			DrawTextEx(sagaFont, "Back", backBtn.origin, HUBMAINFONTSIZE, 0, WHITE);
			DrawRectangleLinesEx(backBtn.border, 2, WHITE);
		} break;

		default:break; 
	}

	EndDrawing();
}


//-------------------------------------------------------------------------------
//			draw functions
//-------------------------------------------------------------------------------
static void DrawBtnSelected(Rectangle rct, int btn) {
	if (btnHovered == btn) {
		DrawRectangleRec(rct, DARKBLUE);
	}
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


//-------------------------------------------------------------------------------
//			button collision
//-------------------------------------------------------------------------------
static void CheckBtnCollision() {
	switch (currentScreen) {
		case MAINMENU: {
			if (CheckCollisionPointRec(GetMousePosition(), newGameBtn.border)) {
				btnHovered = NEWGAMEBTN;
			}
			else  if (CheckCollisionPointRec(GetMousePosition(), exitBtn.border)) {
				btnHovered = EXITBTN;
			}
			else {
				btnHovered = NOBTN;
			}
		} break;

		case HUB: {
			if (CheckCollisionPointRec(GetMousePosition(), hubBtn[0].border)) {
				btnHovered = BOARDBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[1].border)) {
				btnHovered = MARKETBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[2].border)) {
				btnHovered = STATUSBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[3].border)) {
				btnHovered = GIVEUPBTN;
			}
			else {
				btnHovered = NOBTN;
			}
		} break;

		case BOARD: {
			if (CheckCollisionPointRec(GetMousePosition(), backBtn.border)) {
				btnHovered = BACKBTN;
			}
			else {
				btnHovered = NOBTN;
			}
		}

		default: break;
	}
}

