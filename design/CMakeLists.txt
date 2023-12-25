cmake_minimum_required(VERSION 3.10)

project(wuziqi)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(wuziqi
        wuziqi/fontdata.h
        wuziqi/fontdata.c
        wuziqi/main.c
        wuziqi/game.h
        wuziqi/stackAndSeqList.h
        wuziqi/stackAndSeqList.c
        wuziqi/game.c
        wuziqi/class.h
        wuziqi/interface.c
        wuziqi/interaction.c
        wuziqi/evaluate.c
        wuziqi/evaluate.h
        wuziqi/interface.h
        wuziqi/interaction.h
)

target_link_libraries(wuziqi PRIVATE raylib)

