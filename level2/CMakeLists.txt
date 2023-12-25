project(level2)

add_executable(GA GA/GA_main.c
        GA/GA_function.c
        GA/GA.h
)
add_executable(NeuralNetworks
        NeuralNetworks/NeuralNetworks.c
        NeuralNetworks/train_data.h
        NeuralNetworks/basical_parameter.h
        NeuralNetworks/functions.h
        NeuralNetworks/functions.c)
MATH(EXPR stack_size "2*1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
