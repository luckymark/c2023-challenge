#set(CMAKE_PREFIX_PATH "C:\\Users\\14212\\.vcpkg-clion\\vcpkg (5)\\installed\\x64-windows\\")
project(gobang)
find_package(raylib CONFIG REQUIRED)
add_executable(gobang gobang.c
        gobang.h
        GUI.c
        init_.c
        check.c
        act.c
        judge_function.h
        search_function.h
        search_function.c)
target_link_libraries(gobang PRIVATE raylib)

