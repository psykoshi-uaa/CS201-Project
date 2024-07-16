#include "star.h"
#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include <cmath>
#include <random>


//-------------------------------------------------------------------------------
//			particle animations (PTX = particles)
//-------------------------------------------------------------------------------
PTXstarmanager::PTXstarmanager() {
	//Create FX area here instead of tied to full screen?
}

PTXstarmanager::LifeCycle() {
	for (int i=0; i<MAXSTARPTX; i++) {
		if (ptx[i].life == 0) {
			GenerateStar(ptx[i]);
		}
		else if (ptx[i].life > 0 && ptx[i].life < FPS) {
			UpdateSelf(ptx[i]);
			DrawSelf(ptx[i]);
		else if (ptx[i].alpha > 0) {
			DiminishSelf(ptx[i]);
			DrawSelf(ptx[i]);
		}
		else {
			ptx[i].life = 0;
		}
	}
}

void PTXstarmanager::GenerateStar(PTXstar &ptx) {
	if (ptx.life == 0) {
		std::uniform_int_distribution<int> rand_chance(0, 400);

		int chance = rand_chance(rd);
		
		if (chance == 1) {
			std::uniform_int_distribution<int> rand_dist(0, 45);
			std::uniform_int_distribution<int> rand_color_selector(1, 3);
			std::uniform_int_distribution<int> rand_screen_x(1, SCREENWIDTH);
			std::uniform_int_distribution<int> rand_screen_y(1, SCREENHEIGHT);

			ptx[i].dist += rand_dist(rd) * 0.01f;

			int colorChance = rand_color_selector(rd);

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
			ptx.pos = {float(rand_screen_x(rd) ), float(rand_screen_y(rd) ) };
	}
}

void PTXstarmanager::UpdateSelf(PTXstar &ptx) {

			if (int(counter) % FPS == 0) {
				ptx[i].halflife++;
			}

			if (ptx[i].alpha < ptx[i].dist) {
				ptx[i].alpha += 0.001f;
			}
}

void PTXStarAnim(PTX *ptx, float counter){
	for (int i=0; i<MAXSTARPTX; i++) {
		//initiialize the particles
		if (ptx[i].halflife == 0 ) {
			}
		}
		
		//update the particles
		else if (ptx[i].halflife > 0 && ptx[i].halflife < FPS) {
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
