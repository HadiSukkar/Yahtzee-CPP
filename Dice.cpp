#include"Dice.h"
#include <iostream>
#include <cstdlib>

Dice::Dice(){
    value = 0; //This is a value that is not possible for a dice but is the default value to indicate that it is not yet rolled.
    lock = false; //This value denotes whether the player is keeping a dice they rolled.
    srand(time(NULL));
}

/* A method to roll the dice. */
void Dice::rollDice(){
    if (!lock){value = rand()%6 + 1;}
};

int Dice::getValue(){
    return value;
};

/* A method to reset the object back to an unlocked state. */
void Dice::reset(){
    lock = false;
};

/* A method to turn on a 'lock' that prevents rollDice from executing. */
void Dice::keep(){
    lock = true;
};