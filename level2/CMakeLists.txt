project(level2)

add_executable(GA GA/GA_main.c
        GA/GA_function.c
        GA/GA.h
        PI/main.c
)
add_executable(NeuralNetworks
        NeuralNetworks/NeuralNetworks.c
        NeuralNetworks/train_data.h
        NeuralNetworks/basical_parameter.h
        NeuralNetworks/functions.h
        NeuralNetworks/functions.c)
add_executable(PI
        PI/main.c)
MATH(EXPR stack_size "3*1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
