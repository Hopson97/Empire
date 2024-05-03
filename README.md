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

    SIMULATION BEGINS
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

## Building and Running

### Windows (Visual Studio)

The easiest way to build is to use [vcpkg](https://vcpkg.io/en/index.html) and install libraries through this:

```bash
vcpkg install sfml
vcpkg integrate install
```

Then open the Visual Studio project file, and it should build.

### Linux

Requires conan.

```sh
python3 -m pip install conan==1.61.0
```

To build, at the root of the project:

```sh
sh scripts/build.sh install
```

The install argument is only needed for the first time compilation as this is what grabs the libraries from Conan.

So after the first time, you can simply run:

```
sh scripts/build.sh
```

To run, at the root of the project:

```sh
sh scripts/run.sh
```

To build and run in release mode, simply add the `release` suffix:

```sh
sh scripts/build.sh release
sh scripts/run.sh release
```
