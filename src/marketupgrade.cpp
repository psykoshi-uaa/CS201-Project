#include "../include/star.h"

//======================================
//     MarketUpgrade Class Imp File
//======================================

    // Constructor
MarketUpgrade::MarketUpgrade(std::string name, float tier, std::string type, int cost, Rectangle button) 
    : name(name), tier(tier), type(type), cost(cost), button(button) {
	isMax = false;
}

// =============
//    Methods
// =============

void MarketUpgrade::DrawButton(){
    // Rectangle

    if (isMax){
        DrawRectangleRec(button, DARKGRAY);
    } else { 
        DrawRectangleRec(button, GRAY);
    }

    // text display
    //tier text
    std::ostringstream tierStream;
    tierStream.precision(1);
    tierStream << std::fixed << tier;
    std::string tier_text = ("TIER " + tierStream.str() + " Upgrade");


    std::string name_text = name;
    std::string type_text = type;

    //percent text
    std::ostringstream percentStream;
    percentStream.precision(0);
    percentStream << std::fixed << (tier * 100);

    std::string reward_percent_text = " + " + percentStream.str() + "% " + type_text; // const TIER * 100 should result in percent form
    std::string time_percent_text = " - " + percentStream.str() + "% " + type_text;
    std::string cost_text = "$" + std::to_string(cost);
    std::string maxxed_text = "MAX TIER";
    

    if (!isMax){ // if !maxxed, display text normally

            // display tier
        DrawText(tier_text.c_str(), button.x + 10, button.y + 10, 20, YELLOW);
            // display effect
        if (type == "reward"){
            DrawText(reward_percent_text.c_str(), button.x + 10, button.y + 40, 20, GREEN);
        }
        if (type == "timeCost"){
            DrawText(time_percent_text.c_str(), button.x + 10, button.y + 40, 20, GREEN);
        }
        
            //display name
        DrawText(name_text.c_str(), button.x + 10, button.y + 60, 20, GRAY);
            // display cost
        DrawText(cost_text.c_str(), button.x + 10, button.y + 80, 20, RED);

        } else { // if maxxed, display MAX

            // display max
        DrawText(maxxed_text.c_str(), button.x + 10, button.y + 10, 40, PURPLE);
        }
        
        //sample
    
   /* 
    "TIER 1 Upgrade:" (yellow) tier
    "+5% move speed" (green) percent, type
    "Extra Booster" (grey) name
    "$5000" (red) cost
   */

} // END DRAWBUTTON

bool MarketUpgrade::IsClicked(){
    //click handling
    if (!isMax && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button))
        {
            return true;
        }
    return false;
} 

void MarketUpgrade::BuyUpgrade(Player& player){ // not sure if I need to include max handling
    if (IsClicked()){
        
            // reward upgrade
        if (type == "reward"){ // if mission type is reward...
            reward_upgrade_counter += 1;
            player.reward_upgrade_tier = tierPercentage[reward_upgrade_counter];
        } else if (type == "timeCost") { // timeCost upgrade
            timeCost_upgrade_counter += 1;
            player.timeCost_upgrade_tier = tierPercentage[timeCost_upgrade_counter];
        }   
    // charge player
    player.setMoney(player.money - cost);
    }
}



