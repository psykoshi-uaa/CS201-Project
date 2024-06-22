#ifndef STAR_H
#define STAR_H


typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY } GameScreen;

#define FPS 60

extern GameScreen currentScreen;

#include <iostream>
#include <string>


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
	void	Reset();
	void	Run();
	bool 	Wait(double);
};

#endif
