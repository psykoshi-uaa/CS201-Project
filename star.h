
#ifndef STAR_H
#define STAR_H

#include <string>

class Player{
	private:
	string 		name;
	unsigned int 	flight_class, rep, rep_cap;

	public:
	string get_name() {return name;}
	string get_flight_class() {return flight_class;}
	void add_rep(unsigned int);
	void rank_up();

	Player(string inp_name){
		name = inp_name;
		rep_cap = (flight_class * 5) + flight_class;
	}
};


class Weapon{
	private:
	string	full_name, model, type;
	float	base_damage,
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
}

#endif

