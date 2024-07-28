#include "include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <cmath>
#include <string>

//declaring structs and other init stuff
Texture2D titleCard = { 0 };
Texture2D titleGlow = { 0 };
Texture2D titleUnderline = { 0 };
Texture2D logo = { 0 };
Texture2D particle = { 0 };
Texture2D hubBase = { 0 };
Texture2D gameOver = { 0 };
Texture2D gameOver2 = { 0 };
Font sagaFont = { 0 };
Player pilot;

static Vector2 sbar[SBARNUMSEGS+1];
static PTXstarmanager ptxStar;
static Sun sun;
static Planet planet[NUMPLANETS];
static HubPort hubPort(5, 125);
static Ship ship(hubPort.GetPos());

static SubMenu leftSideMenu(true);
static SubMenu rightSideMenu(false);
static GUIbtn hubBtn[HUBNUMBTNS];
static GUIbtn newGameBtn = { 0 };
static GUIbtn exitBtn = { 0 };
static GUIbtn backBtn = { 0 };
static GUIbtn missionBtn[NUMMISSIONS];
static Timer screenTimer;
static Timer animTimer[10];
static int shipDest = -1,
	   shootingStarStage = 0;
static float alphaChannel[NUMALPHACHANNELS];

//function prototypes
void DrawStatusBar(Player, Vector2*, float);
void DrawBtnSelected(Rectangle, int);
void DrawMainBtns(GUIbtn*);
void DrawAndUpdateSolarSystem(Sun, Player, Planet*, HubPort&, bool, Texture2D);
void ShootingStar(float, float, int&);
float AlphaWaveAnim(float, float, float);
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

	//Until the window is closed, draw and update the game
	while (!WindowShouldClose()) {
		UpdateAndDrawCurrentScreen();
		ButtonCollisionAndClick();
	}

	//Unlaod all images and fonts used.
	UnloadTexture(titleCard);
	UnloadTexture(titleGlow);
	UnloadTexture(titleUnderline);
	UnloadTexture(logo);
	UnloadTexture(hubBase);
	UnloadTexture(gameOver);
	UnloadTexture(gameOver2);
	UnloadFont(sagaFont);

	CloseWindow();

	return 0;
}


//-------------------------------------------------------------------------------
//			initializations
//-------------------------------------------------------------------------------
static void InitGame() {
	SetTargetFPS(FPS);

	//Load all images and fonts
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Starcaller");
	titleCard	= LoadTexture("resources/title.png");
	titleGlow	= LoadTexture("resources/title_glow.png");
	titleUnderline	= LoadTexture("resources/title_ship.png");
	logo 		= LoadTexture("resources/logo.png");
	hubBase		= LoadTexture("resources/hub_base.png");
	gameOver	= LoadTexture("resources/game_over.png");
	gameOver2	= LoadTexture("resources/game_over2.png");
	sagaFont	= LoadFontEx("resources/saga.ttf", 72, NULL, 0);

	//initializations of variables
	currentScreen = LOGO;

	btnHovered = NOBTN;
	screenTimer.Reset();
	alphaChannel[0] = 0.0f;
	alphaChannel[1] = -0.5f;

		//prepare statusbar dimensions
	float sbarH = 5;
	sbar[0] = (Vector2) {15, sbarH};
	sbar[1] = (Vector2) {SBARSEG[0] + 15, sbarH};
	sbar[2] = (Vector2) {SBARSEG[1] + 15, sbarH};
	sbar[3] = (Vector2) {SBARSEG[2] + 15, sbarH};

		//prepare new game button dimensions
	newGameBtn.origin = (Vector2) {SCREENWIDTH/5, SCREENHEIGHT - SCREENHEIGHT/4};
	newGameBtn.border = (Rectangle) {newGameBtn.origin.x, newGameBtn.origin.y, 100, 25};
		//prepare exit game button dimensions
	exitBtn.origin = (Vector2) {SCREENWIDTH/5, newGameBtn.origin.y + 25};
	exitBtn.border = (Rectangle) {exitBtn.origin.x, exitBtn.origin.y, 40, 25};
	
		//prepare Status, Interface, and Giveup button dimensions and origins
	hubBtn[0].origin = (Vector2) { SCREENWIDTH - HUBBTNWIDTH + 20, MARGIN + SBARHEIGHT + 80};
	hubBtn[0].border = (Rectangle) { hubBtn[0].origin.x - 20, hubBtn[0].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	hubBtn[1].origin = (Vector2) { MARGIN * 2, MARGIN + SBARHEIGHT + 80};
	hubBtn[1].border = (Rectangle) { hubBtn[1].origin.x - 20, hubBtn[1].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	hubBtn[2].origin = (Vector2) { MARGIN * 2, SCREENHEIGHT - MARGIN * 2};
	hubBtn[2].border = (Rectangle) { hubBtn[2].origin.x - 20, hubBtn[2].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };

		//prepare interface button origins and dimensions
	for (int i=0; i<NUMMISSIONS; i++) {
		missionBtn[i].origin = (Vector2) { SCREENWIDTH - (SCREENWIDTH / 6.5 ), (float)(SCREENHEIGHT / 4 + (i * 125)) };
		missionBtn[i].border = (Rectangle) { missionBtn[i].origin.x - 20, missionBtn[i].origin.y - BTNPADDING, HUBBTNWIDTH - 20, HUBBTNHEIGHT - 2 };
	}

		//create market buttons for hub port
	hubPort.GenerateMarket(missionBtn);
	
		//create mission buttons per planet
	int randPlanet = GetRandomValue(0, NUMPLANETS);
	for (int i=0; i<NUMPLANETS; i++) {
		if (i == randPlanet) {
			planet[i].GenerateMissions(missionBtn, true);
		}
		else {
			planet[i].GenerateMissions(missionBtn, false);
		}
	}

		//set ship to the sun - wanted to make origin set to the hub port but position of each planet updates after the timer starts running in update and draw, aka after this function.
	ship.SetPosition((Vector2) { SCREENWIDTH / 2, SCREENHEIGHT / 2 });
}


//-------------------------------------------------------------------------------
//			update and draw screen
//-------------------------------------------------------------------------------
static void UpdateAndDrawCurrentScreen(){
		//shooting stars
	int shootingStarChance = GetRandomValue(0, 5000);

		//raylib begin drawing screen
	BeginDrawing();
		//set background to black
	ClearBackground(BLACK);

		//run the star particle system
	ptxStar.LifeCycle();

		//run the shooting star function based on shootingStarChance and if the shooting star is not currently running.
	if (shootingStarChance == 1 && shootingStarStage == -1) {
		shootingStarStage = 0; 
	}
	ShootingStar(SCREENWIDTH, SCREENHEIGHT, shootingStarStage);
	
		//Switch what happens based on the current screen________________
	switch (currentScreen)
	{
		case LOGO: {
			//Mort Corp display on exe startup
			screenTimer.Run();
				//if 3 seconds pass or the mouse left button is pressed - continue to TITLE screen
			if (screenTimer.Wait(3) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				screenTimer.Reset();
				animTimer[0].Reset();
				currentScreen = TITLE;
			}

			//draw the image
			DrawTexture(logo, SCREENWIDTH/2 - logo.width/2, SCREENHEIGHT/2 - logo.height/2, WHITE);
		} break;
		
		case TITLE: {
			//Title card display and "click anywhere" and run an animation timer that is necessary for the pulsing galaxy to fade in and out
			animTimer[0].Run();
			alphaChannel[0] = AlphaWaveAnim(animTimer[0].GetCounter(), 1, 0.5);
			
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				screenTimer.Reset();
				currentScreen = MAINMENU;
			}

			//draw the title card image and the glowing galaxy behind title, as well as the click anywhere text
			if (alphaChannel[1] < 1.0f) {
				DrawTexture(titleGlow, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[0]) );
				DrawTexture(titleCard, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[1]) );
			}
			else {	
					//once the title is fully faded in , queue click anywhere
				DrawTexture(titleGlow, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[0]) );
				DrawTexture(titleCard, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, WHITE);
				DrawTextEx(sagaFont, "<click anywhere>", (Vector2){SCREENWIDTH/2 - 80, SCREENHEIGHT/2}, 30, 0, ColorAlpha(WHITE, alphaChannel[0]));
			}
		} break;

		case MAINMENU: {
			//same animation and title as TITLE but this time new game and exit game are drawn and handled
			animTimer[0].Run();
			alphaChannel[0] = AlphaWaveAnim(animTimer[0].GetCounter(), 1, 0.5);

				//draw the title
			DrawTexture(titleGlow, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, ColorAlpha(WHITE, alphaChannel[0]) );
			DrawTexture(titleCard, SCREENWIDTH/2 - titleCard.width/2, SCREENHEIGHT/5, WHITE);
					
				//based on which button btnHovered is equal to - draw them as white or blue
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
			//fade in intro text
			AlphaLinearAnim(alphaChannel[0], 1.0f, 0.006f, true);
			screenTimer.Run();
				//if mouse is pressed after 1 second or 6 seconds pass - switch to HUB screen
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && alphaChannel[0] > 0.5f ) {
				currentScreen = HUB;
			}

			//draw the text
			DrawTextEx(sagaFont, "Welcome back to life, pilot. We (Mort Corp) were generous enough to bring you back from the dead.\n\nYour last legs were destroyed beyond repair so we changed them out for you, generous, we know!\n\nNow prove to us that you are grateful by paying them off. What? You didn't ask for them? Too bad!\n\nYou have until the next planetary allignment to do so or we will - Take. Them. Back...",
					(Vector2){MARGIN * 3, SCREENHEIGHT/2 - 50}, MAINMENUFONTSIZE, 0, ColorAlpha(WHITE, alphaChannel[0]) );	
		} break;

		case HUB: {
			//this is the primary screen where all of the  magic happens
			DrawAndUpdateSolarSystem(sun, pilot, planet, hubPort, true, hubBase);

				//if the mouse is right clicked over a planet set that planet as the ships destination
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
					//if the planet hubPort is clicked set ship destination to -1
				if (CheckCollisionPointCircle(GetMousePosition(), hubPort.GetPos(), hubPort.GetRadius() + 5) ) {
					shipDest = -1;
				}
					// otherwise set shipDest to the planets index number
				else {
					for (int i=0; i<NUMPLANETS; i++) {
						if (CheckCollisionPointCircle(GetMousePosition(), planet[i].GetPos(), planet[i].GetRadius()) ) {
							shipDest = i;
						}
					}
				}
			}

				//if the player time remaining variable runs out switch to gameover screen
			if (pilot.getTimeRemaining() <= 0) {
				currentScreen = GAMEOVER;
				animTimer[0].SetCounter(40);
				animTimer[1].Reset();
			}
				//otherwise decrease the timer gradually
			else {
				pilot.loseTimeGradually();
			}

				//if the player pays off all of their debt then switch to the success screen
			if (pilot.getDebt() >= 0) {
				currentScreen = SUCCESS;
			}
				
				//run the mission handler for only the planet at the index of shipDest 
			for (int i=0; i<NUMPLANETS; i++) {
				planet[i].MissionHandler(pilot, ship, true);
			}
			
				//update and draw the players ship.
			if (shipDest >= 0) {
				ship.UpdateDestination(planet[shipDest].GetPos());
				ship.DrawSelf(planet[shipDest].GetRadius(), WHITE);

			//mission update and draw if the right side menu is activated and the ship is at it's destination
				if (rightSideMenu.GetActive() && ship.IsAtDestination(planet[shipDest].GetRadius()) ) {
					planet[shipDest].MissionHandler(pilot, ship, false);
				}
			}
			else {
					//update and draw the players ship if hubPort is the dest (it is not part of the planet array, so if shipDest is < 0, then do this)
				ship.UpdateDestination(hubPort.GetPos());
				ship.DrawSelf(hubPort.GetRadius(), WHITE);

					//run the hubports market handler function if the right side menu is activated and the ship is at it's destination
				if (rightSideMenu.GetActive() && ship.IsAtDestination(hubPort.GetRadius()) ) {
					hubPort.MarketHandler(pilot, ship);
				}
			}

				//Draw the status screen on the left hand side of the screen as long as the left menu is activated
			if (leftSideMenu.GetActive()) {
				std::string statusStr[] = { "Ship", "Weapon LVL:", "Cargo LVL:", "Gathering Tool LVL: ", "Overall Speed:" };
				std::string statusStats[] = { ship.getName(), std::to_string(pilot.weapon_upgrade_counter), std::to_string(pilot.reward_upgrade_counter), std::to_string(ship.getGatheringTool()), std::to_string(ship.getSpeed()) };
				int fontSize = 32;
				
				for (int i=0; i<5; i++) {
						//The length of the string needed to be measure first in order for a nicer looking centered look
					Vector2 len = MeasureTextEx(sagaFont, statusStr[i].c_str(), fontSize, 1);
					DrawTextEx(sagaFont, statusStr[i].c_str(), {150 - len.x / 2, (float)(SCREENHEIGHT/4) + (i * 50)}, fontSize, 1, WHITE);
					DrawTextEx(sagaFont, statusStats[i].c_str(), {SCREENWIDTH / 5 - 70, (float)(SCREENHEIGHT/4) + (i * 50)}, fontSize, 1, GREEN);
				}
			}
			
				//Draw the status bar, main buttons, and left and right submenus if they are active
			DrawStatusBar(pilot, sbar, pilot.getTimeRemaining());
			DrawMainBtns(hubBtn);
			rightSideMenu.UpdateAndDrawSelf();
			leftSideMenu.UpdateAndDrawSelf();
		} break;

		case GAMEOVER: {
			//Run timers that determine the position of the images drawn as they bob up and down
			animTimer[0].Run();
			animTimer[1].Run();
			alphaChannel[0] = AlphaWaveAnim(animTimer[0].GetCounter(), FPS * 5, 0.3f);
			alphaChannel[1] = AlphaWaveAnim(animTimer[1].GetCounter(), FPS * 5, 0.3f);
			
				//draw a guy floating and his torn off arm
			DrawTexture(gameOver, SCREENWIDTH/2 - gameOver.width/2, SCREENHEIGHT / 3 - (5 * alphaChannel[0]) - gameOver.height/2, WHITE);
			DrawTexture(gameOver2, SCREENWIDTH - SCREENWIDTH / 2.2, SCREENHEIGHT - SCREENHEIGHT / 1.3 - (5 * alphaChannel[1]), WHITE);
			
				//draw the text based on it's length in order to center the text
			std::string loseStr = "You ran out of time. Mort Corp has reclaimed the legs they loaned you at ALL costs.";
			Vector2 len = MeasureTextEx(sagaFont, loseStr.c_str(), MAINMENUFONTSIZE, 1);
			DrawTextEx(sagaFont, loseStr.c_str(), (Vector2){ SCREENWIDTH/2 - len.x / 2, SCREENHEIGHT - SCREENHEIGHT / 3 }, MAINMENUFONTSIZE, 1, WHITE);

				//if the mouse is pressed switch screen to retry
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				currentScreen = RETRY;
			}
		} break;

		case RETRY: {
			//same anim and picture as GAMEOVER
			animTimer[0].Run();
			animTimer[1].Run();
			alphaChannel[0] = AlphaWaveAnim(animTimer[0].GetCounter(), FPS * 5, 0.3f);
			alphaChannel[1] = AlphaWaveAnim(animTimer[1].GetCounter(), FPS * 5, 0.3f);

			DrawTexture(gameOver, SCREENWIDTH/2 - gameOver.width/2, SCREENHEIGHT / 3 - (5 * alphaChannel[0]) - gameOver.height/2, WHITE);
			DrawTexture(gameOver2, SCREENWIDTH - SCREENWIDTH / 2.2, SCREENHEIGHT - SCREENHEIGHT / 1.3 - (5 * alphaChannel[1]), WHITE);
			
				//draw the exit button
			if (btnHovered == EXITBTN) {
				DrawTextEx(sagaFont, "exit", exitBtn.origin, MAINMENUFONTSIZE, 1, BLUE);
			}
			else {
				DrawTextEx(sagaFont, "exit", exitBtn.origin, MAINMENUFONTSIZE, 1, WHITE);
			}

				//draw the credits
			Vector2 creditsOrigin = (Vector2) { SCREENWIDTH - SCREENWIDTH / 4, SCREENHEIGHT - SCREENHEIGHT / 4 };
			DrawTextEx(sagaFont, "Credits", creditsOrigin, MAINMENUFONTSIZE, 1, WHITE);
			DrawTextEx(sagaFont, "Calvin Michele", (Vector2){creditsOrigin.x, creditsOrigin.y + MAINMENUFONTSIZE * 2}, MAINMENUFONTSIZE, 1, WHITE);
			DrawTextEx(sagaFont, "Ethan Shalstrom", (Vector2){creditsOrigin.x, creditsOrigin.y + MAINMENUFONTSIZE * 3}, MAINMENUFONTSIZE, 1, WHITE);
			DrawTextEx(sagaFont, "Sheng Her", (Vector2){creditsOrigin.x, creditsOrigin.y + MAINMENUFONTSIZE * 4}, MAINMENUFONTSIZE, 1, WHITE);
		} break;

		case SUCCESS: {
			//draw the exit button
			if (btnHovered == EXITBTN) {
				DrawTextEx(sagaFont, "exit", exitBtn.origin, MAINMENUFONTSIZE, 1, BLUE);
			}
			else {
				DrawTextEx(sagaFont, "exit", exitBtn.origin, MAINMENUFONTSIZE, 1, WHITE);
			}
				
				//draw victory text
			std::string winStr = "You have succesfully payed off your artificial legs granted by Mort Corp!\n\nGood flying pilot.";
			Vector2 len = MeasureTextEx(sagaFont, winStr.c_str(), MAINMENUFONTSIZE, 1);
			DrawTextEx(sagaFont, winStr.c_str(), (Vector2){ SCREENWIDTH/2 - len.x / 2,SCREENHEIGHT/2 }, MAINMENUFONTSIZE, 1, WHITE);
			
				//draw credits
			Vector2 creditsOrigin = (Vector2) { SCREENWIDTH - SCREENWIDTH / 4, SCREENHEIGHT - SCREENHEIGHT / 4 };
			DrawTextEx(sagaFont, "Credits", creditsOrigin, MAINMENUFONTSIZE, 1, WHITE);
			DrawTextEx(sagaFont, "Calvin Michele", (Vector2){creditsOrigin.x, creditsOrigin.y + MAINMENUFONTSIZE * 2}, MAINMENUFONTSIZE, 1, WHITE);
			DrawTextEx(sagaFont, "Ethan Shalstrom", (Vector2){creditsOrigin.x, creditsOrigin.y + MAINMENUFONTSIZE * 3}, MAINMENUFONTSIZE, 1, WHITE);
			DrawTextEx(sagaFont, "Sheng Her", (Vector2){creditsOrigin.x, creditsOrigin.y + MAINMENUFONTSIZE * 4}, MAINMENUFONTSIZE, 1, WHITE);
		} break;
		
		default:break;
	}

	//raylib function to stop drawing to the screen
	EndDrawing();
}


//-------------------------------------------------------------------------------
//			button handling
//-------------------------------------------------------------------------------
static void ButtonCollisionAndClick() {
	//based on which screen currentScreen is set to check to see if any buttons are being collided with
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
				btnHovered = GIVEUPBTN;
			}
			else {
				btnHovered = NOBTN;
			}
		} break;

		case RETRY:
		case SUCCESS: {
			if (CheckCollisionPointRec(GetMousePosition(), exitBtn.border)) {
				btnHovered = EXITBTN;
			}
			else {
				btnHovered = NOBTN;
			}
		}

		default: break;
	}
	
	// if button clicked do whatever
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		switch (btnHovered) {
			case NEWGAMEBTN: {
				for (int i=0; i<NUMALPHACHANNELS; i++) {
					alphaChannel[i] = 0.0f;
				}
				screenTimer.Reset();
				btnHovered = NOBTN;
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