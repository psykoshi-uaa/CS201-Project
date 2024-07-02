#include <ctime>
#include <cstdlib> 
#include "star.h"


//player, ship, and mission classes
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



//code utility classes
int  Timer::GetCounter() {
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



/*backup
 *
 * Weapon::Weapon(std::string idType, std::string idModel) {
	model = idModel;
	type = idType;
	fullName = idType + " " + idModel;
	
	if (type == "low impact"){
		fireRate = 4.7;
		baseDamage = 0.25;
		damageScaling[0] = 1;
		damageScaling[1] = 0.7;
		damageScaling[2] = 0.1;
	} 
	
	else if (type == "high impact"){
		fireRate = 1.2; 
		baseDamage = 1.8;
		damageScaling[0] = 1;
		damageScaling[1] = 0.9;
		damageScaling[2] = 0.1;
	}

	else if (type == "laser"){
		fireRate = 2.1; 
		baseDamage = 3.7;
		damageScaling[0] = 1.4;
		damageScaling[1] = 0.7;
		damageScaling[2] = 0.7; 
	}
}
 */
