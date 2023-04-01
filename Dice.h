#include <iostream>
using namespace std;

class Dice
{
    private:
        int value;
        bool lock;
    public:
        Dice();
        void rollDice();
        int getValue();
        void reset();
        void keep();
};