cmake_minimum_required(VERSION 3.20)
project(seventh_gen C)

set(CMAKE_C_STANDARD 11)

include_directories(head)

add_executable(seventh_gen
        head/barcode.c
        head/barcode.h
        head/data_handling.c
        head/data_handling.h
        head/date_funcs.c
        head/date_funcs.h
        head/menu_opt.c
        head/menu_opt.h
        head/sort.c
        head/sort.h
        head/struct.h
        easy_fridge_69_with_struct.c)
