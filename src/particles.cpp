#include "../include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>


//-------------------------------------------------------------------------------
//			particle animations (PTX = particles)
//-------------------------------------------------------------------------------
PTXstarmanager::PTXstarmanager() {
	starFX[0] = '+';
	starFX[1] = '*';
	starFX[2] = 'x';
	counter = 0;
	updateTime = FPS;
}

void PTXstarmanager::LifeCycle() {
	for (int i=0; i<MAXSTARPTX; i++) {
		if (ptxstar[i].life == 0) {
			GenerateStar(ptxstar[i]);
		}
		else if (ptxstar[i].life > 0 && ptxstar[i].life < FPS) {
			UpdateSelf(ptxstar[i]);
			DrawSelf(ptxstar[i]);
		}
		else if (ptxstar[i].alpha > 0) {
			ptxstar[i].alpha -= 0.001f;
			DrawSelf(ptxstar[i]);
		}
		else {
			ptxstar[i].life = 0;
		}
	}

	if (counter > updateTime) {
		counter = 0;
	}
	else {
		counter++;
	}

}

void PTXstarmanager::GenerateStar(PTXstar &ptx) {
	if (ptx.life == 0) {
		int chance = GetRandomValue(0, 400);
		
		if (chance == 1) {
			ptx.dist = GetRandomValue(3, 20) * 0.01f;

			int colorChance = GetRandomValue(0, 3);

			switch (colorChance) {
				case 0: ptx.color = {70, 200, 255, 255};
						break;
				
				case 1: ptx.color = {70, 70, 255, 255};
						break;
						
				case 2: ptx.color = {70, 150, 255, 255};
						break;
				
				case 3: ptx.color = {255, 250, 230, 255};
						break;
				
				default: break;
			}

			ptx.life = 1;
			ptx.pos = { (float)GetRandomValue(0, SCREENWIDTH), (float)GetRandomValue(0, SCREENHEIGHT) };
		}
	}
}

void PTXstarmanager::UpdateSelf(PTXstar &ptx) {
	if (counter == updateTime) {
		ptx.life++;
	}

	if (ptx.alpha < ptx.dist) {
		ptx.alpha += 0.001f;
	}
}

void PTXstarmanager::DrawSelf(PTXstar &ptx) {
	if (ptx.life > 0) {
		if ((ptx.life + 1) % 3 == 0) {
			DrawTextCodepoint(GetFontDefault(), starFX[0], ptx.pos, 10, ColorAlpha(ptx.color, ptx.alpha) );
		}
		else if ((ptx.life + 1) % 3 == 1) {
			DrawTextCodepoint(GetFontDefault(), starFX[1], ptx.pos, 10, ColorAlpha(ptx.color, ptx.alpha) );
		}
		else {
			DrawTextCodepoint(GetFontDefault(), starFX[2], ptx.pos, 10, ColorAlpha(ptx.color, ptx.alpha) );
		}
	}
}

void ShootingStar(float screenWidth, float screenHeight, int& count)
{  
    Vector2 direction;
    float distance;
    float velocity = 16.0f;
    int width = GetRandomValue(30, 40),
	height= GetRandomValue(70, 90);

    static float alpha = 0.0f;
    static Vector2 destination_1;
    static Vector2 destination_2;
    static Vector2 start;
    static Vector2 position;
    static float total_distance = sqrt(pow((destination_2.x - position.x), 2) + pow((destination_2.y - position.x), 2));

    if (count == 0) {
        position = { (float)GetRandomValue(0, screenWidth - total_distance), (float)GetRandomValue(0, screenHeight - total_distance)};
        start = position;
        destination_1 = {position.x + (float)width, position.y + (float)height};  
        destination_2 = {destination_1.x + (float)width, destination_1.y + (float)height};
    }

    if (alpha < 1.0f) {
		alpha += 0.1f;
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
                DrawLine(start.x, start.y, position.x - (screenWidth / 400), position.y - (screenHeight / 225), ColorAlpha(WHITE, alpha));
            } else {
                count++;
            }
            break;
        case 2:
            if (position.x < destination_2.x) {
                DrawLine(start.x, start.y, destination_1.x, destination_1.y, ColorAlpha(ColorAlpha(WHITE, alpha), alpha));
                direction = { destination_2.x - position.x, destination_2.y - position.y };
                distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                position.x += direction.x * (velocity / distance);
                position.y += direction.y * (velocity / distance);
                if(position.x > destination_1.x + (800 / 200))
                {
                    DrawLine(destination_1.x, destination_1.y, position.x - (screenWidth / 400), position.y - (screenHeight / 225), ColorAlpha(WHITE, alpha));
                }
            } else {
                position = start;
                count++;
            }
            break;
        case 3:
            DrawLine(destination_1.x, destination_1.y, destination_2.x, destination_2.y, ColorAlpha(WHITE, alpha));
            direction = { destination_1.x - position.x, destination_1.y - position.y };
            distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            position.x += direction.x * (velocity / distance);
            position.y += direction.y * (velocity / distance);
            if(position.x < destination_1.x)
            {
                DrawLine(position.x, position.y, destination_1.x, destination_1.y, ColorAlpha(WHITE, alpha));
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
                DrawLine(position.x, position.y, destination_2.x, destination_2.y, ColorAlpha(WHITE, alpha));
            }
            else{
                count = -1;
            }
            break;
        default:
            break;
    }
    
    if (count >= 0 && count < 3)
    {
        DrawText("*", position.x, position.y, 14, WHITE);
    }
};
