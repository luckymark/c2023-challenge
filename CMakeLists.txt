cmake_minimum_required(VERSION 3.2)
project(c2023_challenge)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
#我的环境变量咋访问不了了？
set(Boost_INCLUDE_DIR C:/Users/cz241/Documents/GitHub/vcpkg/installed/x64-windows-static/include)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
find_package(Boost COMPONENTS system REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif ()
add_executable(level2_PI level2/PI/main.cpp
        level2/PI/Calculator.cpp
        level2/PI/Calculator.h)
target_link_libraries(level2_PI ${Boost_LIBRARIES})

add_executable(GobangCat
        ClassDesign/main.cpp
        ClassDesign/Player/RandomRobot.cpp
        ClassDesign/DataHelper/DataType.h
        ClassDesign/BoardDrawer.cpp
        ClassDesign/BoardDrawer.h
        ClassDesign/Player/IPlayer.h
        ClassDesign/Player/HumanPlayer.cpp
        ClassDesign/Player/ChessTreeRobot.cpp
        ClassDesign/DataHelper/DataType.cpp
        ClassDesign/DataHelper/ChessTree.cpp
        ClassDesign/DataHelper/ChessTree.h
        ClassDesign/DataHelper/ModelChecker.cpp
        ClassDesign/DataHelper/ModelChecker.h)
find_package(raylib)
target_link_libraries(GobangCat raylib)

add_executable(NeuralNetworks level2/NeuralNetworks/main.cpp
        level2/NeuralNetworks/Network.cpp
        level2/NeuralNetworks/Network.h)
target_link_libraries(NeuralNetworks raylib)
