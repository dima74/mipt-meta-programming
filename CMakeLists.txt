cmake_minimum_required(VERSION 3.12)
project(meta_programming)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 17)

#add_executable(seminars_20180912_singleton seminars/20180912/Singleton/SingletonMayer.cpp)
#add_executable(seminars_20180912_compound seminars/20180919/Compound/Compound.cpp)
#add_executable(seminars_20180912_flyweight seminars/20180919/Flyweight/Flyweight.cpp)

add_executable(bonus1 bonuses/1_10102018/main.cpp)
add_executable(bonus2 bonuses/2_20181024/main.cpp)
add_executable(bonus3 bonuses/3_20181107/main.cpp)

add_executable(task1 tasks/1_20180926/main.cpp)