#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include "Dice.h"
#include "Scoreboard.h"
using namespace std;

const int REROLL = 2;

//Simulates a game of yahtzee with just the user as the player. Game ends when the score card is filled out.
int main() {
    Dice dice[5];
    int roll = 0;
    char keep[50], lock[50];
    bool flag = false;
    ScoreBoard scoreboard;
    do{ // This loop basically goes until all the parts of the score card are filled out or "locked in".
        do{ // This is essentially a loop in the game of yahtzee where the player will roll the dice and keep any number of them and reroll the ones they don't keep up to two times.
            for (int i = 0; i < 5; i++){
                dice[i].rollDice();
                dice[i].reset();
            }
            for (int i = 0; i < 5; i++){
                if (i != 4){
                    printf("%d ", dice[i].getValue());
                }
                else{
                    printf("%d\n", dice[i].getValue());
                }
            }
            if (roll != REROLL){ //The part of the program where the user is asked which dice they'd like to keep.
                printf("What dice would you like to keep? They are ordered (A, B, C, D and E). If you would like to keep them all, you can simply enter in N and no more rerolls will be executed.\n");
                fgets(keep, 50, stdin);
                for (int i = 0; i < strlen(keep); i++){
                    keep[i] = toupper(keep[i]);
                    if (int(keep[i])>=int('A') && int(keep[i])<=int('N')){
                        if (int(keep[i]) == int('N')){
                            roll = REROLL; //Ensures exiting of while loop
                            break;
                        }
                        else{
                            int diff = int(keep[i]) - int('A');
                            if (diff >= 0 && diff <= 4){
                                dice[diff].keep();
                            }
                        }
                    }
                }
            }
            roll++;
        }while (roll <= REROLL);
        roll = 0;
        int values[5]; // Collects the value of the dice into an array for more easily accessible use in the socreboard class.
        for (int i = 0; i < 5; i++){
            values[i] = dice[i].getValue();
        }
        scoreboard.newRoll(values);
        scoreboard.showScores();
        do{ // Loops until the user makes a valid choice as to what category to lock in their score.
            cout << "Please choose a section to lock in:" << endl;
            fgets(lock, 50, stdin);
            for (int i = 0; i < strlen(lock); i++){
                lock[i] = toupper(lock[i]);
            }
            flag = scoreboard.lock(lock);
        }while(!flag);
        flag = false;
    } while (!scoreboard.fullLock());
    cout << "Your final score is: " << scoreboard.tally() << endl;
}