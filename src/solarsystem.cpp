#include "../include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <vector>
#include <random>


std::random_device ss_rd;

//-------------------------------------------------------------------------------
//			Sun and Planets
//-------------------------------------------------------------------------------
	//This is the function that handles all of the solar system functions
void DrawAndUpdateSolarSystem(Sun sun, Player pilot, Planet *planet, HubPort &hubBase, bool doDrawOrbital, Texture2D hubBaseTX) {
	sun.DrawSun();

	hubBase.UpdateHubPort(pilot);
	hubBase.RegisterClick();
	hubBase.DrawHubPort(doDrawOrbital, hubBaseTX);

	for (int i=0; i<NUMPLANETS; i++) {
		planet[i].UpdatePlanet(pilot);
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
	DrawCircleV(sunPos, sunRadius, WHITE); 
}


//Planet functions
Planet::Planet() {
		//GetRand was not working correctly so I opted for the <random> include
	std::uniform_int_distribution<int> rand_radius(3, 15);
	std::uniform_int_distribution<int> rand_dist(50, 450);
	std::uniform_int_distribution<int> rand_conic(-0.8, 0.8);
	std::uniform_int_distribution<int> rand_RGB(25, 255);

		//init the planet variables
	orbitAngle = 0;
	startingAngle = 0;
	radius = rand_radius(ss_rd);
	orbitDistance = rand_dist(ss_rd);
	conicRotation = rand_conic(ss_rd);
	mass = pow(radius, 2) * 100;
	conicScale = orbitDistance / mass;
	alpha = 0.0f;

		//assign the color randomly
	unsigned char colors[3] = {
		(unsigned char)(rand_RGB(ss_rd) ),
		(unsigned char)(rand_RGB(ss_rd) ),
		(unsigned char)(rand_RGB(ss_rd) )
	};
	color = (Color) {colors[0], colors[1], colors[2], 255};
	orbitColor = (Color) {colors[0], colors[1], colors[2], 55};

	orbitOn = false;
}

void Planet::GenerateMissions(GUIbtn * btnSetting, bool raidPlanet) {
		//sometimes there are no planets that are far enough away to generate every mission type
		//so I included this as a surefire way to make sure atleast one planet has all 5 mission types
	if (raidPlanet == false) {
		numMissionsAvail = ceil(orbitDistance / 101);
	}
	else {
		numMissionsAvail = 5;
	}

		//fill the mission vector
	missionsAvail.emplace_back("OddJob", 200, 4, 1.0, (btnSetting)->border );
	missionsAvail.emplace_back("Gather", 1200, 20, 10.0, (btnSetting + 1)->border );
	missionsAvail.emplace_back("Salvage", 3000, 7, 45.0, (btnSetting + 2)->border );
	missionsAvail.emplace_back("Bounty", 8000, 45, 10.0, (btnSetting + 3)->border );
	missionsAvail.emplace_back("Raid", 24000, 90, 180.0, (btnSetting + 4)->border );
}


void Planet::UpdatePlanet(Player pilot) {
		//adjust the orbit based on an orbital equation
	orbitRadius = orbitDistance / (1 - conicScale * cos(orbitAngle - conicRotation));

	pos = (Vector2) {
		sunPos.x + cos(orbitAngle) * orbitRadius,
		sunPos.y + sin(orbitAngle) * orbitRadius 
	};
	
		//there are two orbital point arrays for the gradually increasing and decreasing orbit lines based on mouse distance
	for(int p=0; p<ORBITALPOINTS; p++) {
		float distScaler = 1 / distFromMouse;
		float splineAngleA = orbitAngle - (p * distScaler);
		float splineAngleB = orbitAngle + (p * distScaler);

			//these two arrays change the position of each point based on mouse distance along the same orbital equation that the planet follows
		orbitPointsAhead[p] = {
			sunPos.x + cos(splineAngleA) * (orbitDistance / (1 - conicScale * cos(splineAngleA - conicRotation)) ),
			sunPos.y + sin(splineAngleA) * (orbitDistance / (1 - conicScale * cos(splineAngleA - conicRotation)) )
		};

		orbitPointsBehind[p] = {
			sunPos.x + cos(splineAngleB) * (orbitDistance / (1 - conicScale * cos(splineAngleB - conicRotation)) ),
			sunPos.y + sin(splineAngleB) * (orbitDistance / (1 - conicScale * cos(splineAngleB - conicRotation)) )
		};
	}

		//this is a third array for the full orbital line based on the same orbital equation that the planet follows
	for(int p=0; p<ORBITALPOINTSFULL; p++) {
		float splineAngleF = ((M_PI / ORBITALPOINTSFULL) * p * 2.041);

		orbitPointsFull[p] = {
			sunPos.x + cos(splineAngleF) * (orbitDistance / (1 - conicScale * cos(splineAngleF - conicRotation)) ),
			sunPos.y + sin(splineAngleF) * (orbitDistance / (1 - conicScale * cos(splineAngleF - conicRotation)) )
		};
	}

		//important distance calculations
	distFromMouse = GetDist(pos, GetMousePosition() );
	distFromSun = GetDist(pos, sunPos);

		//if the mouse dist is less than 10 than set to 10 otherwise the lines do some crazy things
	if (distFromMouse < 10) {
		distFromMouse = 10;
	}

		//adust the orbit of the planet based on time, distance from sun, and mass of planet
	if (orbitAngle > 0) {
		orbitAngle = ((pilot.getTimeRemaining() * 0.0001) / distFromSun) * mass;
	}
	else {
		orbitAngle = 360;
	}
}

void Planet::DrawPlanet(bool doDrawOrbital) {
		//if the mouse is colliding with the planet, the orbit is on, or the sun is on then draw the full orbital line
	if (((CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	|| CheckCollisionPointCircle(GetMousePosition(), sunPos, 30) )
	|| orbitOn == true
	|| sunClicked == true)
	&& doDrawOrbital == true) {
		DrawSplineLinear(orbitPointsFull, ORBITALPOINTSFULL, 2, orbitColor );
	}
		//otherwise if the planet is within a certain range then draw the gradually increasing and decreasing orbital lines
	else if (CheckCollisionPointCircle(GetMousePosition(), pos, PLANETBOUNDS) ) {
		DrawSplineLinear(orbitPointsAhead, ORBITALPOINTS, 2, orbitColor );
		DrawSplineLinear(orbitPointsBehind, ORBITALPOINTS, 2, orbitColor );
	}
	
		//draw the planet
	DrawCircleV(pos, radius, color);
}

void Planet::RegisterClick() {
		//if the sun is clicked turn sunclicked on
	if (CheckCollisionPointCircle(GetMousePosition(), sunPos, sunRadius)
	&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
		if (sunClicked == false) {
			sunClicked = true;
		}
		else {
			sunClicked = false;
		}
	}
		//if the planet is clicked turn orbit on
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

void Planet::MissionHandler(Player &pilot, Ship ship, bool doUpdateTimer) {
		//mission correction is needed for the planets with bounty or raid
	int missionCorrection = 0;

		//for each mission, draw and handle mission based on if it can be clicked or not
	if (!doUpdateTimer) {
		if (GetNumMissions() >= 4) {
			missionCorrection = 1;
			if (pilot.weapon_upgrade_counter > 0) {
				missionsAvail[3].CompleteMission(pilot, ship);
				missionsAvail[3].DrawButton(pilot, true);
			}
			else {
				missionsAvail[3].DrawButton(pilot, false);
			}
		}

		if (GetNumMissions() == 5) {
			missionCorrection = 2;
			if (pilot.weapon_upgrade_counter == 3) {
				missionsAvail[4].CompleteMission(pilot, ship);
				missionsAvail[4].DrawButton(pilot, true);
			}
			else {
				missionsAvail[4].DrawButton(pilot, false);
			}
		}

			//draw each mission except for the bounty or raid missions because they draw themselves already
			//this was a workaround fix that needs a rework with the mission class but we did not have time
		for (int i=0; i<GetNumMissions() - missionCorrection; i++) {
			missionsAvail[i].CompleteMission(pilot, ship);
			missionsAvail[i].DrawButton(pilot, true);
		}
	}
	else {
		for (int i=0; i<GetNumMissions(); i++) {
				//update the cooldown for each mission regardless of anything
			missionsAvail[i].updateTimer();
		}
	}
}

// getters
Vector2 Planet::GetPos() {
	return pos;
}

float Planet::GetRadius() {
	return radius;
}

int Planet::GetNumMissions() {
	return numMissionsAvail;
}

//Hubport class that operates similarily to the planet class
HubPort::HubPort(float radius, float orbitDistance)
	: radius(radius), orbitDistance(orbitDistance) {
		//see planet class for constructor info
	orbitAngle = 0;
	mass = pow(radius, 2) * 100;
	conicScale = orbitDistance / mass;
	conicRotation = 0;

	orbitOn = false;

	orbitRadius = orbitDistance / (1 - conicScale * cos(orbitAngle - conicRotation));
	pos = (Vector2) {
		sunPos.x + cos(orbitAngle) * orbitRadius,
		sunPos.y + sin(orbitAngle) * orbitRadius 
	};
}

void HubPort::GenerateMarket(GUIbtn * btnSetting) {
	//init of market upgrades and their different tier levels
    weaponUpgrade.emplace_back("Slot-1 Turret", 1, "weapon", 10000, (btnSetting)->border);
    weaponUpgrade.emplace_back("Slot-2 Turret", 2, "weapon", 10000, (btnSetting)->border);
    weaponUpgrade.emplace_back("Slot-3 Turret", 3, "weapon", 10000, (btnSetting)->border);

    rewardUpgrade.emplace_back("Cargo Hold Tape", 1, "reward", 250, (btnSetting + 2)->border);
    rewardUpgrade.emplace_back("Refrigerator Unit", 2, "reward", 1000, (btnSetting + 2)->border);
    rewardUpgrade.emplace_back("Live Creature Cage", 3, "reward", 2500, (btnSetting + 2)->border);
    rewardUpgrade.emplace_back("MortCorp Stasis Freezer", 4, "reward", 10000, (btnSetting + 2)->border);
    rewardUpgrade.emplace_back("MortCorp Transpo License", 5, "reward", 25000, (btnSetting + 2)->border);

    timeCostUpgrade.emplace_back("R0B0-t1 Lifter", 1, "timeCost", 500, (btnSetting + 3)->border);
    timeCostUpgrade.emplace_back("Thruster Kit", 2, "timeCost", 2000, (btnSetting + 3)->border);
    timeCostUpgrade.emplace_back("Grav Sleds", 3, "timeCost", 10000, (btnSetting + 3)->border);
    timeCostUpgrade.emplace_back("Kitsa Minion Egg", 4, "timeCost", 25000, (btnSetting + 3)->border);
    timeCostUpgrade.emplace_back("Priority Bathroom Pass", 5, "timeCost", 80000, (btnSetting + 3)->border);

    payDebt.emplace_back("Pay Debt", 0, "pay debt", 1000, (btnSetting + 4)->border);
    payDebt.emplace_back("Pay Debt", 1, "pay debt", 10000, (btnSetting + 4)->border);
    payDebt.emplace_back("Pay Debt", 2, "pay debt", 100000, (btnSetting + 4)->border);
	payDebt.emplace_back("Pay Debt", 3, "pay debt", 150000, (btnSetting + 4)->border);
}	

void HubPort::UpdateHubPort(Player pilot) {
		//see planet update function for info -----------
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
		orbitAngle -= ((pilot.getTimeRemaining() * 0.00000001) / distFromSun) * mass;
	}
	else {
		orbitAngle = 360;
	}
}

void HubPort::DrawHubPort(bool doDrawOrbital, Texture2D hubBaseTX) {
		//see planet draw for info (except that this one draws a texture instead of a filled circle)
	if (((CheckCollisionPointCircle(GetMousePosition(), pos, radius)
	|| CheckCollisionPointCircle(GetMousePosition(), sunPos, 30) )
	|| orbitOn == true
	|| sunClicked == true)
	&& doDrawOrbital == true) {
		DrawSplineLinear(orbitPointsFull, ORBITALPOINTSFULL, 2, GRAY );
	}
	else if (CheckCollisionPointCircle(GetMousePosition(), pos, PLANETBOUNDS) ) {
		DrawSplineLinear(orbitPointsAhead, ORBITALPOINTS, 2, GRAY );
		DrawSplineLinear(orbitPointsBehind, ORBITALPOINTS, 2, GRAY );
		}
		
	Vector2 texPos = (Vector2){ pos.x - 16, pos.y - 16 };
	DrawTextureV(hubBaseTX, texPos, WHITE);
}

void HubPort::RegisterClick() {
		//see planet registerclick for info
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

void HubPort::MarketHandler(Player& pilot, Ship& ship) {
		//handle each market button based on player upgrade levels
	static int payDebtCounter = 0;

	if (pilot.timeCost_upgrade_counter < 5) {
		timeCostUpgrade[pilot.timeCost_upgrade_counter].DrawButton(pilot);
		timeCostUpgrade[pilot.timeCost_upgrade_counter].BuyUpgrade(pilot, ship);
	}

	if (pilot.reward_upgrade_counter < 5) {
		rewardUpgrade[pilot.reward_upgrade_counter].DrawButton(pilot);
		rewardUpgrade[pilot.reward_upgrade_counter].BuyUpgrade(pilot, ship);
	}

	if (pilot.weapon_upgrade_counter < 3) {
		weaponUpgrade[pilot.weapon_upgrade_counter].DrawButton(pilot);
		weaponUpgrade[pilot.weapon_upgrade_counter].BuyUpgrade(pilot, ship);
	}

		//if the pay debt button is right clicked change it's tier level
	if (payDebt[0].IsRClicked() ) {
		if (payDebtCounter < 3) {
			payDebtCounter++;
		}
		else {
			payDebtCounter = 0;
		}
	}
	payDebt[payDebtCounter].DrawButton(pilot);
	payDebt[payDebtCounter].BuyUpgrade(pilot, ship);
}

Vector2 HubPort::GetPos() {
	return pos;
}

float HubPort::GetRadius() {
	return radius;
}
