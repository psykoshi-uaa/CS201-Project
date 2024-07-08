#include <ctime>
#include <cstdlib> 
#include "../lib/includes/star.h"

 
//-------------------------------------------------------------------------------
//			player, ship, and mission classes
//-------------------------------------------------------------------------------
std::string Player::getName() {
	return name;
}

int Player::getMoney() {
	return money;
}

int Player::getDebt() {
	return debt;
}

int Player::getHP() {
	return HP;
}

int Player::getSP() {
	return SP;
}

int Player::getPilot(){
	return piloting;
}

int Player::getRepair(){
	return repair;
}

int Player::getBarter(){
	return bartering;
}


//-------------------------------------------------------------------------------
//			code utility classes
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
		std::srand(std::time(nullptr));
		seeded = true;
	}
}

int Dice::rollD6(int numRolls = 0) {
	int total = 0;
	for (int i=0; i<numRolls; ++i) {
		total += std::rand() % 6 + 1;
	}
	return total;
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
//			particle animations (PTX = particles)
//-------------------------------------------------------------------------------
void PTXStars(int * starPtx, Vector2 * starPtxPos, Color * starPtxColor, float counter){
	for (int i=0; i<MAXSTARPTX; i++) {
		if (starPtx[i] == 0 ) {
			int chance = std::rand() % (FPS*FPS);
			
			if (chance == 1) {
				int colorChance = std::rand() % 3;
				switch (colorChance) {
					case 0: starPtxColor[i] = {106, 70, 160, 255};
							break;
					
					case 1: starPtxColor[i] = {160, 100, 72, 255};
							break;
							
					case 2: starPtxColor[i] = {54, 67, 85, 255};
							break;
					
					default: break;
				}
				starPtx[i] = 1;
				starPtxPos[i] = {float(std::rand()%SCREENWIDTH), float(std::rand()%SCREENHEIGHT)};
			}
		}
		else if (starPtx[i] > 0 && starPtx[i] < FPS) {
			if (starPtx[i] % 3 == 0) {
				DrawTextEx(GetFontDefault(), "+", starPtxPos[i], 10, 0, starPtxColor[i]);
			}
			else if (starPtx[i] % 3 == 1) {
				DrawTextEx(GetFontDefault(), "*", starPtxPos[i], 10, 0, starPtxColor[i]);
			}
			else {
				DrawTextEx(GetFontDefault(), "x", starPtxPos[i], 10, 0, starPtxColor[i]);
			}
			
			if (int(counter) % FPS == 0) {
				starPtx[i]++;
			}
		}
		else {
			starPtx[i] = 0;
		}
	}
}

//