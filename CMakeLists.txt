cmake_minimum_required(VERSION 3.10)
project(ProjetTechniquesDeCompilation C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(ProjetTechniquesDeCompilation
        analyseur_syntaxique.c
        analyseur_lexical.c
)
