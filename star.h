#ifndef STAR_H
#define STAR_H

#include "raylib.h"
#include <string>


typedef enum GameScreen { LOGO = 0, TITLE, MAINMENU, GAMEPLAY } GameScreen;
typedef enum MenuOptions { NEWGAMEBTN = 0, EXITBTN } MenuOptions;

extern GameScreen currentScreen;

#define FPS 60

typedef struct GUIbtn {
	Rectangle position;
	Vector2 origin;
} GUIbtn;


class Player {
	private:
	std::string	name;
	short int 	flightClass,
	      		rep, 
			repCap;

	public:
	std::string getName() {return name;}
	short int getFlightClass() {return flightClass;}
	void addRep(short int);
	void rankUp();
	Player(std::string inpName);
};


class Weapon {
	private:
	std::string	fullName,
			model,
			type;
	double		baseDamage,	
			fireRate,
			damageScaling[3];

	public:
	std::string 	getModel() {return model;}
	std::string	getType() {return type;}
	std::string	getName() {return fullName;}
	double 		calculateDamage(short int);
	Weapon(std::string idType, std::string idModel);
};


class Drill {
	private:
	short int 	level;	
	double 		baseDamage;
	std::string 	name;

	public:
	void 		upgradeDrill();
	short int 	getLevel();
	double 		getDamage();
	std::string	getName();
};


class CargoBay {
	private:
	double		maxWeight;

	public:
	double		getWeight();
};



//code utility classes
class Timer {
	private:
	int	frameCounter = 0;
	static double	waitTime;

	public:
	int	GetCounter();
	void	Reset();
	void	Run();
	bool 	Wait(double);
};

#endif
