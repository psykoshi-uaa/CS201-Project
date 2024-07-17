#include "star.h"
#include "raylib.h"
#include <cmath>

Ship::Ship() {

	destination = (Vector2){400, 400};
	position = destination;
}

void Ship::DrawSelf(float radius, Color color) {
        
    Vector2 direction = {destination.x - position.x, destination.y - position.y};
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    float rotation = 0;

    if (distance > radius + 1)
    {
        position.x += direction.x * (velocity.x / distance);
        position.y += direction.y * (velocity.x / distance);
        rotation = atan2f(direction.y, direction.x) + acos(0.0);
    }
    else
    {
        float time = GetTime();

        position.x = destination.x - radius * cosf(time);
        position.y = destination.y - radius * sinf(time);
        rotation = time;
    }

        
    Vector2 points[3] = {
        { position.x, position.y - 10 },
        { position.x - 10, position.y + 10 },
        { position.x + 10, position.y + 10 }
    };

    for (int i = 0; i < 3; ++i) {
        float cosA = cosf(rotation);
        float sinA = sinf(rotation);
        float rotatedX = cosA * (points[i].x - position.x) - sinA * (points[i].y - position.y) + position.x;
        float rotatedY = sinA * (points[i].x - position.x) + cosA * (points[i].y - position.y) + position.y;
        points[i] = { rotatedX, rotatedY };
    }

    DrawTriangle(points[0], points[1], points[2], color);
}

void Ship::UpdateDestination(Vector2 dest) {
	destination = dest;
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
