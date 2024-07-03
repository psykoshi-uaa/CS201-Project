#ifndef STAR_H
#define STAR_H

//includes
#include "raylib.h"
#include "raymath.h"
#include <string>

//defines
#define FPS 60
#define MAXBTNS 8
#define MAINMENUFONTSIZE 30
#define HUBMAINFONTSIZE 72
#define HUBSUBFONTSIZE 12
#define HUBBTNWIDTH 300
#define HUBBTNHEIGHT 180
#define STATUSBARHEIGHT 14
#define MARGIN 50

//enums and structs
typedef enum GameScreen  { LOGO = 0, TITLE, MAINMENU, HUB, BOARD, PLAYERSHEET, GAMEOVER, SUCCESS } GameScreen;
typedef enum Buttons {	NOBTN, NEWGAMEBTN, EXITBTN,
			MISSIONBOARD=10, MARKET=11, STATUS=12, GIVEUP=13,
			ODDJOB=20, GATHER=21, SALVAGE=22, BOUNTY=23, RAID=24
} Buttons;

typedef struct GUIbtn {
	Rectangle position;
	Vector2 origin;
} GUIbtn;

//global variables
extern GameScreen currentScreen;
extern Buttons btnHovered;


//-------------------------------------------------------------------------------
//player, ship, and mission classes
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



//code utility classes
class Timer {
	private:
	int		frameCounter;
	static double	waitTime;

	public:
	int	GetCounter();
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
