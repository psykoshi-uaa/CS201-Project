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

static Vector2 sbar[SBARNUMSEGS+1];
static PTXstarmanager ptxStar;
static Sun sun;
static Planet planet[NUMPLANETS];
static HubPort hubPort(15, 125);
static Ship ship(hubPort.GetPos());
static Player pilot;
static SubMenu leftSideMenu(true);
static SubMenu rightSideMenu(false);
static GUIbtn hubBtn[HUBNUMBTNS];
static GUIbtn boardBtn[BOARDNUMBTNS];
static GUIbtn newGameBtn = { 0 };
static GUIbtn exitBtn = { 0 };
static GUIbtn backBtn = { 0 };
static GUIbtn missionBtn[NUMMISSIONS];
static Timer screenTimer;
static Timer animTimer;
static int shipDest = -1,
	   shootingStarStage = 0;
static float alphaChannel[NUMALPHACHANNELS];
static bool increasing = true;

//function prototypes
void DrawStatusBar(Player, Vector2*);
void DrawStatusScreen(Font);
void DrawBtnSelected(Rectangle, int);
void DrawMainBtns(GUIbtn*);
void DrawAndUpdateSolarSystem(Sun, Planet*, HubPort&, bool, Texture2D);
void ShootingStar(float, float, int&);
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
	
	hubBtn[0].origin = (Vector2) { SCREENWIDTH - HUBBTNWIDTH + 20, MARGIN + SBARHEIGHT + 80};
	hubBtn[0].border = (Rectangle) { hubBtn[0].origin.x - 20, hubBtn[0].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	hubBtn[1].origin = (Vector2) { 0, MARGIN + SBARHEIGHT + 80};
	hubBtn[1].border = (Rectangle) { hubBtn[1].origin.x - 20, hubBtn[1].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	hubBtn[2].origin = (Vector2) { 0, MARGIN + SBARHEIGHT + 40};
	hubBtn[2].border = (Rectangle) { hubBtn[2].origin.x - 20, hubBtn[2].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	hubBtn[3].origin = (Vector2) { MARGIN, SCREENHEIGHT - MARGIN * 2};
	hubBtn[3].border = (Rectangle) { hubBtn[3].origin.x - 20, hubBtn[3].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };

	for (int i=0; i<BOARDNUMBTNS; i++) {
		boardBtn[i].origin = (Vector2) { MARGIN, MARGIN};
	}

	for (int i=0; i<NUMMISSIONS; i++) {
		missionBtn[i].origin = (Vector2) { SCREENWIDTH - (SCREENWIDTH / 7), (float)(SCREENWIDTH / 7 + (i * 125)) };
		missionBtn[i].border = (Rectangle) { missionBtn[i].origin.x - 20, missionBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	}
	
	for (int i=0; i<NUMPLANETS; i++) {
		planet[i].GenerateMissions(missionBtn);
	}
}


//-------------------------------------------------------------------------------
//			update and draw screen
//-------------------------------------------------------------------------------
static void UpdateAndDrawCurrentScreen(){
	int shootingStarChance = GetRandomValue(0, 1000);

	BeginDrawing();

	ClearBackground(BLACK);

	ptxStar.LifeCycle();

	if (shootingStarChance == 1 && shootingStarStage == -1) {
		shootingStarStage = 0; 
	}

	ShootingStar(SCREENWIDTH, SCREENHEIGHT, shootingStarStage);

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
			DrawTextEx(sagaFont, "Intro text block blah dee blah dee blah\nhello how are you woohoo you are pilot John Doe",
					(Vector2){MARGIN * 3, SCREENHEIGHT/2 - 50}, MAINMENUFONTSIZE, 0, ColorAlpha(WHITE, alphaChannel[0]) );	
		} break;

		case HUB: {
			DrawAndUpdateSolarSystem(sun, planet, hubPort, true, hubBase);

			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
				if (CheckCollisionPointCircle(GetMousePosition(), hubPort.GetPos(), hubPort.GetRadius() + 5) ) {
					shipDest = -1;
				}
				else {
					for (int i=0; i<NUMPLANETS; i++) {
						if (CheckCollisionPointCircle(GetMousePosition(), planet[i].GetPos(), planet[i].GetRadius()) ) {
							shipDest = i;
						}
					}
				}
			}

			if (shipDest >= 0) {
				ship.UpdateDestination(planet[shipDest].GetPos());
				ship.DrawSelf(planet[shipDest].GetRadius(), WHITE);

			//mission update and draw
				if (rightSideMenu.GetActive() && ship.IsAtDestination(planet[shipDest].GetRadius()) ) {
					planet[shipDest].MissionHandler(pilot);
				}
			}
			else {
				ship.UpdateDestination(hubPort.GetPos());
				ship.DrawSelf(hubPort.GetRadius(), WHITE);

				//MARKET GO HERE
			}
			
			DrawStatusBar(pilot, sbar);
			DrawMainBtns(hubBtn);
			rightSideMenu.UpdateAndDrawSelf();
			leftSideMenu.UpdateAndDrawSelf();
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

		case HUB: {
			if (CheckCollisionPointRec(GetMousePosition(), hubBtn[0].border)) {
				btnHovered = BOARDBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[1].border)) {
				btnHovered = STATUSBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[2].border)) {
				btnHovered = MARKETBTN;
			}
			else if (CheckCollisionPointRec(GetMousePosition(), hubBtn[3].border)) {
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
				rightSideMenu.HandleActivation();
			} break;

			case MARKETBTN: {
			} break;
			
			case STATUSBTN: {
				leftSideMenu.HandleActivation();
			} break;

			case GIVEUPBTN: {
				CloseWindow();
			} break;
			
			default: break;
		}
	}
}
