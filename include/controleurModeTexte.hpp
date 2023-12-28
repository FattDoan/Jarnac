#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

bool lanceJeu(std::set <std::string> dictPourJoueurs, int maxLigne, int minLongueurMot, int maxColonne, int nombreJarnacChaqueTour, std::vector <std::vector <std::string>> nomEquipes, bool aideDeIA, bool laisseIAJouer);

