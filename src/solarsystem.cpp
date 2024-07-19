#include "../include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <random>


std::random_device ss_rd;

//-------------------------------------------------------------------------------
//			Sun and Planets
//-------------------------------------------------------------------------------
void DrawAndUpdateSolarSystem(Sun sun, Planet *planet, Planet &hubBase, bool doDrawOrbital) {
	sun.DrawSun();

	hubBase.UpdatePlanet();
	hubBase.RegisterClick();

	for (int i=0; i<NUMPLANETS; i++) {
		planet[i].UpdatePlanet();
		planet[i].RegisterClick();
		planet[i].DrawPlanet(doDrawOrbital);
	}
}

//Sun functions
Sun::Sun() {
	sunPos = (Vector2) {
		SCREENWIDTH/2,
		SCREENHEIGHT/2
	};

	sunRadius = 30;
	sunClicked = false;
}

void Sun::DrawSun() {
	DrawCircleV(sunPos, sunRadius, YELLOW); 
}


//Planet functions
Planet::Planet() {
	std::uniform_int_distribution<int> rand_angle(0, 360);
	std::uniform_int_distribution<int> rand_radius(3, 15);
	std::uniform_int_distribution<int> rand_dist(50, 450);
	std::uniform_int_distribution<int> rand_conic(0, 6);
	std::uniform_int_distribution<int> rand_RGB(25, 255);

	orbitAngle = rand_angle(ss_rd);
	radius = rand_radius(ss_rd);
	orbitDistance = rand_dist(ss_rd);
	conicRotation = rand_conic(ss_rd);
	mass = pow(radius, 2) * 100;
	conicScale = orbitDistance / mass;
	alpha = 0.0f;

	unsigned char colors[3] = {
		(unsigned char)(rand_RGB(ss_rd) ),
		(unsigned char)(rand_RGB(ss_rd) ),
		(unsigned char)(rand_RGB(ss_rd) )
	};
	color = (Color) {colors[0], colors[1], colors[2], 255};
	orbitColor = (Color) {colors[0], colors[1], colors[2], 55};

	orbitOn = false;
}

void Planet::UpdatePlanet() {
	orbitRadius = orbitDistance / (1 - conicScale * cos(orbitAngle - conicRotation));

	pos = (Vector2) {
		sunPos.x + cos(orbitAngle) * orbitRadius,
		sunPos.y + sin(orbitAngle) * orbitRadius 
	};
	
	for(int p=0; p<ORBITALPOINTS; p++) {
		float distScaler = 1 / distFromMouse;
		float splineAngleA = orbitAngle - (p * distScaler);
		float splineAngleB = orbitAngle + (p * distScaler);

		orbitPointsAhead[p] = {
			sunPos.x + cos(splineAngleA) * (orbitDistance / (1 - conicScale * cos(splineAngleA - conicRotation)) ),
			sunPos.y + sin(splineAngleA) * (orbitDistance / (1 - conicScale * cos(splineAngleA - conicRotation)) )
		};

		orbitPointsBehind[p] = {
			sunPos.x + cos(splineAngleB) * (orbitDistance / (1 - conicScale * cos(splineAngleB - conicRotation)) ),
			sunPos.y + sin(splineAngleB) * (orbitDistance / (1 - conicScale * cos(splineAngleB - conicRotation)) )
		};
	}

	for(int p=0; p<ORBITALPOINTSFULL; p++) {
		float splineAngleF = ((M_PI / ORBITALPOINTSFULL) * p * 2.041);

		orbitPointsFull[p] = {
			sunPos.x + cos(splineAngleF) * (orbitDistance / (1 - conicScale * cos(splineAngleF - conicRotation)) ),
			sunPos.y + sin(splineAngleF) * (orbitDistance / (1 - conicScale * cos(splineAngleF - conicRotation)) )
		};
	}

	distFromMouse = GetDist(pos, GetMousePosition() );
	distFromSun = GetDist(pos, sunPos);

	if (distFromMouse < 10) {
		distFromMouse = 10;
	}

	if (orbitAngle > 0) {
		orbitAngle -= (0.000001 / distFromSun) * mass;
	}
	else {
		orbitAngle = 360;
	}
}

void Planet::DrawPlanet(bool doDrawOrbital) {
	if (((CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	|| CheckCollisionPointCircle(GetMousePosition(), sunPos, 30) )
	|| orbitOn == true
	|| sunClicked == true)
	&& doDrawOrbital == true) {
		DrawSplineLinear(orbitPointsFull, ORBITALPOINTSFULL, 2, orbitColor );
	}
	else if (CheckCollisionPointCircle(GetMousePosition(), pos, PLANETBOUNDS) ) {
		DrawSplineLinear(orbitPointsAhead, ORBITALPOINTS, 2, orbitColor );
		DrawSplineLinear(orbitPointsBehind, ORBITALPOINTS, 2, orbitColor );
	}
	
	DrawCircleV(pos, radius, color);
}

void Planet::RegisterClick() {
	if (CheckCollisionPointCircle(GetMousePosition(), sunPos, sunRadius)
	&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
		if (sunClicked == false) {
			sunClicked = true;
		}
		else {
			sunClicked = false;
		}
	}

	if (CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
		if (orbitOn == false) {
			orbitOn = true;
		}
		else {
			orbitOn = false;
		}
	}
}

Vector2 Planet::GetPos() {
	return pos;
}

float Planet::GetRadius() {
	return radius;
}
