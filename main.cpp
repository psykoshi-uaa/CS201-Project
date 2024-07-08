#include "lib/includes/star.h"
#include <cmath>

//declaring structs and other init stuff
Texture2D titleCard = { 0 };
Texture2D titleGlow = { 0 };
Texture2D titleUnderline = { 0 };
Texture2D logo = { 0 };
Texture2D particle = { 0 };
Font sagaFont = { 0 };
Vector2 sbar[SBARNUMSEGS+1];

Vector2 starPtxPos[MAXSTARPTX]; //TODO: Turn this into array of structs instead of this mess
Color starPtxColor[MAXSTARPTX];
int starPtx[MAXSTARPTX];

static GUIbtn newGameBtn = { 0 };
static GUIbtn exitBtn = { 0 };
static GUIbtn hubBtn[HUBNUMBTNS];
static GUIbtn oddjobMissionBtn = { 0 };
static GUIbtn gatherMissionBtn = { 0 };
static GUIbtn salvageMissionBtn	= { 0 };
static GUIbtn bountyMissionBtn = { 0 };
static GUIbtn raidMissionBtn = { 0 };
static GUIbtn backBtn = { 0 };
static Timer screenTimer;
static Timer animTimer;
static Timer ptxTimer;
static float alphaChannel[5];
static bool increasing = true;

//function prototypes
void DrawStatusBar(Vector2*);
void DrawBtnSelected(Rectangle, int);
void AlphaWaveAnim(float&, float, float, float, bool&);
void AlphaLinearAnim(float&, float, float, bool);
void PTXStars(int*, Vector2*, Color*, float);

static void InitGame();
static void UpdateCurrentScreen();
static void DrawScreen();
static void CheckBtnCollision();

//declaring global
GameScreen currentScreen = LOGO;
Buttons btnHovered = NOBTN;

//-------------------------------------------------------------------------------
//			main program
//-------------------------------------------------------------------------------
int main(){
	InitGame();

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
static void InitGame() {
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Starcaller");
	titleCard	= LoadTexture("resources/title.png");
	titleGlow	= LoadTexture("resources/title_glow.png");
	titleUnderline	= LoadTexture("resources/title_ship.png");
	logo 		= LoadTexture("resources/logo.png");
	sagaFont	= LoadFontEx("resources/saga.ttf", 72, NULL, 0);
	
	currentScreen = LOGO;
	btnHovered = NOBTN;
	screenTimer.Reset();
	alphaChannel[0] = 0.0f;
	alphaChannel[1] = -0.5f;
	
	float sbarH = 5;
	sbar[0] = (Vector2) {15, sbarH};
	sbar[1] = (Vector2) {195, sbarH};
	sbar[2] = (Vector2) {SBARSEG[1] + 15, sbarH};

	newGameBtn.origin = (Vector2) {SCREENWIDTH/5, SCREENHEIGHT - SCREENHEIGHT/4};
	newGameBtn.border = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 100, 25};

	exitBtn.origin = (Vector2) {SCREENWIDTH/5, newGameBtn.origin.y + 25};
	exitBtn.border = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 40, 25};

	backBtn.origin = (Vector2) {(Vector2){SCREENWIDTH - MARGIN * 3, SCREENHEIGHT - MARGIN * 3}};
	backBtn.border = (Rectangle) {backBtn.origin.x - 20, backBtn.origin.y - BTNPADDING, 100, 40 + BTNPADDING * 2};
	
	for (int i=0; i<HUBNUMBTNS; i++) {
		if (i == HUBNUMBTNS - 1) {
			hubBtn[i].origin = (Vector2) { MARGIN, SCREENHEIGHT - MARGIN * 2};
			hubBtn[i].border = (Rectangle) { hubBtn[i].origin.x - 20, hubBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
		}
		else {
			hubBtn[i].origin = (Vector2) { MARGIN, MARGIN + SBARHEIGHT + 60 * i };
			hubBtn[i].border = (Rectangle) { hubBtn[i].origin.x - 20, hubBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
		}
	}
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
			if (alphaChannel[1] < 1.0f) {
				alphaChannel[0] += 0.005f;
				alphaChannel[1] += 0.005f;
			}
			else {
				AlphaWaveAnim(alphaChannel[0], 1.0f, 0.5f, 0.006f, increasing);
			}
			
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				screenTimer.Reset();
				currentScreen = MAINMENU;
			}
		} break;

		case MAINMENU: {
			AlphaWaveAnim(alphaChannel[0], 1.0f, 0.5f, 0.006f, increasing);
			
			if (ptxTimer.GetCounter() <= FPS*10) {
				ptxTimer.Run();
			}
			else {
				ptxTimer.Reset();
			}
			
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				switch (btnHovered) {
					case NEWGAMEBTN: {
						for (int i=0; i<sizeof(alphaChannel); i++) {
							alphaChannel[i] = 0.0f;
						}
						currentScreen = INTRO;
					} break;
	
					case EXITBTN: {
						CloseWindow();
					} break;
				}
			}
		} break;

		case INTRO: {
			AlphaLinearAnim(alphaChannel[0], 1.0f, 0.006f, true);
			screenTimer.Run();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || screenTimer.GetCounter() > 6 * FPS) {
				screenTimer.Reset();
				currentScreen = HUB;
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
			DrawTexture(logo, SCREENWIDTH/2 - logo.width/2, SCREENHEIGHT/2 - logo.height/2, WHITE);
		} break;
		
		case TITLE: {
			if (alphaChannel[1] < 1.0f) {
				DrawTexture(titleGlow, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[0]) );
				DrawTexture(titleCard, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[1]) );
			}
			else {	
				DrawTexture(titleGlow, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[0]) );
				DrawTexture(titleCard, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, WHITE);
				DrawTextEx(sagaFont, "<click anywhere>", (Vector2){SCREENWIDTH/2 - 80, SCREENHEIGHT/2}, 30, 0, ColorAlpha(WHITE, alphaChannel[0]));
			}
		} break;

		case MAINMENU: {
			PTXStars(starPtx, starPtxPos, starPtxColor, ptxTimer.GetCounter());

			DrawTexture(titleGlow, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[0]) );
			DrawTexture(titleCard, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, WHITE);
					
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

		case INTRO: {
			DrawTextEx(sagaFont, "Intro text block blah dee blah dee blah\nhello how are you woohoo you are player John Doe",
					(Vector2){MARGIN * 3, SCREENHEIGHT/2 - 50}, MAINMENUFONTSIZE, 0, ColorAlpha(WHITE, alphaChannel[0]) );	
		} break;

		case HUB: {
			DrawStatusBar(sbar);
			
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
			DrawStatusBar(sbar);

			DrawRectangle(MARGIN, SBARHEIGHT + MARGIN, SCREENWIDTH - MARGIN * 5, SCREENHEIGHT - MARGIN * 3, (Color){3, 3, 3, 255} );
			DrawRectangleLines(MARGIN, SBARHEIGHT + MARGIN, SCREENWIDTH - MARGIN * 5, SCREENHEIGHT - MARGIN * 3, WHITE);

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

