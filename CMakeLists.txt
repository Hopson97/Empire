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
./Source/Util/Random.cpp
./Source/Util/FPSCounter.cpp
./Source/Native/Win32.cpp
./Source/Native/Unix.cpp)
file(COPY Res colours.txt config.txt DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Screenshots)
find_package(Threads)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED network audio graphics window system)
target_link_libraries(empire Threads::Threads ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} )
