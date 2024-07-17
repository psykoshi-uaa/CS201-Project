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
#define MAXSTARPTX 250 
#define NUMPLANETS 7
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

typedef struct PTX {
	int halflife;
	Vector2 pos;
	Color color;
	float alpha,
	      dist;
}PTX;

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
	int timeRemaining;

	public:
	// getters
	std::string getName();
	int getMoney();
	int getDebt();
	int getHP();
	int getSP();
	int getPilot();
	int getRepair();
	int getBarter();
	int getTimeRemaining();

	// setters
	void setName(std::string);
	void setMoney(int);
	void setDebt(int);
	void setHP(int);
	void setSP(int);
	void setPilot(int);
	void setRepair(int);
	void setBarter(int);
	void setTimeRemaining(int);

	// methods
	void addMoney(int);
	void payDebt(int);
	void loseTime(int);


	Player() 
	: name("Unknown"), Class("Unknown"), money(0), debt(-1000000), HP(0), maxHP(25), hasShield(false), SP(0), piloting(0), repair(0), bartering(0) {
    }
};

//====================================
//     Mission Class Header 
//====================================


class Mission
{
    // ==========
    // Attributes
    // ==========
    private:
    std::string name;
    int reward;
    int timeCost;
    float cooldownTime;
    float currentCooldown;
    Rectangle button;
    bool onCooldown;
	

    public:

    // Constructor
    Mission(std::string name, int reward, int timeCost, float cooldownTime, Rectangle rect);

    // Getters
    std::string getName();
    int getReward();
    int getTimeCost();
    float getCooldownTime();
    float getCurrentCooldown();

    // Setters
    void setName(std::string& name);
    void setReward(int reward);
    void setTimeCost(int timeCost);
    void setCooldownTime(float cooldownTime);
    void setCurrentCooldown(float currentCooldown);

    //      =======
    //      Methods
    //      =======

    void startCooldown();
    void updateTimer(float deltaTime);
    void DrawButton();
    bool IsClicked();
    void CompleteMission(Player& player);


};

class Sun {
	public:
	Vector2 sunPos;
	float sunRadius;

	Sun();
	void DrawSun();
};

class Planet : public Sun {
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
	void RegisterPlanetClicked();
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
		
