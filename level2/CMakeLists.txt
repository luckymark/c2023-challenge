project(level2)

find_package(raylib CONFIG REQUIRED)
add_executable(GA GA/GA_main.c
        GA/GA_function.c
        GA/GA.h)
target_link_libraries(GA PRIVATE raylib)
