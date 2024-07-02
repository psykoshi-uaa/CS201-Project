#ifndef STAR_H
#define STAR_H

#include "raylib.h"
#include <string>

//MODULAR VARIABLES, STRUCTS, ENUMS
typedef enum GameScreen  { LOGO = 0, TITLE, MAINMENU, GAMEPLAY } GameScreen;
typedef enum MenuOptions { NEWGAMEBTN = 0, EXITBTN } MenuOptions;
typedef enum HubButtons	 { MISSIONBOARD, STATUS, MARKET, GIVEUP } HubButtons;
typedef enum Missions	 { ODDJOB = 0, GATHER, SALVAGE, BOUNTY, RAID } Missions;

typedef struct GUIbtn {
	Rectangle position;
	Vector2 origin;
} GUIbtn;

extern GameScreen currentScreen;

#define FPS 60
#define MAINMENUFONTSIZE 25
//END OF MODULAR VARIABLES

//player, ship, mission classes
class Player {
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



/* backup
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
*/
