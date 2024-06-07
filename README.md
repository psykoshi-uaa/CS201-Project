# CS201-Project
This project is a creative assignment from Computer Science 201. We will be creating a space-faring game of sorts.

The header file is used to declare functions and classes as well as the functions and variables within the classes. It looks like:

________________________________________________________________
#ifndef HEADERNAME_H
#define HEADERNAME_H

#include blah
#include blar

void function_name1(int);
double function_name2(int, double);

class Class_name{
    private:
    private vars go here

    public:
    declare class functions here
    declare class constructor here

}; //note the semicolon to end th class definition

#endif
________________________________________________________________

The #ifdef and #define tell the compiler to only compile the code that is read until #endif ONCE. That way when we call the header in the implementation AND source code file it does not add the header code to compile twice.



The implementation file is where we DEFINE the functions, class functions, and class constructors. This makes for generally cleaner code. In the implementation file you will notice the Player::Player or Player::get_name(string inp). These tell the compiler that we are going to be defining a variable within the scope of the class Player. Player::Player is not a function however and is the constructor for the class. It is code that will run for each object declared for that class.


The main source code file is where everything is brought together.
