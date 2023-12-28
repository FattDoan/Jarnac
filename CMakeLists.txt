cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Nom du projet
project(Jeu-Jarnac)

#Activer la génération de compile_commands.json (permettre à clang de trouver le fichiers header)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/moteur-test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/moteur.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gestionDict
   )
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/moteur.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gestionDict.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vueEnModeTexte.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/controleurModeTexte.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IA.cpp
   )

#Spécifier le dossier de header
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#Ajouter l'exécutable en incluant tous les fichiers sources
add_executable(JeuJarnac ${SOURCES})
if (ENABLE_TESTS)
    #Si le test est activé 
    add_executable(Test ${TEST_SOURCES})
endif()


