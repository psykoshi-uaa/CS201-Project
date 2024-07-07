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

void Player::getSkills(int& Piloting, int& Repair, int& Bartering) {
	Piloting = piloting;
	Repair = repair;
	Bartering = bartering;
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
float WaveAnim(float val, float dur, float scale) {
	float b = dur*3.14159;
	return (scale * pow(sin(val/b), 2) + 1.2);
}