cmake_minimum_required (VERSION 3.0.2)
project (Empire)

add_executable (empire
./Source/ResourceManager/*
./Source/Sim/*
./Source/*
./Source/Util/*
)

target_link_libraries (empire -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system)
