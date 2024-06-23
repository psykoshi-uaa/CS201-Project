# CS201-Project
  This project is a creative assignment from Computer Science 201. We will be creating a space-faring game of sorts. The goal of our game is to build resources that generate idly, allowing you to build more advanced resoure generation tools for your ship and allow you to take on more dangerous missions. 


## GUI
  We will be using RAYLIB in order to incorporate a Graphical User Interface for our game. This is a minimalist GUI library that will require us to have an understanding of what is going on with the windows and graphics behind the scenes, unlike with QT.

## Player Choice
  The player should have agency in making the best decision as a space pilot. They will choose which mission they should take in order to maximize their mission rewards based on ship equipment, currency, and other stats that will affect the outcome of the varied missions.

# GAME LOOP
Game Loop
Intro:
	Title screen appears. Player presses key to begin. Through text interaction player names character. Welcome message appears, introducing the game (this could also come before title screen). Land on home/hub screen.

1. Home:
	The display of Home depends on graphical capability. Functionally it represents the main part of the player’s journey. It should say how much money the player has, and present a of couple option trees. (GUI or text).
	
Upgrades, ship and character. 
Money, debt and income (especially if the player acquires a constant income upgrade). 
Market, buy and sell.
Jobs, Missions/increment grind.

Player should be able to look at their stats here, and current inventory/equipment.

   Player chooses how to proceed. To begin with, player should do 1-3 incremental “jobs” or clicks to just increase money (small chance for big salvage win as well). Player then buys a weapon, tool, whatever to take a mission that has 1 requirement.

! All equipment could be designed as flat stat increases or new capabilities, eliminating the need for a gear-swapping system. 

! Missions can be randomized to a degree but to start they can also just be set “levels” that can be cleared for big payouts.


2. Mission:
	Player takes mission. Mission plays out by giving a text blurb that varies depending on mission type. Last paragraph may vary depending on fail/success. In the background the game compares player stats with mission requirements, and adds the modifier +number depending on weapon/ship bonuses or other stats. (For example, an upgraded laser would provide +3 to the player ‘dice roll’ against an enemy. An upgraded engine would allow the cargo to be transported +2 parsecs faster.) Further interactivity could be brought by making mid-combat choices in a turn based system. (Use different weapons, flee, etc.)
	
	2.5: Display results - 
To start with just displaying results will be good. Display money earned, damage taken (-money to repair). If money falls below debt threshold, GAME OVER. 

	Mission design may take 2 forms: combat and industry/mining/transport. More types can be created for more complexity. Upgrades that give new abilities (cargo hold, anti-gravity, etc.) allow access to these missions. Combat is the high-risk, high reward scenario, whereas the others are lower risk, less reward. Combat carries risk of death, and the increase of your debt. Other options allow you to increase money with very small chance of pirate attack.




3. Back Home
	Player is now back Home, but with more money. They can now buy a new upgrade, stat increase, etc. They may be able to access a new tier of missions with harder difficulty, pay toward their debt, etc.
	3.5 Market
	The market supplies upgrades for ship (thrusters, lasers, etc.) that either unlock 		 new mission types or increase damage stat, money yield, etc. A reliably available upgrade is extra money per “odd job” click. Expensive upgrades may include automation options (money flow per minute from minions?). The market can either be a text menu, a screen of its own, or a popup when money threshold is reached. (Like in incremental games when new things pop up.)


This loop continues until player pays off debt or GAME OVER.

4. Outro
	The game will terminate when the player pays off their debt or the debt increases too much. Different text will display depending on outcome. May display stats, money, etc. Upon player input the window will close.

