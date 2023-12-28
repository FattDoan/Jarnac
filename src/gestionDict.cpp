#include <string>
#include <set>
#include <fstream>

#include "gestionDict.hpp"
#include "moteur.hpp"

std::set <std::string> extraitDict(std::string langue) {
    std::string nomDict = "dictionnaire" + langue + ".txt";
    std::fstream fichierDict("dictionnaire/" + nomDict);
    std::set <std::string> dict;
    while (true) {
        std::string mot;
        fichierDict >> mot;
        mot = motEnMinuscules(mot);
        if (fichierDict.eof()) break;
        dict.insert(mot);
    }
    return dict;
}
