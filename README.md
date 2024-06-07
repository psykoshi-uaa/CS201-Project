# CS201-Project
This project is a creative assignment from Computer Science 201. We will be creating a space-faring game of sorts. The goal of our game is to build resources that generate idly, allowing you to build more advanced resoure generation tools for your ship and allow you to take on more dangerous missions. 

## Quick-Tutorial:
This quick-tutorial is to relay some of the info that I have learned and am utilizing.

### GitHub
GitHub is one of many tools used in order to use git. Another example of a tool that uses git is Bitbucket. I recommend downloading the GitHub desktop tool from GitHub and then selecting the repository CS201-Project. It will allow us to share files with ease.
1. Pull (grab latest changes)
2. Add (files to be changed or added)
3. Commit (registers changes to be made with a note)
4. Push (Pushes all committed changes to the main repository)
There is more to be said on branching but we can get to that in the future when it is necessary. Think of branching as different save states.

### Header File
The header file is used to declare functions and classes as well as the functions and variables within the classes. It looks like:

___
```
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
    
}; note the semicolon to end this class declaration

#endif
```
___

The #ifdef and #define tell the compiler to only compile the code that is read until #endif ONCE. That way when we call the header in the implementation AND source code file it does not add the header code to compile twice.


### Implementation File
The implementation file is where we DEFINE the functions, class functions, and class constructors. This makes for generally cleaner code. In the implementation file you will notice the Player::Player or Player::get_name(string inp). These tell the compiler that we are going to be defining a variable within the scope of the class Player. Player::Player is not a function however and is the constructor for the class. It is code that will run for each object declared for that class.


### Main File
The main source code file is where everything is brought together.
