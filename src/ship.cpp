#include "../include/star.h"
#include "raylib.h"
#include <cmath>
#include <string>

Ship::Ship(Vector2 startingPoint) 
	: destination(startingPoint), position(startingPoint) {
	velocity = (Vector2){1.0, 1.0};
	speed = 1;
}

void Ship::DrawSelf(float radius, Color color) {
		//calculate direction faced and distance
    Vector2 direction = {destination.x - position.x, destination.y - position.y};
    distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    float rotation = 0;

		//if the distance of the ship is > radius + 1 then set the position closer to the destination based on velocity
    if (distance > radius + 1)
    {
        position.x += direction.x * (velocity.x / distance);
        position.y += direction.y * (velocity.x / distance);
        rotation = atan2f(direction.y, direction.x) + acos(0.0);
    }
		//otherwise draw the ship circling it's destination
    else
    {
        float time = GetTime();

        position.x = destination.x - radius * cosf(time);
        position.y = destination.y - radius * sinf(time);
        rotation = time;
    }

        
    Vector2 points[3] = {
        { position.x, position.y - 2 },
        { position.x - 5, position.y + 5 },
        { position.x + 5, position.y + 5 }
    };
    Vector2 outlinepoints[3] = {
        { position.x, points[0].y - 1 },
        { points[1].x - 1, points[1].y + 1 },
        { points[2].x + 1, points[2].y + 1 }
    };

    for (int i = 0; i < 3; ++i) {
			//the ship is drawn as a triangle given three points, here the points are calculated based on rotation
        float cosA = cosf(rotation);
        float sinA = sinf(rotation);
        float rotatedX = cosA * (points[i].x - position.x) - sinA * (points[i].y - position.y) + position.x;
        float rotatedY = sinA * (points[i].x - position.x) + cosA * (points[i].y - position.y) + position.y;
        float outlinerotatedX = cosA * (outlinepoints[i].x - position.x) - sinA * (outlinepoints[i].y - position.y) + position.x;
        float outlinerotatedY = sinA * (outlinepoints[i].x - position.x) + cosA * (outlinepoints[i].y - position.y) + position.y;
        points[i] = { rotatedX, rotatedY };
        outlinepoints[i] = { outlinerotatedX, outlinerotatedY };
    }

		//draw the ship
    DrawTriangle(outlinepoints[0], outlinepoints[1], outlinepoints[2], BLACK);
    DrawTriangle(points[0], points[1], points[2], color);
}

void Ship::UpdateDestination(Vector2 dest) {
	destination = dest;
}

void Ship::SetPosition(Vector2 pos) {
	position = pos;
}	

bool Ship::IsAtDestination(float radius) {
	if (distance <= radius + 1) {
		return true;
	}
	else {
		return false;
	}
}

	//THE REST IS LARGELY UNUSED EXCEPT FOR A SET SPEED AND GET SPEED

//getters
std::string Ship::getName()
{
    return name;
}
int Ship::getHP()
{
    return HP;
}
int Ship::getMaxHP()
{
    return maxHP;
}
int Ship::getShield()
{
    return shield;
}
int Ship::getmaxShield()
{
    return maxShield;
}
int Ship::getCargo()
{
    return cargo;
}
int Ship::getCargoCapacity()
{
    return cargoCapacity;
}
int Ship::getSpeed()
{
    return speed;
}
int Ship::getWeapon()
{
	return weapon;
}
int Ship::getGatheringTool()
{
	return gatheringTool;
}

//setters
void Ship::setHP(int newHP)
{
    HP = newHP;
}
void Ship::setMaxHP(int newMaxHP)
{
    maxHP = newMaxHP;
}
void Ship::setShield(int newShield)
{
    shield = newShield;
}
void Ship::setmaxShield(int newMaxShield)
{
    maxShield = newMaxShield;
}
void Ship::setCargo(int newCargo)
{
    cargo = newCargo;
}
void Ship::setCargoCapacity(int newCargoCapacity)
{
    cargoCapacity = newCargoCapacity;
}
void Ship::setSpeed(int newSpeed)
{
    velocity.x = newSpeed;
    velocity.y = newSpeed;
    speed = newSpeed;
}
void Ship::setWeapon(int newWeapon)
{
	weapon = newWeapon;
}
void Ship::setGatheringTool(int newGatheringTool)
{
	gatheringTool = newGatheringTool;
}

//Combat Methods
void Ship::TakeDamage(int amount)
{
    shield -= amount;
    HP -= amount;
}
void Ship::Repair(int amount)
{
    HP += amount;
}
void Ship::AddCargo(int amount)
{
    cargo += amount;
}
void Ship::RemoveCargo(int amount)
{
    cargo -= amount;
}


/*
int main() {
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Draw Ship");

    Ship ship;
    ship.position.x = screenWidth / 2;
    ship.position.y = screenHeight / 2;
    ship.velocity.x = 2.0;
    ship.velocity.y = 2.0;

    Vector2 destination = {0, 0};
    float radius = 0;

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            
            destination.x = (float)GetRandomValue(0, screenWidth - 100);
            destination.y = (float)GetRandomValue(0, screenHeight - 100);
            radius = GetRandomValue(30, 100);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(destination.x, destination.y, 2, WHITE);

        DrawShip(ship, destination, radius, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
*/
