cmake_minimum_required(VERSION 3.12)
project(meta_programming)

set(CMAKE_CXX_COMPILER /usr/bin/clang)
set(CMAKE_CXX_STANDARD 17)

#add_executable(meta_programming 20180912/Singleton/SingletonMayer.cpp)
#add_executable(meta_programming 20180919/Compound/Compound.cpp)
#add_executable(meta_programming seminars/20180919/Flyweight/Flyweight.cpp)

add_executable(meta_programming bonuses/1_10102018/main.cpp bonuses/1_10102018/type_list.h bonuses/1_10102018/length.h bonuses/1_10102018/erase.h)