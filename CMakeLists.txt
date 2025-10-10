cmake_minimum_required(VERSION 4.0)
project(c2JSON C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(json)
include_directories(lists)

add_executable(c2JSON
        json/c-json.c
        json/c-json.h
        json/json-array.c
        json/json-array.h
        json/json-dt-2.c
        json/json-dt-2.h
        json/json-ob-2.c
        json/json-ob-2.h
        lists/cllist.c
        lists/cllist.h
        lists/dllist.c
        lists/dllist.h
        lists/lhash-2.c
        lists/lhash.h
        lists/llist.c
        lists/llist.h
        test1.c
        json/main.c)
