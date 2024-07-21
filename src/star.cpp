#include "../include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <ctime>
#include <cmath>


// ================================
//          Player Class
// ================================

//+++++ Getters +++++

std::string Player::getName() {
	return name;
}

int Player::getMoney() {
	return money;
}

int Player::getDebt() {
	return debt;
}
int Player::getTimeRemaining(){
	return timeRemaining;
}

/*
int Player::getHP() {
	return HP;
}
						//HP AND SP NOT NECESSARY AT THE MOMENT
int Player::getSP() {
	return SP;
}
*/
/*
int Player::getPilot(){
	return piloting;
}

int Player::getRepair(){  // SKILLS NOT NECESSARY AT THE MOMENT
	return repair;
}

int Player::getBarter(){
	return bartering;
}
*/

//+++++ Setters +++++

void Player::setName(std::string new_name)
{
	name = new_name;
}
void Player::setMoney(int money)
{
	money = money;
}
void Player::setDebt(int debt)
{
	debt = debt;
}
void Player::setHP(int HP)
{
	HP = HP;
}
void Player::setTimeRemaining(int time)
{
	timeRemaining = time;
}

//++++++++ METHODS +++++++

// add money to player account
void Player::addMoney(int money_to_add)
{
	money += money_to_add;
}
// add money to negative debt total
void Player::payDebt(int money_paid)
{
	debt += money_paid;
}
void Player::loseTime(int time_lost)
{
	timeRemaining -= time_lost;
}


//-------------------------------------------------------------------------------
//			draw functions
//-------------------------------------------------------------------------------
void DrawBtnSelected(Rectangle rct, int btn) {
	if (btnHovered == btn) {
		DrawRectangleRec(rct, DARKBLUE);
	}
}

void DrawStatusBar(Player pilot, Vector2* sbar) {
	DrawRectangleLinesEx((Rectangle) {0, 0, SCREENWIDTH, SBARHEIGHT}, 3, WHITE);

	for (int i=0; i<SBARNUMSEGS; i++) {
		DrawLine(SBARSEG[i], 0, SBARSEG[i], SBARHEIGHT, WHITE);
	}

	DrawTextEx(sagaFont, "PILOT: ", sbar[0], SBARFONTSIZE, 0, WHITE);
//	DrawTextEx(sagaFont, pilot.getName(), (Vector2) {sbar[0].x + 50, sbar[0].y}, SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "CURRENCY: ", sbar[1], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "TIME LEFT TIL REPO: ", sbar[2], SBARFONTSIZE, 0, WHITE);
}

void DrawMainBtns(GUIbtn *hubBtn) {
	for (int i=0; i<HUBNUMBTNS; i++) {
		DrawBtnSelected(hubBtn[i].border, i + 3);
		DrawRectangleLinesEx(hubBtn[i].border, 2, WHITE);
	}
	DrawTextEx(sagaFont, "Mission Board", hubBtn[0].origin, HUBMAINFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "Status", hubBtn[1].origin, HUBMAINFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "Market", hubBtn[2].origin, HUBMAINFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "Give Up", hubBtn[3].origin, HUBMAINFONTSIZE, 0, WHITE);
}

void DrawStatusScreen(Font sagaFont) {
		Vector2 menuPos[] = {
			(Vector2) { SCREENWIDTH / 5, SCREENHEIGHT / 9 },
			(Vector2) { SCREENWIDTH / 2 + SCREENWIDTH / 10, SCREENHEIGHT / 9 },
			(Vector2) { SCREENWIDTH / 2 + SCREENWIDTH / 10, SCREENHEIGHT / 2 }
		};
		
		Rectangle menuBor[] = {
			(Rectangle) { menuPos[0].x, menuPos[0].y, SCREENWIDTH/3, SCREENHEIGHT/1.2 },	
			(Rectangle) { menuPos[1].x, menuPos[1].y, SCREENWIDTH/3, SCREENHEIGHT/3   },	
			(Rectangle) { menuPos[2].x, menuPos[2].y, SCREENWIDTH/3, SCREENHEIGHT/2.5 }
		};
 
        //Ship
	DrawRectangleLinesEx(menuBor[0], 2, WHITE);

        DrawTextEx(sagaFont, "Ship", {menuPos[0].x + MARGIN, menuPos[0].y + 50}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Weapon LVL:", {menuPos[0].x + MARGIN, menuPos[0].y + 100}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Shield LVL:", {menuPos[0].x + MARGIN, menuPos[0].y + 150}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Gathering Tool LVL:", {menuPos[0].x + MARGIN, menuPos[0].y + 200}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Overall Speed:", {menuPos[0].x + MARGIN, menuPos[0].y + 250}, HUBMAINFONTSIZE, 1, WHITE);
   	    
	//Pilot
	DrawRectangleLinesEx(menuBor[1], 2, WHITE);

        DrawTextEx(sagaFont, "Pilot: XYZ", {menuPos[1].x + MARGIN, menuPos[1].y + 50}, HUBMAINFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Registered Pilot Under", {menuPos[1].x + MARGIN, menuPos[1].y + 100}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "the SSE Administration", {menuPos[1].x + MARGIN, menuPos[1].y + 150}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "License Valid Until: 04/14/2248", {menuPos[1].x + MARGIN, menuPos[1].y + 200}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Birthdate:           09/12/2223", {menuPos[1].x + MARGIN, menuPos[1].y + 250}, HUBSUBFONTSIZE, 1, WHITE);

        //Debt
	DrawRectangleLinesEx(menuBor[2], 2, WHITE);

        DrawTextEx(sagaFont, "This pilot is to pay of their debt to MORT CORP by", {menuPos[2].x + MARGIN, menuPos[2].y + 50}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "08/28/2242", {menuPos[2].x + MARGIN, menuPos[2].y + 100}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "for the loan of borrowed limbs or shall forfeit their life", {menuPos[2].x + MARGIN, menuPos[2].y + 150}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "and body for scientific and good purposes.", {menuPos[2].x + MARGIN, menuPos[2].y + 200}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "MORT CORP is protected under the Right to", {menuPos[2].x + MARGIN, menuPos[2].y + 250}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Dismemberment Act and the Right to Slay Act.", {menuPos[2].x + MARGIN, menuPos[2].y + 300}, HUBSUBFONTSIZE, 1, WHITE);
        DrawTextEx(sagaFont, "Debt owed to MORT CORP: Debt", {menuPos[2].x + MARGIN, menuPos[2].y + 350}, HUBSUBFONTSIZE, 1, WHITE);
}


//-------------------------------------------------------------------------------
//			menu
//-------------------------------------------------------------------------------
SubMenu::SubMenu(bool leftSide) {
	float menuWidth = SCREENWIDTH / 5,
	      menuHeight = SCREENHEIGHT / 1.5;

	if (leftSide) {
		pos = (Vector2) { 0 - menuWidth, SCREENHEIGHT / 5 };
		dim = (Vector2) { menuWidth, menuHeight };
		min_x = pos.x;
		max_x = pos.x + menuWidth;
	}
	else {
		pos = (Vector2) { SCREENWIDTH, SCREENHEIGHT / 5 };
		dim = (Vector2) { menuWidth, menuHeight };
		min_x = pos.x - menuWidth;
		max_x = pos.x;
	}

	isLeftSide = leftSide;
	border = (Rectangle){ pos.x, pos.y, dim.x, dim.y };
	isActive = false;
}

void SubMenu::HandleActivation() {
	if (isActive == false) {
		isActive = true;
	}
	else {
		isActive = false;
	}
}

void SubMenu::UpdateAndDrawSelf() {
	if (isActive && isLeftSide) {
		pos.x = max_x;
		DrawRectangleLinesEx(border, 2, WHITE);
	}
	else if (isActive && !isLeftSide) {
		pos.x = min_x;
		DrawRectangleLinesEx(border, 2, WHITE);
	}
	else if (!isActive && isLeftSide) {
		pos.x = min_x;
	}
	else {
		pos.x = max_x;
	}

	border = (Rectangle){ pos.x, pos.y, dim.x, dim.y };
}

bool SubMenu::GetActive() {
	return isActive;
}


//-------------------------------------------------------------------------------
//			code utility
//-------------------------------------------------------------------------------
float  Timer::GetCounter() {
	return frameCounter;
}

void Timer::Reset() {
	frameCounter = 0;
}

void Timer::Run() {
	frameCounter++;
}

bool Timer::Wait(double mark){
	if (frameCounter > FPS * mark) {
		return true;
	}
	return false;
}


Dice::Dice() {
	static bool seeded = false;
	if (!seeded) {
		//std::srand(std::time(nullptr)); 	obsolete, switched to uniform_int_distribution
		seeded = true;
	}
}

int Dice::rollD6(int numRolls = 0) {
	int total = 0;
	for (int i=0; i<numRolls; ++i) {
		//total += std::rand() % 6 + 1;		obsolete, switched to uniform_int_distribution
	}
	return total;
}


float GetDist(Vector2 x1y1, Vector2 x2y2) {
	return sqrt(pow(x2y2.x - x1y1.x, 2) + pow(x2y2.y - x1y1.y, 2) );
}


//-------------------------------------------------------------------------------
//			animation scalers
//-------------------------------------------------------------------------------
void AlphaWaveAnim(float& counter, float max, float min, float increment, bool& increasing) {
	if (counter < max && increasing == true) {
		counter += increment;
	}
	else {
		increasing = false;
	}

	if (counter > min && increasing == false){
		counter -= increment;
	}
	else {
		increasing = true;
	}
}

void AlphaLinearAnim(float& counter, float goal, float increment, bool increase) {
	if (increase == false && counter > goal) {
		counter -= increment;
	}
	else if (increase == true && counter < goal) {
		counter += increment;
	}
}

