<p align="center" width="100%">
    <img width="33%" src="https://github.com/psykoshi-uaa/CS201-Project/blob/main/resources/github_title.png">
</p>

___

### CS201-Project
  This project is a creative assignment from Computer Science 201 at University of Alaska Anchorage. Starcaller is an incremental space-faring game. You fly to planets and click buttons that represent missions. Those missions will consume time until the repo men get you and increase your currency based on upgrades bought at the market. Make sure to pay off your debt before it's game over!

### Controls
[Left Click] - display planet orbits and select missions and markets buys

[Right Click] - move to planets and change payment increment for 'pay debt'

### GUI
  We will be using RAYLIB in order to incorporate a Graphical User Interface for our game. This is a minimalist GUI library that will require us to have an understanding of what is going on with the windows and graphics behind the scenes, unlike with QT.

### Player Choice
  The player has agency in making the best decision as a space pilot. They will choose which mission they should take in order to maximize their mission rewards based on ship market upgrades that will affect the outcome of the varied missions.

### 1. Home
- Upgrades, ship and character.
- Money, debt and income (especially if the player acquires a constant income upgrade).
- Market, buy and sell.
- Jobs, Missions/increment grind.

The port that circles the sun is where you can find all of the market upgrades and pay off your debt. The debt button has the extra funcionality of changing payment increment based on if you right click.

### 2. Mission
 - Oddjob
 - Gather
 - Salvage
 - Bounty
 - Raid

Each planet has a number of mission depending on it's distance from the sun as well as one catch all planet in case no planets are generated far enough from the sun. The missions have varying degrees of time cost and rewards that are calculated against the players upgrades. Bounty missions require 1 weapon and Raids require 2 weapons.
	

### 3 Market
The market supplies upgrades for ship (thrusters, lasers, etc.) that either unlock new mission types, money yield, ship speed, and reduce time taken from doing a mission. A reliably available upgrade is extra money per “odd job” click. This loop continues until player pays off debt or GAME OVER.

### Outro
The game will terminate when the player pays off their debt or the debt increases too much. Different text will display depending on outcome.


# HOW TO BUILD
In order to build you will need to install the raylib library following the raylib installation following the build and installation in the [raylib github](https://github.com/raysan5/raylib).
If you are on windows and using a minGW toolchain run this commandline:

```g++ -o starcaller main.cpp src/star.cpp src/particles.cpp src/solarsystem.cpp src/mission.cpp src/marketupgrade.cpp src/ship.cpp -lraylib -lgdi32 -lwinmm```

If you are on MacOS use this commandline:

```CS201-Project % clang++ -std=c++17 -I/opt/homebrew/opt/raylib/include -L/opt/homebrew/opt/raylib/lib -lraylib src/marketupgrade.cpp src/particles.cpp src/ship.cpp src/solarsystem.cpp src/mission.cpp src/star.cpp main.cpp -o starcaller```
