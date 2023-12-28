#!/bin/bash

#Par défaut, le test est désactivé
TEST="DISABLED"
EXECUTABLE="JeuJarnac"

#Vérifie l'argument ./build.sh, s'il existe un argument et qu'il s'agit de "-t", le test est activé.
if [ -n "$1" ] && [ "$1" == "-t" ]
then
    TEST="ENABLED"
    EXECUTABLE="Test"
fi

#Cmake commandes de construction du projet, activation du test si le test est activé
if [ "$TEST" == "DISABLED" ]
then
    cmake -S . -B build -DENABLE_TESTS=OFF
else
    cmake -S . -B build -DENABLE_TESTS=ON
fi
cmake --build build

#Déplacer le fichier compile_commands.json dans le dossier parent du src pour clang
mv build/compile_commands.json ..

#Attendre d'appuyer sur la touche "Entrée" pour voir s'il y a des erreurs
read -p "Press enter to continue..."
echo ""

#Déplacer le fichier exécutable en dehors du dossier build
mv build/"$EXECUTABLE" .
if [ "$TEST" == "DISABLED" ]
then
    ./JeuJarnac
else
    ./Test
fi
