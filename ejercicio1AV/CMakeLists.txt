cmake_minimum_required(VERSION 3.26)
project(ejercicio1AV C)

set(CMAKE_C_STANDARD 11)

add_executable(ejercicio1AV main.c ivector.c ivector.h
        Pedido.h)
