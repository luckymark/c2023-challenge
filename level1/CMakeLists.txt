project(level1)

add_executable(p01_running_letter p01_running_letter/main.c
)

add_executable(p02_is_prime p02_is_prime/main.c)

add_executable(p03_all_primes p03_all_primes/main.c)

add_executable(p04_goldbach p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.c)

add_executable(p06_hanoi p06_hanoi/main.c)

add_executable(p07_maze p07_maze/main.c
        p07_maze/head_maze.h
        p07_maze/creat.c
        p07_maze/initialize.c
        p07_maze/menu.c
        p07_maze/have_neighbor.c
        p07_maze/move.c
        p07_maze/print.c
        p07_maze/direction.c
)

add_executable(p08_push_boxes p08_push_boxes/main.c
        p08_push_boxes/map.c
        p08_push_boxes/head_push_box.h
        p08_push_boxes/print.c
        p08_push_boxes/menu.c
        p08_push_boxes/push.c
        p08_push_boxes/direction.c
        p08_push_boxes/whether_finish.c
        p08_push_boxes/note.c
        p08_push_boxes/read.c)

add_executable(p09_linked_list p09_linked_list/main.c)

add_executable(p10_warehouse p10_warehouse/main.c)

add_executable(temp temp/main.c
)