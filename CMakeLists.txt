cmake_minimum_required (VERSION 3.0.2)
project (Empire)
find_package(Threads)
find_package(SFML 2 REQUIRED network audio graphics window system)
add_executable (empire 
./Source/main.cpp
./Source/ResourceManager/ResourceHolder.cpp
./Source/Sim/World.cpp
./Source/Sim/Person.cpp
./Source/Sim/Colony.cpp
./Source/Application.cpp
./Source/Util/Common.cpp
./Source/Util/Random.cpp)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries (empire ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} Threads::Threads)
