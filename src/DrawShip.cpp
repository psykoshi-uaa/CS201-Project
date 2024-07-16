#include "raylib.h"
#include <cmath>

struct Ship {
    Vector2 position;
    Vector2 velocity;
};

void DrawShip(Ship& ship, float rotationDegrees, Color color) {
    Vector2 points[3] = {
        { ship.position.x, ship.position.y - 20 },
        { ship.position.x - 10, ship.position.y + 10 },
        { ship.position.x + 10, ship.position.y + 10 }
    };

    for (int i = 0; i < 3; ++i) {
        float angle = (rotationDegrees + acos(0.0));
        float cosA = cosf(angle);
        float sinA = sinf(angle);
        float rotatedX = cosA * (points[i].x - ship.position.x) - sinA * (points[i].y - ship.position.y) + ship.position.x;
        float rotatedY = sinA * (points[i].x - ship.position.x) + cosA * (points[i].y - ship.position.y) + ship.position.y;
        points[i] = { rotatedX, rotatedY };
    }

    DrawTriangle(points[0], points[1], points[2], color);
}

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

    SetTargetFPS(60);

    
    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            
            destination.x = (float)GetRandomValue(0, screenWidth);
            destination.y = (float)GetRandomValue(0, screenHeight);
        }

        Vector2 direction = {destination.x - ship.position.x, destination.y - ship.position.y};
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 1)
        {
        ship.position.x += direction.x * (ship.velocity.x / distance);
        ship.position.y += direction.y * (ship.velocity.x / distance);
        }

        float rotation = atan2f(direction.y, direction.x);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(destination.x, destination.y, 2, WHITE);

        DrawShip(ship, rotation, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}