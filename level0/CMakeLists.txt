project(level0)

add_subdirectory(c1)

add_subdirectory(c2)

add_subdirectory(c3)

add_executable(bubbleSort bubbleSort/main.c
)

add_executable(c0 c0/main.c)