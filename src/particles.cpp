#include "../include/star.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <random>


std::random_device ptx_rd;

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
		if (ptx[i].life == 0) {
			GenerateStar(ptx[i]);
		}
		else if (ptx[i].life > 0 && ptx[i].life < FPS) {
			UpdateSelf(ptx[i]);
			DrawSelf(ptx[i]);
		}
		else if (ptx[i].alpha > 0) {
			ptx[i].alpha -= 0.001f;
			DrawSelf(ptx[i]);
		}
		else {
			ptx[i].life = 0;
		}
	}
}

void PTXstarmanager::GenerateStar(PTXstar &ptx) {
	if (ptx.life == 0) {
		std::uniform_int_distribution<int> rand_chance(0, 100);

		int chance = rand_chance(ptx_rd);
		
		if (chance == 1) {
			std::uniform_int_distribution<int> rand_dist(20, 45);
			std::uniform_int_distribution<int> rand_color_selector(1, 3);
			std::uniform_int_distribution<int> rand_screen_x(1, SCREENWIDTH);
			std::uniform_int_distribution<int> rand_screen_y(1, SCREENHEIGHT);

			ptx.dist += rand_dist(ptx_rd) * 0.01f;

			int colorChance = rand_color_selector(ptx_rd);

			switch (colorChance) {
				case 0: ptx.color = {220, 233, 255, 255};
						break;
				
				case 1: ptx.color = {125, 112, 180, 255};
						break;
						
				case 2: ptx.color = {22, 90, 153, 255};
						break;
				
				default: break;
			}

			ptx.life = 1;
			ptx.pos = {float(rand_screen_x(ptx_rd) ), float(rand_screen_y(ptx_rd) ) };
		}
	}
}

void PTXstarmanager::UpdateSelf(PTXstar &ptx) {
	if (counter == updateTime) {
		ptx.life++;
	}

	if (counter > updateTime) {
		counter = 0;
	}
	else {
		counter++;
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
