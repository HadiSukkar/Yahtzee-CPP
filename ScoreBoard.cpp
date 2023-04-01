#include"Scoreboard.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;

char categories[13][50] = {"ACES", "TWOS", "THREES", "FOURS", "FIVES", "SIXES", "3 OF A KIND", "4 OF A KIND", "FULL HOUSE", "SM STRAIGHT", "LG STRAIGHT", "YAHTZEE", "CHANCE"};

/* Same as newRoll except since it is initialized it leaves all the score values as unlocked since the game has presumably just started.*/
ScoreBoard::ScoreBoard(){
    for (int i = 0; i < 13; i++){
        scoreValues[i].value = 0;
        scoreValues[i].unlock = true;
    }
};

/* A method to take all the rolls and add them all to an array of integer values with the tally of each result of the dice. */
void ScoreBoard::newRoll(int input[5]){
    for (int i = 0; i < 6; i++){
        count[i] = 0;
    }
    for (int i = 0; i < 5; i++){
        diceValues[i] = input[i];
        count[input[i]-1]++;
    }
};

/* 
A more complex method that accesses all the other methods in the class with the end-goal of showing the user all their accumulated scores
and potential scores they might achieve by locking in a slot they haven't yet locked in. If a slot is already locked, it will show the old value
and the method will not assess the value with the new results. Since each score category works differently, there has to be a method for assigning each
attribute and cannot be simply looped through.
*/
void ScoreBoard::showScores(){
    cout << left << setw(15) << "Section" << left << setw(10) << "Score" << endl;
    for (int i = 0; i < 6; i++){
        if (scoreValues[i].unlock) {scoreValues[i].value = upper(i+1);}
    }
    for (int i = 6; i < 8; i++){
        if (scoreValues[i].unlock) {scoreValues[i].value = ofAKind(i-3);}
    }
    if (scoreValues[8].unlock) {
        scoreValues[8].value = (fullHouse()) ? 25 : 0;
    }
    for (int i = 9; i < 11; i++){
        if (scoreValues[i].unlock){
            scoreValues[i].value = (straight(i-5)) ? (i-6)*10 : 0;
        }
    }
    if (scoreValues[12].unlock){
        scoreValues[12].value = sum();
    }
    if (ofAKind(5) > 0){
        scoreValues[11].value = (scoreValues[11].value == 0) ? 50 : scoreValues[11].value + 100;
    }
    for (int i = 0; i < 13; i++){
        cout << left << setw(15) << categories[i] << left << setw(10) << scoreValues[i].value << endl;
    }
};

/* 
A method to obtain the score out of the upper section of the yahtzee scorecard. In this section all of a corresponding number rolled that corresponds
the number input into the parameter will be totalled together.
*/
int ScoreBoard::upper(int number){
    return number*count[number-1];
};

/*
A method to obtain the score for the categories that include getting the parameter number of rolls of a kind. For example, 3 of a kind would have a parameter
of number = 3 and the method would identify whether there exists three of the same number from the set of input rolls. If such a set exists within the set of rolls
then the sum of all the numbers rolled will be returned, otherwise 0 will be returned.
*/
int ScoreBoard::ofAKind(int number){
    for (int i = 0; i < 6; i++){
        if (count[i] >= number) {return sum();}
    }
    return 0;
};

/*
A method to obtain whether a full house was achieved given the set of rolls. A full house is a unique set of rolls in which there are three of a kind of a distinct
number and two of a kind of a different but also distinct number.
*/
bool ScoreBoard::fullHouse(){
    bool two = false, three = false;
    for (int i = 0; i < 6; i++){
        if (count[i] == 2) {two = true;}
        if (count[i] == 3) {three = true;}
    }
    return (two && three);
};

/*
A method to obtain whether a straight was achieved given the set of rolls. The parameter indicates the size of the straight required. A straight is essentially
a set of dice rolls in which a subset of the numbers rolled can form a sequence where each consecutive number increases by 1. A small straight (or SM straight)
is a straight of size 4. In practice this would only be a roll where the subsets (1,2,3,4) or (2,3,4,5) or (3,4,5,6) exist. A large straight (or LG straight)
is a straight of size 5. In practice this would only be when the user rolls either (1,2,3,4,5) or (2,3,4,5,6).
*/
bool ScoreBoard::straight(int number){
    int consecutive = 0, max = 0;
    for (int i = 0; i < 6; i++){
        if (count[i] > 0){
            consecutive++;
            if (consecutive > max) {max = consecutive;}
        }
        else {consecutive = 0;}
    }
    return (max >= number);
};

/*
Sums all the input dice.
*/
int ScoreBoard::sum(){
    int acc = 0;
    for (int i = 0; i < 5; i++){
        acc += diceValues[i];
    }
    return acc;
};

/*
A method that indicates whether every part of the scoreboard is locked or not.
*/
bool ScoreBoard::fullLock(){
    for (int i = 0; i < 13; i++){
        if (scoreValues[i].unlock) {return false;}
    }
    return true;
};

/*
A method that will lock a specific category based on a string input. Notably this method returns a boolean because the user can input an invalid
input. This can either be an incorrect category or a category that has already been locked.
*/
bool ScoreBoard::lock(char choice[50]){
    int i;
    for (i = 0; i < 13; i++){
        if (strncmp(choice, categories[i], strlen(categories[i])) == 0){
            break;
        }
    }
    if (i == 13 || !scoreValues[i].unlock) {return false;}
    else {
        scoreValues[i].unlock = false;
        return true;
    }
};

/*
A method that will total the score achieved in each category of the scoreboard.
*/
int ScoreBoard::tally(){
    int upper = 0, lower = 0;
    for (int i = 0; i < 6; i++){
        upper += scoreValues[i].value;
    }
    if (upper >= 63) {upper += 35;} //Notably in yahtzee, if the total of your upper section exceeds 63 points, you also gain an additional 35 points.
    for (int i = 6; i < 13; i++){
        lower += scoreValues[i].value;
    }
    return (upper + lower);
};