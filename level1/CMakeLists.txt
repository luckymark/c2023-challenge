project(level1)

add_executable(p01_running_letter p01_running_letter/main.cpp)

add_executable(p02_is_prime p02_is_prime/main.c
        p04_goldbach/func.c)

add_executable(p03_all_primes p03_all_primes/main.c)

add_executable(p04_goldbach p04_goldbach/main.c
        p04_goldbach/func.c)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.cpp
        p05_encrypt_decrypt/Crypter.cpp
        p05_encrypt_decrypt/Crypter.h)

add_executable(p06_hanoi p06_hanoi/main.c)

add_executable(p07_maze p07_maze/main.cpp)

add_executable(p08_push_boxes p08_push_boxes/main.cpp)

add_executable(p09_linked_list p09_linked_list/main.cpp
        p09_linked_list/NodeList.h
)

add_executable(p10_warehouse p10_warehouse/main.cpp
        p10_warehouse/StoreHelper.cpp
        p10_warehouse/StoreHelper.h)