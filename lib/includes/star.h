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
#define HUBSUBFONTSIZE 24
#define HUBBTNWIDTH 250
#define HUBBTNHEIGHT 40 
#define SBARHEIGHT 30
#define SBARFONTSIZE 22
#define SBARNUMSEGS 2
#define MAXSTARPTX 100
	  
const int SCREENWIDTH = 800,
          SCREENHEIGHT = 800;
			  
const float SBARSEG[SBARNUMSEGS] = {180, 400},
			MARGIN = 30,
			BTNPADDING = 2;

//enums and structs
typedef enum GameScreen  { LOGO = 0, TITLE, MAINMENU, INTRO, HUB, BOARD, PLAYERSHEET, GAMEOVER, SUCCESS } GameScreen;
typedef enum Buttons { NOBTN, NEWGAMEBTN, EXITBTN,
			BOARDBTN, MARKETBTN, STATUSBTN, GIVEUPBTN,
			ODDJOBBTN, GATHERBTN, SALVAGEBTN, BOUNTYBTN, RAIDBTN,
			BACKBTN
} Buttons;

typedef struct GUIbtn {
	Rectangle border;
	Vector2 origin;
} GUIbtn;

//global variables
extern GameScreen currentScreen;
extern Buttons btnHovered;
extern Font sagaFont;

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
	int getPilot();
	int getRepair();
	int getBarter();

	Player() 
	: name("Unknown"), Class("Unknown"), money(0), debt(1000000), HP(0), maxHP(25), hasShield(false), SP(0), piloting(0), repair(0), bartering(0) {
    }
};


//-------------------------------------------------------------------------------
//			code utility classes
//-------------------------------------------------------------------------------
class Timer {
	private:
	float	frameCounter;
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
		
