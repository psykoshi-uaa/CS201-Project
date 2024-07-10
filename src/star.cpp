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
//			Planets
//-------------------------------------------------------------------------------
Planet::Planet() {
	orbitAngle = (std::rand() % 360) + 1;
	alpha = 0.0f;
	radius = (std::rand() % 10) + 3;
	mass = (radius * 1000);
	orbitDistance = (std::rand() % 350) + 100;
	conicScale = orbitDistance/mass;

	unsigned char colors[3] = {
		(unsigned char)((std::rand() % 155) + 100),
		(unsigned char)((std::rand() % 155) + 100),
		(unsigned char)((std::rand() % 155) + 100),
	};
	color = (Color) {colors[0], colors[1], colors[2], 255};
}

void Planet::UpdatePlanet(Vector2 sunPos) {
	if (orbitAngle < 360) {
		orbitAngle -= 0.00001 * distFromSun;
	}
	else {
		orbitAngle = 0;
	}

	orbitRadius = orbitDistance / (1 - conicScale * cos(orbitAngle - 0));

	pos = (Vector2) {
		sunPos.x + cos(orbitAngle) * orbitRadius,
		sunPos.y + sin(orbitAngle) * orbitRadius 
	};
	
	distFromMouse = GetDist(pos, GetMousePosition() );
	distFromSun = GetDist(pos, sunPos);
}

void Planet::DrawPlanet(Vector2 sunPos, bool doDrawOrbital) {
	if (CheckCollisionPointCircle(GetMousePosition(), pos, PLANETBOUNDS) && doDrawOrbital == true) {
		for(int p=0; p<ORBITALPOINTS; p++) {
			float scaleSpline = 0.1 * (1 - (distFromMouse/PLANETBOUNDS));

			orbitPointsAhead[p] = {
				sunPos.x + cos(orbitAngle - p * scaleSpline) * orbitRadius,
				sunPos.y + sin(orbitAngle - p * scaleSpline) * orbitRadius
			};

			orbitPointsBehind[p] = {
				sunPos.x + cos(orbitAngle + p * scaleSpline) * orbitRadius,
				sunPos.y + sin(orbitAngle + p * scaleSpline) * orbitRadius
			};
		}

		DrawSplineLinear(orbitPointsAhead, ORBITALPOINTS, 2, (Color) {255, 255, 255, 75} );
		DrawSplineLinear(orbitPointsBehind, ORBITALPOINTS, 2, (Color) {255, 255, 255, 75} );
	}

	
	if ((CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	|| (CheckCollisionPointCircle(GetMousePosition(), sunPos, 30) ) )
	&& doDrawOrbital == true) {
		DrawEllipseLines(sunPos.x, sunPos.y, orbitRadius, orbitRadius, WHITE);
	}
	

	DrawCircleV(pos, radius, color);
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

void DrawSolarSystem(Planet *planet, Vector2 sunPos, bool doDrawOrbital) {
	DrawCircleV(sunPos, 30, (Color) {245, 255, 245, 255});
	for (int i=0; i<NUMPLANETS; i++) {
		planet[i].UpdatePlanet(sunPos);
		planet[i].DrawPlanet(sunPos, doDrawOrbital);
	}
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
				ptx[i].dist += (std::rand() % 25) * 0.01f;

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
