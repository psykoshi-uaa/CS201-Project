#ifndef STAR_H
#define STAR_H

#define _USE_MATH_DEFINES

//includes
#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include <cmath>
#include <string>
#include <random>

//defines
#define FPS 60
#define MAINMENUFONTSIZE 30
#define HUBNUMBTNS 4
#define HUBMAINFONTSIZE 36
#define HUBSUBFONTSIZE 24
#define HUBBTNWIDTH 250
#define HUBBTNHEIGHT 40 
#define BOARDNUMBTNS 5
#define BOARDMAINFONTSIZE 50
#define BOARDSUBFONTSIZE 24
#define BOARDBTNWIDTH 300
#define BOARDBTNHEIGHT 60
#define SBARHEIGHT 30
#define SBARFONTSIZE 22
#define SBARNUMSEGS 2
#define NUMPLANETS 7
#define MAXSTARPTX 400
#define ORBITALPOINTS 10
#define ORBITALPOINTSFULL 50
#define PLANETBOUNDS 100
#define NUMALPHACHANNELS 10
	  
const int SCREENWIDTH = 1920,
          SCREENHEIGHT = 1080;

const float SBARSEG[SBARNUMSEGS] = {180, 400},
			MARGIN = 30,
			BTNPADDING = 2;


//enums
typedef enum GameScreen  { LOGO = 0, TITLE, MAINMENU, INTRO, HUB, BOARD, PLAYERSHEET, GAMEOVER, SUCCESS } GameScreen;
typedef enum Buttons { NOBTN, NEWGAMEBTN, EXITBTN,
			BOARDBTN, MARKETBTN, STATUSBTN, GIVEUPBTN,
			ODDJOBBTN, GATHERBTN, SALVAGEBTN, BOUNTYBTN, RAIDBTN,
			BACKBTN
} Buttons;


//structs
typedef struct GUIbtn {
	Rectangle border;
	Vector2 origin;
} GUIbtn;

typedef struct PTXstar {
	float dist;
	int life;
	Vector2 pos;
	Color color;
	float alpha;
} PTXstar;

//global variables
extern GameScreen currentScreen;
extern Buttons btnHovered;
extern Font sagaFont;

//functions
float GetDist(Vector2, Vector2);


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

class Ship {
    Vector2 position,
	    velocity,
	    destination;
	
    public:
    Ship();
    void DrawSelf(float, Color);
    void UpdateDestination(Vector2);
};


//-------------------------------------------------------------------------------
//			solar system and planet classes
//-------------------------------------------------------------------------------
class Sun {
	public:
	Vector2 sunPos;
	float sunRadius;
	bool sunClicked;

	Sun();
	void DrawSun();
};

class Planet : private Sun {
	private:
	float mass,
	      radius,
	      orbitAngle,
	      orbitDistance,
	      orbitRadius,
	      conicScale,
	      conicRotation,
	      distFromMouse,
	      distFromSun,
	      alpha;
	Vector2 pos,
		angle,
		axisLengths,
		orbitPointsFull[ORBITALPOINTSFULL],
		orbitPointsAhead[ORBITALPOINTS],
		orbitPointsBehind[ORBITALPOINTS];
	Color color,
	      orbitColor;
	bool orbitOn;


	public:
	Planet();
	void DrawPlanet(bool);
	void UpdatePlanet();
	void RegisterClick();
};


//-------------------------------------------------------------------------------
//			particle classes
//-------------------------------------------------------------------------------
class PTXstarmanager {
	private:
	PTXstar ptx[MAXSTARPTX];
	char starFX[3];
	float lifetime;
	Vector2 area;
	int counter, updateTime;
		//functions
	void GenerateStar(PTXstar&);
	void UpdateSelf(PTXstar&);
	void DrawSelf(PTXstar&);

	public:
	PTXstarmanager();
	void LifeCycle();
};


//-------------------------------------------------------------------------------
//			code utility classes
//-------------------------------------------------------------------------------
class MapPlanetMenu {
	Rectangle dimensions;
};

class Timer {
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
		
