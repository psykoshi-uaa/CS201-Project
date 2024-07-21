#include "raylib.h"
#include <iostream>
#include <cmath>

void shootingStar(float screenWidth, float screenHeight, int& count)
{  
    Vector2 direction;
    float distance;
    float velocity = 2.0f;

    static Vector2 destination_1;
    static Vector2 destination_2;
    static Vector2 start;
    static Vector2 position;
    static float total_distance = sqrt(pow((destination_2.x - position.x), 2) + pow((destination_2.y - position.x), 2));

    if (count == 0) {
        position = { (float)GetRandomValue(0, screenWidth - total_distance), (float)GetRandomValue(0, screenHeight - total_distance)};
        start = position;
        destination_1 = {position.x + (screenWidth / 16), position.y + (screenHeight / 15)};  
        destination_2 = {position.x + (screenWidth / 10), position.y + (screenHeight / (45.0f/8.0f))};
    }

    switch (count) {
        case 0:
            count++;
            break;
        case 1:
            if (position.x < destination_1.x) {
                direction = { destination_1.x - position.x, destination_1.y - position.y };
                distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                position.x += direction.x * (velocity / distance);
                position.y += direction.y * (velocity / distance);
                if(distance > 800 / 200)
                DrawLine(start.x, start.y, position.x - (screenWidth / 400), position.y - (screenHeight / 225), WHITE);
            } else {
                count++;
            }
            break;
        case 2:
            if (position.x < destination_2.x) {
                DrawLine(start.x, start.y, destination_1.x, destination_1.y, WHITE);
                direction = { destination_2.x - position.x, destination_2.y - position.y };
                distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                position.x += direction.x * (velocity / distance);
                position.y += direction.y * (velocity / distance);
                if(position.x > destination_1.x + (800 / 200))
                {
                    DrawLine(destination_1.x, destination_1.y, position.x - (screenWidth / 400), position.y - (screenHeight / 225), WHITE);
                }
            } else {
                position = start;
                count++;
            }
            break;
        case 3:
            DrawLine(destination_1.x, destination_1.y, destination_2.x, destination_2.y, WHITE);
            direction = { destination_1.x - position.x, destination_1.y - position.y };
            distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            position.x += direction.x * (velocity / distance);
            position.y += direction.y * (velocity / distance);
            if(position.x < destination_1.x)
            {
                DrawLine(position.x, position.y, destination_1.x, destination_1.y, WHITE);
            }
            else{
                count++;
            }
            break;
        case 4:
            direction = { destination_2.x - position.x, destination_2.y - position.y};
            distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            position.x += direction.x * (velocity / distance);
            position.y += direction.y * (velocity / distance);
            if(position.x < destination_2.x)
            {
                DrawLine(position.x, position.y, destination_2.x, destination_2.y, WHITE);
            }
            else{
                count = 0;
            }
            break;
        default:
            break;
    }
    
    if (count < 3)
    {
        DrawText("*", position.x, position.y, screenWidth / 80, WHITE);
    }
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Draw Ship");

    SetTargetFPS(60);

    int count = 0;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);
        
        shootingStar(screenWidth, screenHeight, count);

        EndDrawing();
    }
        CloseWindow();
}