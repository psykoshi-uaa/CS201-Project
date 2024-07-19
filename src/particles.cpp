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
