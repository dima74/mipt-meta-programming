cmake_minimum_required(VERSION 3.12)
project(meta_programming)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 17)

#add_executable(seminars_20180912_singleton seminars/20180912/Singleton/SingletonMayer.cpp)
#add_executable(seminars_20180912_compound seminars/20180919/Compound/Compound.cpp)
#add_executable(seminars_20180912_flyweight seminars/20180919/Flyweight/Flyweight.cpp)

#add_executable(bonus1 bonuses/1_10102018/main.cpp bonuses/1_10102018/type_list.h bonuses/1_10102018/length.h bonuses/1_10102018/erase.h bonuses/1_10102018/append_front.h bonuses/base.h)
add_executable(task1 tasks/1_26092018/main.cpp tasks/1_26092018/proxy.h tasks/1_26092018/mediator.h tasks/1_26092018/observer.h tasks/1_26092018/base.h)