cmake_minimum_required (VERSION 3.1.3)
project (Empire)
add_executable (empire
./Source/Native/Win32.cpp
./Source/Native/Unix.cpp
./Source/ResourceManager/ResourceHolder.cpp
./Source/Sim/CustomColonyCreator.cpp
./Source/Sim/WorldUpdater.cpp
./Source/Sim/World.cpp
./Source/Sim/ColonyCreator.cpp
./Source/Sim/Map.cpp
./Source/Sim/Person.cpp
./Source/Sim/Colony.cpp
./Source/Sim/ColonyStatistics.cpp

./Source/Sim/RandomColonyCreator.cpp
./Source/main.cpp
./Source/Application.cpp






./Source/Util/Common.cpp
./Source/Util/Random.cpp
./Source/Util/FPSCounter.cpp)? 
set_property(TARGET empire PROPERTY CXX_STANDARD 14)
set_property(TARGET empire PROPERTY CXX_STANDARD_REQUIRED ON)
file(COPY Res colours.txt config.txt DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Screenshots)
find_package(Threads)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED network audio graphics window system)
option(SFML_STATIC_LIBRARIES "Set to TRUE to link libraries statically. Requires statically built SFML." FALSE)
target_link_libraries(empire Threads::Threads ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} )

