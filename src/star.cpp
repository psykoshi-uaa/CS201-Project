#include "star.h"
#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include <ctime>
#include <cstdlib>

 
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
//			planets
//-------------------------------------------------------------------------------
void DrawSolarSystem(Planet *planet, Vector2 sunPos, bool doDrawOrbital) {
	DrawCircle(sunPos.x, sunPos.y, 30, (Color) {245, 255, 245, 255});

	for (int i=0; i<NUMPLANETS; i++) {
		if (planet[i].orbitAngle < 360) {
			planet[i].orbitAngle += .05 / planet[i].orbitRadius.x;
		}
		else {
			planet[i].orbitAngle = 0;
		}

		DrawPlanet(planet[i], (Vector2) {sunPos.x, sunPos.y}, doDrawOrbital);
	}
}

void DrawPlanet(Planet planet, Vector2 sunPos, bool doDrawOrbital) {
	planet.angle = (Vector2) {
		sunPos.x + cos(planet.orbitAngle) * planet.orbitRadius.x,
		sunPos.y + sin(planet.orbitAngle) * planet.orbitRadius.y };

	if (CheckCollisionPointCircle(GetMousePosition(), planet.angle, PLANETBOUNDS) && doDrawOrbital == true) 
	{
		float pointPerDist = 1 - (GetDist(planet.angle, GetMousePosition()) / PLANETBOUNDS);

		for(int p=0; p<ORBITALPOINTS; p++) {
			float scaleSpline = 0.1 * pointPerDist;

			planet.orbitPointsAhead[p] = (Vector2) {
				(float)(sunPos.x + cos((planet.orbitAngle - p * scaleSpline)) * planet.orbitRadius.x),
				(float)(sunPos.y + sin((planet.orbitAngle - p * scaleSpline)) * planet.orbitRadius.y) };
			planet.orbitPointsBehind[p] = (Vector2) {
				(float)(sunPos.x + cos((planet.orbitAngle + p * scaleSpline)) * planet.orbitRadius.x),
				(float)(sunPos.y + sin((planet.orbitAngle + p * scaleSpline)) * planet.orbitRadius.y) };
		}

		DrawSplineLinear(planet.orbitPointsAhead, ORBITALPOINTS, 2, (Color) {255, 255, 255, 75} );
		DrawSplineLinear(planet.orbitPointsBehind, ORBITALPOINTS, 2, (Color) {255, 255, 255, 75} );
	}

	if ((CheckCollisionPointCircle(GetMousePosition(), planet.angle, planet.radius)
	|| (CheckCollisionPointCircle(GetMousePosition(), sunPos, 30) ) )
	&& doDrawOrbital == true) {
		DrawEllipseLines(sunPos.x, sunPos.y, planet.orbitRadius.x, planet.orbitRadius.y, (Color) {255, 255, 255, 20} );
	}

	DrawCircle(planet.angle.x, planet.angle.y, planet.radius, planet.color);
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
void PTXStarAnim(PTX *ptx, float counter){
	for (int i=0; i<MAXSTARPTX; i++) {
		//initiialize the particles
		if (ptx[i].halflife == 0 ) {
			int chance = std::rand() % (FPS*FPS);
			
			if (chance == 1) {
				ptx[i].dist += (std::rand() % 35) * 0.01f;

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
			ptx[i].alpha -= 0.1f;
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

//
