# Yahtzee-CPP
A simple program to simulate the game of Yahtzee for a single player for the express purpose of learning how to use C++. The simulation is fairly simple, it will roll a set of 5 dice and give the option to pick any combination of the 5 dice to keep. This is asked through an input where each dice has a corresponding letter (A, B, C, D and E respectively). They will reroll any dice they do not keep up to two times. They can change what dice they keep after each reroll.

After they are finished rolling they are presented with a scorecard of yahtzee score categories with the corresponding score they'd get for each category if they were to choose that category. They then lock in a category and that score is locked in for the remainder of the game (and will not change in future displays of the scoreboard).

The user then repeats this process until all categories are locked in. After all categories are locked in, the game will end and the user will be presented with their total tallied score.

This is a rather simple program and so is missing some capabilities. Namely, only one player can play. Additionally, it is a user that has to be playing and the program will not play for the user. Such a change would be an interesting source for improvement of the program but would likely require some heftier statistical implementation that would vary for each category of scoring.
