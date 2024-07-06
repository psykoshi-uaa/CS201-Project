#ifndef STAR_H
#define STAR_H

//includes
#include "raylib.h"
#include "raymath.h"
#include <string>

//defines
#define FPS 60
#define MAINMENUFONTSIZE 30
#define HUBNUMBTNS 4
#define HUBMAINFONTSIZE 36
#define HUBSUBFONTSIZE 12
#define HUBBTNWIDTH 250
#define HUBBTNHEIGHT 40 
#define SBARHEIGHT 30
#define SBARFONTSIZE 22
#define SBARNUMSEGS 2

const float SBARSEG[SBARNUMSEGS] = {180, 400};
const float MARGIN = 30;

//enums and structs
typedef enum GameScreen  { LOGO = 0, TITLE, MAINMENU, HUB, BOARD, PLAYERSHEET, GAMEOVER, SUCCESS } GameScreen;
typedef enum Buttons {	NOBTN, NEWGAMEBTN, EXITBTN,
			MISSIONBOARD, MARKET, STATUS, GIVEUP,
			ODDJOB, GATHER, SALVAGE, BOUNTY, RAID
} Buttons;

typedef struct GUIbtn {
	Rectangle border;
	Vector2 origin;
} GUIbtn;

//global variables
extern GameScreen currentScreen;
extern Buttons btnHovered;

//-------------------------------------------------------------------------------
//			player, ship, and mission classes
//-------------------------------------------------------------------------------
class Player {
	private: 
	std::string	name;
	std::string Class;
	int money;
	int debt;
	int HP;
	const int maxHP;
	bool hasShield;
	int SP;
	int piloting;
	int repair;
	int bartering;

	public:
	std::string getName();
	int getMoney();
	int getDebt();
	int getHP();
	int getSP();
	void getSkills(int&, int&, int&);

};


//-------------------------------------------------------------------------------
//			code utility classes
//-------------------------------------------------------------------------------
class Timer {
	private:
	float		frameCounter;
	static double	waitTime;

	public:
	float	GetCounter();
	void	Reset();
	void	Run();
	bool 	Wait(double);
};

class Dice {
	public:
	Dice();
	int rollD6(int);
};


#endif
		
