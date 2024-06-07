#include "star.h"
using namespace std;


Player::Player(string inp_name) {
	name = inp_name;
	flight_class = 1;
	rep_cap = (flight_class * 5) + flight_class;
}
void Player::add_rep(short int rep_to_add){	
	if (rep_to_add + rep > rep_cap){
		rank_up();
		rep = 0 + (rep_to_add - (rep_cap - rep));
	}
	else{
		rep += rep_to_add;
	}
}
void Player::rank_up(){
	flight_class++;
	rep_cap = (flight_class * 5) + flight_class;
	//Genererate congratulatory message
}


Weapon::Weapon(string id_type, string id_model) {
	model = id_model;
	type = id_type;
	full_name = id_type + " " + id_model;
	
	if (type == "low impact"){
		fire_rate = 4.7;
		base_damage = 0.25;
		damage_scaling[0] = 1;
		damage_scaling[1] = 0.7;
		damage_scaling[2] = 0.1;
	} 
	
	else if (type == "high impact"){
		fire_rate = 1.2; 
		base_damage = 1.8;
		damage_scaling[0] = 1;
		damage_scaling[1] = 0.9;
		damage_scaling[2] = 0.1;
	}

	else if (type == "laser"){
		fire_rate = 2.1; 
		base_damage = 3.7;
		damage_scaling[0] = 1.4;
		damage_scaling[1] = .7;
		damage_scaling[2] = 0.7; 
	}
}
