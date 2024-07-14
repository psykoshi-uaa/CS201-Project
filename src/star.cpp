#include "star.h"
#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
 
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
//			Planets
//-------------------------------------------------------------------------------
void Sun::DrawSun() {
	DrawCircleV(sunPos, sunRadius, (Color) {245, 255, 245, 255});
}

Planet::Planet() {
	orbitAngle = (std::rand() % 360) + 1;
	alpha = 0.0f;
	radius = (std::rand() % 10) + 3;
	mass = pow(radius, 2) * 100;
	orbitDistance = (std::rand() % 350) + 100;
	conicScale = orbitDistance / mass;
	conicRotation = std::rand() % 6;

	unsigned char colors[3] = {
		(unsigned char)((std::rand() % 155) + 100),
		(unsigned char)((std::rand() % 155) + 100),
		(unsigned char)((std::rand() % 155) + 100),
	};
	color = (Color) {colors[0], colors[1], colors[2], 255};
	orbitColor = (Color) {colors[0], colors[1], colors[2], 55};

	orbitOn = false;
}

void Planet::UpdatePlanet() {
	if (orbitAngle < 360) {
		orbitAngle -= (0.000001f / distFromSun) * mass;
	}
	else {
		orbitAngle = 0.0f;
	}

	orbitRadius = orbitDistance / (1 - conicScale * cos(orbitAngle - conicRotation));

	pos = (Vector2) {
		Sun::sunPos.x + cos(orbitAngle) * orbitRadius,
		Sun::sunPos.y + sin(orbitAngle) * orbitRadius 
	};
	
	for(int p=0; p<ORBITALPOINTS; p++) {
		float distScaler = 1 / distFromMouse;
		float splineAngleA = orbitAngle - (p * distScaler);
		float splineAngleB = orbitAngle + (p * distScaler);

		orbitPointsAhead[p] = {
			Sun::sunPos.x + cos(splineAngleA) * (orbitDistance / (1 - conicScale * cos(splineAngleA - conicRotation)) ),
			Sun::sunPos.y + sin(splineAngleA) * (orbitDistance / (1 - conicScale * cos(splineAngleA - conicRotation)) )
		};

		orbitPointsBehind[p] = {
			Sun::sunPos.x + cos(splineAngleB) * (orbitDistance / (1 - conicScale * cos(splineAngleB - conicRotation)) ),
			Sun::sunPos.y + sin(splineAngleB) * (orbitDistance / (1 - conicScale * cos(splineAngleB - conicRotation)) )
		};
	}

	for(int p=0; p<ORBITALPOINTSFULL; p++) {
		float splineAngleF = ((M_PI / ORBITALPOINTSFULL) * p * 2.041);

		orbitPointsFull[p] = {
			Sun::sunPos.x + cos(splineAngleF) * (orbitDistance / (1 - conicScale * cos(splineAngleF - conicRotation)) ),
			Sun::sunPos.y + sin(splineAngleF) * (orbitDistance / (1 - conicScale * cos(splineAngleF - conicRotation)) )
		};
	}

	distFromMouse = GetDist(pos, GetMousePosition() );
	distFromSun = GetDist(pos, Sun::sunPos);

	if (distFromMouse < 10) {
		distFromMouse = 10;
	}
}

void Planet::DrawPlanet(bool doDrawOrbital) {
	if (((CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	|| CheckCollisionPointCircle(GetMousePosition(), Sun::sunPos, 30) )
	&& doDrawOrbital == true)
	|| orbitOn == true) {
		DrawSplineLinear(orbitPointsFull, ORBITALPOINTSFULL, 2, orbitColor );
	}
	else if (CheckCollisionPointCircle(GetMousePosition(), pos, PLANETBOUNDS) ) {
		DrawSplineLinear(orbitPointsAhead, ORBITALPOINTS, 2, orbitColor );
		DrawSplineLinear(orbitPointsBehind, ORBITALPOINTS, 2, orbitColor );
	}
	
	DrawCircleV(pos, radius, color);
}

void Planet::RegisterPlanetClicked() {
	if (CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
		if (orbitOn == false) {
			orbitOn = true;
		}
		else if (orbitOn == true) {
			orbitOn = false;
		}
	}
}

void DrawAndUpdateSolarSystem(Sun sun, Planet *planet, bool doDrawOrbital) {
	
	DrawSun(Sun);

	for (int i=0; i<NUMPLANETS; i++) {
		planet[i].UpdatePlanet(Sun::sunPos);
		planet[i].RegisterPlanetClicked(Sun::sunPos);
		planet[i].DrawPlanet(Sun::sunPos, doDrawOrbital);
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


//-------------------------------------------------------------------------------
//			particle animations (PTX = particles)
//-------------------------------------------------------------------------------
void PTXStarAnim(PTX *ptx, float counter){
	for (int i=0; i<MAXSTARPTX; i++) {
		//initiialize the particles
		if (ptx[i].halflife == 0 ) {
			int chance = std::rand() % (350);
			
			if (chance == 1) {
				ptx[i].dist += (std::rand() % 45) * 0.01f;

				int colorChance = std::rand() % 3;

				switch (colorChance) {
					case 0: ptx[i].color = {220, 233, 255, 255};
							break;
					
					case 1: ptx[i].color = {125, 112, 180, 255};
							break;
							
					case 2: ptx[i].color = {22, 90, 153, 255};
							break;
					
					default: break;
				}

				ptx[i].halflife = 1;
				ptx[i].pos = {float(std::rand()%SCREENWIDTH), float(std::rand()%SCREENHEIGHT)};
			}
		}
		
		//update the particles
		else if (ptx[i].halflife > 0 && ptx[i].halflife < FPS) {
			if (int(counter) % FPS == 0) {
				ptx[i].halflife++;
			}

			if (ptx[i].alpha < ptx[i].dist) {
				ptx[i].alpha += 0.001f;
			}
		}

		//kill the particles
		else if (ptx[i].alpha > 0) {
			ptx[i].alpha -= 0.001f;
		}
		else {
			ptx[i].halflife = 0;
		}
		
		//draw the particles
		if (ptx[i].halflife != 0) {
			if (ptx[i].halflife % 3 == 0) {
				DrawTextEx(GetFontDefault(), "+", ptx[i].pos, 10, 0, ColorAlpha(ptx[i].color, ptx[i].alpha) );
			}
			else if (ptx[i].halflife % 3 == 1) {
				DrawTextEx(GetFontDefault(), "*", ptx[i].pos, 10, 0, ColorAlpha(ptx[i].color, ptx[i].alpha) );
			}
			else {
				DrawTextEx(GetFontDefault(), "x", ptx[i].pos, 10, 0, ColorAlpha(ptx[i].color, ptx[i].alpha) );
			}
		}
	}
}
