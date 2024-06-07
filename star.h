
#ifndef STAR_H
#define STAR_H

#include <string>

using namespace std;

class Player{
	private:
	string 		name;
	short int 	flight_class, rep, rep_cap;

	public:
	string get_name() {return name;}
	short int get_flight_class() {return flight_class;}
	void add_rep(short int);
	void rank_up();
	Player(string inp_name);
};


class Weapon{
	private:
	string	full_name, model, type;
	float	base_damage, fire_rate,

		damage_scaling[3];
		//damage_scaling refers to damage againts specific armor
		//damage scaling list:
			//unarmored: 0
			//reinforved: 1
			//energy: 2

	public:
	string get_model() {return model;}
	string get_type() {return type;}
	string get_name() {return full_name;}
	float calculate_damage(short int);
	Weapon(string id_type, string id_model);
};

#endif

