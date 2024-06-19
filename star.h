
#ifndef STAR_H
#define STAR_H


#include <string>


class Player{
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


class Weapon{
	private:
	std::string	fullName,
			model,
			type;
	double		baseDamage,	
			fireRate,
			damageScaling[3];
		//damageScaling refers to damage againts specific armor
		//damage scaling list:
			//unarmored:	[0]
			//reinforved:	[1]
			//energy:	[2]

	public:
	std::string 	getModel() {return model;}
	std::string	getType() {return type;}
	std::string	getName() {return fullName;}
	double 		calculateDamage(short int);
	Weapon(std::string idType, std::string idModel);
};


class Drill{
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


class CargoBay{
	private:
	double		maxWeight;

	public:
	double		getWeight();
};

#endif

