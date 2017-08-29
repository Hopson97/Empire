cmake_minimum_required (VERSION 3.0.2)
project (Empire)
add_executable (empire 
./Source/main.cpp
./Source/ResourceManager/ResourceHolder.cpp
./Source/Sim/World.cpp
./Source/Sim/Person.cpp
./Source/Sim/Colony.cpp
./Source/Application.cpp
./Source/Util/Common.cpp
./Source/Util/Random.cpp)
target_link_libraries (empire -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -lpthread)
file(COPY Res colours.txt config.txt DESTINATION ${CMAKE_BINARY_DIR})

