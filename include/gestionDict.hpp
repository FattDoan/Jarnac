#pragma once

#include <vector>
#include <set>
#include <string>

/**
 * Extraire tous les mots d'un fichier dictionnaireLangue 
 * @param langue    Langue du dictionnaire choisie
 *                  (Français, Anglais)
 * @return dict     Tous les mots de la langue choisie stockés dans un set
*/
std::set <std::string> extraitDict(std::string langue);
