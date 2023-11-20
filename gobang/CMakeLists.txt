project(gobang)

find_package(raylib CONFIG REQUIRED)

add_executable(gobang main.c
        src/gui.c
        src/gobang.c
        src/alpha_beta_pruning.c
        src/mcts.c
        src/stack.c
)

target_link_libraries(gobang PRIVATE raylib)

