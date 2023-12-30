find_package(Boost REQUIRED)

add_executable(pi main.cpp)
target_link_libraries(pi PRIVATE Boost::boost)