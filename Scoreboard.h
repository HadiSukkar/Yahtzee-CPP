#include <iostream>
using namespace std;

class ScoreBoard
{
    private:
        int diceValues[5];
        int count[6];
        struct score{
            bool unlock;
            int value;
        }scoreValues[13];
    public:
        ScoreBoard();
        void newRoll(int[]);
        void showScores();
        int upper(int);
        int ofAKind(int);
        bool fullHouse();
        bool straight(int);
        int chance();
        int sum();
        bool fullLock();
        bool lock(char[50]);
        int tally();
};