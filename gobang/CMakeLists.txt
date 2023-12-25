project(gobang)

set(CMAKE_PREFIX_PATH "F:\\develop\\c\\.vcpkg-clion\\vcpkg\\packages\\raylib_x64-windows\\")
find_package(raylib CONFIG REQUIRED)

#set(raylib_DIR "F:\\develop\\c\\.vcpkg-clion\\vcpkg\\packages\\raylib_x64-windows\\share\\raylib")

add_executable(gobang
        main.c
        src/gui.c
        src/gobang.c
        src/alpha_beta_pruning.c
        src/stack.c
        src/alpha_beta_pruning.c
)

target_link_libraries(gobang PRIVATE raylib)

