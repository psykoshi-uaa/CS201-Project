/* This class defines a D6, more options can be added
if balancing would be better with a D20 or something

#include <cstdlib>
#include <ctime>
#include <iostream>



class Dice 
{
public:
    Dice() {
        //seeding number properly
        static bool seeded = false;
        if (!seeded) 
        {
            std::srand(std::time(nullptr));
            seeded = true; 
        }  
    }
    
    int rollD6(int numRolls = 1)
    {
        int total = 0;
        for (int i = 0; i < numRolls; ++i)
        {
            total += std::rand() % 6 + 1;
        }
        return total;
    }
};

// example usage

int main()
{
    Dice dice;
    
    int piloting = 7;
    int roll = dice.rollD6(2);

    std::cout << "---- Piloting skillcheck ----" << std::endl;
    std::cout << "Press enter: " << std::endl;
    std::cin.get();
    std::cout << "You rolled: " << roll + piloting;
    

    return 0;
}
*/
