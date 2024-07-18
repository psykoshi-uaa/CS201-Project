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

void DrawStatusBar(Vector2* sbar) {
	DrawRectangleLinesEx((Rectangle) {0, 0, SCREENWIDTH, SBARHEIGHT}, 3, WHITE);

	for (int i=0; i<SBARNUMSEGS; i++) {
		DrawLine(SBARSEG[i], 0, SBARSEG[i], SBARHEIGHT, WHITE);
	}

	DrawTextEx(sagaFont, "PILOT: xyz", sbar[0], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "CURRENCY: xyz", sbar[1], SBARFONTSIZE, 0, WHITE);
	DrawTextEx(sagaFont, "TIME LEFT TIL REPO: xyz", sbar[2], SBARFONTSIZE, 0, WHITE);
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

