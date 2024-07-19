#include "include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <cmath>

//declaring structs and other init stuff
Texture2D titleCard = { 0 };
Texture2D titleGlow = { 0 };
Texture2D titleUnderline = { 0 };
Texture2D logo = { 0 };
Texture2D particle = { 0 };
Texture2D hubBase = { 0 };
Font sagaFont = { 0 };
Vector2 sbar[SBARNUMSEGS+1];
PTXstarmanager ptxStar;
Sun sun;
Planet planet[NUMPLANETS];
Planet hubPlanet;
Ship ship;
Mission mission[NUMMISSIONS] {
	Mission("Odd Jobs", 400, 1, 0.1, (Rectangle) {0, 0, 0, 0} ),
	Mission("Gather", 1200, 3, 3.0, (Rectangle) {0, 0, 0, 0} ),
	Mission("Salvage", 5000, 3, 7.0, (Rectangle) {0, 0, 0, 0} ),
	Mission("Bounty", 34000, 14, 30.0,  (Rectangle) {0, 0, 0, 0} ),
	Mission("Raid", 100000, 28, 90.0, (Rectangle) {0, 0, 0, 0} ),
};

static GUIbtn hubBtn[HUBNUMBTNS];
static GUIbtn boardBtn[BOARDNUMBTNS];
static GUIbtn newGameBtn = { 0 };
static GUIbtn exitBtn = { 0 };
static GUIbtn backBtn = { 0 };
static GUIbtn missionBtn[NUMMISSIONS];
static Timer screenTimer;
static Timer animTimer;
static float alphaChannel[NUMALPHACHANNELS];
static int shipDest;
static bool increasing = true;

//function prototypes
void DrawStatusBar(Vector2*);
void DrawStatusScreen(Font);
void DrawBtnSelected(Rectangle, int);
void DrawMainBtns(GUIbtn*);
void DrawAndUpdateSolarSystem(Sun, Planet*, Planet&, bool);
void AlphaWaveAnim(float&, float, float, float, bool&);
void AlphaLinearAnim(float&, float, float, bool);

static void InitGame();
static void UpdateAndDrawCurrentScreen();
static void ButtonCollisionAndClick();

//declaring global
GameScreen currentScreen = LOGO;
Buttons btnHovered = NOBTN;

//-------------------------------------------------------------------------------
//			main program
//-------------------------------------------------------------------------------
int main(){
	InitGame();

	ToggleFullscreen();

	while (!WindowShouldClose()) {
		UpdateAndDrawCurrentScreen();
		ButtonCollisionAndClick();
	}

	UnloadTexture(titleCard);
	UnloadTexture(titleGlow);
	UnloadTexture(titleUnderline);
	UnloadTexture(logo);
	UnloadTexture(hubBase);
	UnloadFont(sagaFont);

	CloseWindow();

	return 0;
}


//-------------------------------------------------------------------------------
//			initializations
//-------------------------------------------------------------------------------
static void InitGame() {
	SetTargetFPS(FPS);

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Starcaller");
	titleCard	= LoadTexture("resources/title.png");
	titleGlow	= LoadTexture("resources/title_glow.png");
	titleUnderline	= LoadTexture("resources/title_ship.png");
	logo 		= LoadTexture("resources/logo.png");
	hubBase		= LoadTexture("resources/hub_base.png");
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

	for (int i=0; i<BOARDNUMBTNS; i++) {
		boardBtn[i].origin = (Vector2) { MARGIN, };
	}

	for (int i=0; i<NUMMISSIONS; i++) {
		missionBtn[i].origin = (Vector2) { MARGIN * 14, (MARGIN * 4) * i + MARGIN * 3 };
		missionBtn[i].border = (Rectangle) { missionBtn[i].origin.x - 20, missionBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
		mission[i].setButton(missionBtn[i].border);
	}
}


//-------------------------------------------------------------------------------
//			update and draw screen
//-------------------------------------------------------------------------------
static void UpdateAndDrawCurrentScreen(){
	BeginDrawing();

	ClearBackground(BLACK);

	ptxStar.LifeCycle();

	switch (currentScreen)
	{
		case LOGO: {
			//update
			screenTimer.Run();

			if (screenTimer.Wait(3) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				screenTimer.Reset();
				animTimer.Reset();
				currentScreen = TITLE;
			}

			//draw
			DrawTexture(logo, SCREENWIDTH/2 - logo.width/2, SCREENHEIGHT/2 - logo.height/2, WHITE);
		} break;
		
		case TITLE: {
			//update
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

			//draw
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
			//update
			AlphaWaveAnim(alphaChannel[0], 1.0f, 0.5f, 0.006f, increasing);

			//draw
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
			//update
			AlphaLinearAnim(alphaChannel[0], 1.0f, 0.006f, true);
			screenTimer.Run();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || screenTimer.GetCounter() > 6 * FPS) {
				screenTimer.Reset();
				currentScreen = HUB;
			}

			//draw
			DrawTextEx(sagaFont, "Intro text block blah dee blah dee blah\nhello how are you woohoo you are player John Doe",
					(Vector2){MARGIN * 3, SCREENHEIGHT/2 - 50}, MAINMENUFONTSIZE, 0, ColorAlpha(WHITE, alphaChannel[0]) );	
		} break;

		case HUB: {
			DrawAndUpdateSolarSystem(sun, planet, hubPlanet, true);

			//update
			ship.UpdateDestination(planet[shipDest].GetPos());
			
			for (int i=0; i<NUMPLANETS; i++) {
				if (CheckCollisionPointCircle(GetMousePosition(), planet[i].GetPos(), planet[i].GetRadius())
				&& IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) ) {
					shipDest = i;
				}
			}

			//draw
			ship.DrawSelf(planet[shipDest].GetRadius(), WHITE);

			DrawTextureV(hubBase, hubPlanet.GetPos(), WHITE);

			DrawStatusBar(sbar);
			DrawMainBtns(hubBtn);
		} break;

		case BOARD: {
			//mission update and draw
			for (int i=0; i<NUMMISSIONS; i++) {
				if (mission[i].IsClicked() && mission[i].getCurrentCooldown() == 0) {
					mission[i].startCooldown();
				}
				
				if (mission[i].getCurrentCooldown() > 0) {
					mission[i].updateTimer(0.001);
				}
				mission[i].DrawButton();
			}

			//update
			//draw
			DrawStatusBar(sbar);
			DrawMainBtns(hubBtn);
		} break;
		
		case MARKET: {

			DrawStatusBar(sbar);
			DrawMainBtns(hubBtn);
		} break;
		
		case PLAYERSHEET: {
			//update
			//draw
			DrawStatusScreen(sagaFont);
			
			DrawStatusBar(sbar);

			DrawStatusBar(sbar);
			DrawMainBtns(hubBtn);
		} break;

		default:break;
	}

	EndDrawing();
}


//-------------------------------------------------------------------------------
//			button handling
//-------------------------------------------------------------------------------
static void ButtonCollisionAndClick() {
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

		case PLAYERSHEET:
		case BOARD:
		case MARKET:
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
				btnHovered = MAPBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[4].border)) {
				btnHovered = GIVEUPBTN;
			}
			else {
				btnHovered = NOBTN;
			}
		} break;

		default: break;
	}
	
	// if button clicked do whatever
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		switch (btnHovered) {
			case NEWGAMEBTN: {
				for (int i=0; i<NUMALPHACHANNELS; i++) {
					alphaChannel[i] = 0.0f;
				}
				currentScreen = INTRO;
			} break;

			case EXITBTN: {
				CloseWindow();
			} break;
						
			case BOARDBTN: {
				currentScreen = BOARD;
			} break;
			
			case STATUSBTN: {
				currentScreen = PLAYERSHEET;
			} break;

			case MAPBTN: {
				currentScreen = HUB;
			} break;

			case GIVEUPBTN: {
				CloseWindow();
			} break;
			
			default: break;
		}
	}
}
