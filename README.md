# EMPIRE

This is my own cellular automaton

The rules are as follows:

    -The world is made out a grid of cells aka "people"
    -Each person holds some numbers:
        -Age
        -Strength
        -Reproduction Value
        -Colony ID

    -Each person also holds some booleans
        -Whether they are alive or dead
        -Whether they are diseased or not

    -At the start:
        -A few "colonies" are set up. Each colony has their own colour value
        -A few random locations around a map are set up, for each colony to originate from
        -50 people are placed are each of these locations, and are given the respective colony ID

    SIMULATTION BEGINS
        -Each step:
            -Each person:
                - Increases in "Age" and "Reproduction Value"
                - Has a 50% chance of being cured of disease, given they have it
                - Tries to move to a random spot around them:
                    -If they try move onto water, they will not move
                    -If they try move onto land, they will move there

                    -If they try move to a place where someone of a DIFFERENT colony is:
                        -They fight:
                            -Person with higher strength value stays fine.
                            -Person with lower strength value dies.

                    -If they try move to a place where someone of the SAME colony is:
                        -If the person is diseased, then there is a 50% chance of giving/ catching it

                -If the person's "Reproduction Value" is greater than a "Reproduction Threshold"
                    -The person gives birth
                    -The child:
                        -Inherits the parent's Colony ID
                        -Inherits the parent's Strength value
                        -Inherits the parent's Disease (if parent is diseased)
                        -Has a chance of mutating:
                            -Slim Chance        -> Gets diseased
                            -Slightly Larger Chance -> Child is born weaker,


# Deps:

C++14 and up, SFML 2.4.1 and up
