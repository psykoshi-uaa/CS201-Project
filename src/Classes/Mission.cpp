#include "star.h"

//====================================
//     Mission Class Imp File
//====================================

    // Constructor FIXME
Mission::Mission(std::string name, int reward, int timeCost, float cooldownTime, Rectangle rect)
    : name(name), reward(reward), currentCooldown(0), button(rect), onCooldown(false) {}

// Getters
std::string Mission::getName(){
    return name;
}
int Mission::getReward(){
    return reward;
}
int Mission::getTimeCost(){
    return timeCost;
}
float Mission::getCooldownTime(){
    return cooldownTime;
}
float Mission::getCurrentCooldown(){
    return currentCooldown;
}

// Setters
// assign class attributes with given arguments

void Mission::setName(std::string& missionName){
    name = missionName;
}
void Mission::setReward(int missionReward){
    reward = missionReward;
}
void Mission::setTimeCost(int timeCost){
    timeCost = timeCost;
}
void Mission::setCooldownTime(float cooldownTime){
    cooldownTime = cooldownTime;
}
void Mission::setCurrentCooldown(float currentCooldown){
    currentCooldown = currentCooldown;
}


//      =======
//      Methods
//      =======

//COOLDOWN START METHOD
void Mission::startCooldown(){
    onCooldown = true;
    currentCooldown = cooldownTime;
}
// TIMER UPDATE METHOD
void Mission::updateTimer(float deltaTime){
    if (onCooldown)
    {
        currentCooldown -= deltaTime;
        if (currentCooldown <= 0)
        {
            onCooldown = false;
            currentCooldown = 0;
        }
    }
} // Deltatime?

// BUTTON METHODS : WORK IN PROGRESS
void Mission::DrawButton(){
    if (onCooldown)
    {
        DrawRectangleRec(button, DARKGREEN);
    } else 
    {
        DrawRectangleRec(button, GRAY);
    }
    
    std::string yeild_text =  "Yeild: " + std::to_string(reward); // adaptable text for yeild
    std::string time_cost_text = "Time Cost: " + std::to_string(timeCost); // text for timecost
    std::string cooldown_text = "Cooldown: " + std::to_string(currentCooldown); // text for cooldown timer

    //draw mission name
    DrawText(name.c_str(), button.x + 10, button.y + 10, 20, BLACK);
    //draw mission yeild
    DrawText(yeild_text.c_str(), button.x + 10, button.y + 40, 20, GREEN);
    //draw time cost
    DrawText(time_cost_text.c_str(), button.x + 10, button.y + 60, 20, RED);
    //draw cooldown timer
    DrawText(cooldown_text.c_str(), button.x + 10, button.y + 80, 20, GRAY);
}

bool Mission::IsClicked()
{
    //click conditions
    if (!onCooldown && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button))
    {
        return true;
    }
    return false;
}



// Need to fill out player class to integrate
// COMPLETE MISSION: ADD REWARD AND TAKE TIME FROM PLAYER

void Mission:: CompleteMission(Player& player)
{
    if (!onCooldown)
    {
        player.addMoney(reward);
        player.loseTime(timeCost);
        startCooldown();
    }
}

