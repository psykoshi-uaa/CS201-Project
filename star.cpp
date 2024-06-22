#include "star.h"


Player::Player(std::string inpName) {
	name = inpName;
	flightClass = 1;
	repCap = (flightClass * 5) + flightClass;
}
void Player::addRep(short int repToAdd){	
	if (repToAdd + rep > repCap){
		rankUp();
		rep = 0 + (repToAdd - (repCap - rep));
	}
	else{
		rep += repToAdd;
	}
}
void Player::rankUp(){
	flightClass++;
	repCap = (flightClass * 5) + flightClass;
	//Genererate congratulatory message
}


Weapon::Weapon(std::string idType, std::string idModel) {
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



//code utility classes
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
