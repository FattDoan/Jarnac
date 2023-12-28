#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <random>
#include <algorithm>

#include "moteur.hpp"
#include "IA.hpp"

std::string extraitDifficulte(std::string nomIA) {
    // Ex: [IA 1] - Difficile , [IA 2] - Facile
    std::vector <std::string> difficulte = {"Facile","Moyen","Difficile","Impossible"};
    for (int i = 0; i < difficulte.size(); i++) {
        if (nomIA.substr(nomIA.length() - difficulte[i].length(),nomIA.length()-1) == difficulte[i])
            return difficulte[i];
    }
    return "";
}

std::vector <int> initialiseProbabilitieDict(std::string difficulte, int maxColonne) {
    std::vector <int> probabilite(maxColonne+1,0);
    probabilite[2] = 100; 
    if (difficulte == "Facile") {   
        probabilite[3] = 90;
        for (int i = 4; i <= maxColonne; i++) {
            probabilite[i] = std::max(probabilite[i-1] - 25,0);
        }
    }
    else if (difficulte == "Moyen") {
        probabilite[3] = 100;
        for (int i = 4; i <= maxColonne; i++) {
            probabilite[i] = std::max(probabilite[i-1] - 20,0);
        }

    }
    else if (difficulte == "Difficile") {
        probabilite[3] = probabilite[4] = 100;
        for (int i = 5; i <= maxColonne; i++) {
            probabilite[i] = std::max(probabilite[i-1] - 15,0);
        }
    }
    else if (difficulte == "Impossible") {
        for (int i = 3; i <= maxColonne; i++) {
            probabilite[i] = 100;
        }
    }
    return probabilite;
}

std::set <std::string> initialiseDictPourIA(std::string difficulte, const std::set <std::string>& dictPourJoueurs, int maxColonne) {
    std::vector <int> probabilite = initialiseProbabilitieDict(difficulte, maxColonne);    
    std::set <std::string> dictPourIA;
    //Moteur de nombres aleatoires
    std::random_device aleatoire;
    std::mt19937 moteurAleatoire(aleatoire());
    std::uniform_int_distribution <int> distribution_0_99(0, 99);
    //============================================================

    for (std::string mot : dictPourJoueurs) {
        int val = distribution_0_99(moteurAleatoire);
        if (val < probabilite[mot.length()]) {
            dictPourIA.insert(mot);
        } 
    }

    return dictPourIA;
}
void misAJourTabIAPourUneLigne(std::string nouveauMot, const std::set <std::string>& dictPourIA, std::set <std::string>& ligneTabIA) {
    //Si le nouveau mot est vide, cela signifie il y avait un mot sur cette ligne mais il a été chipé par l'opposition qui annonce Jarnac
    if (nouveauMot == "") {
        //Lorsque le tableau de fréquence de tous les mots du dictionnaire toujours >= le tableau de fréquence de le mot vide,
        //l'ensemble des mots serait tout le dictionnaire 
        //Cependant, on n'affecte pas ligneTabIA au dictionnaire mais on le vide
        //Ainsi, si on doit à nouveau le mettre à jour, on passe directement par le dictionnaire
        ligneTabIA.clear();
    } else {
        std::set <std::string>  ensembleActuel, nouveauEnsemble;
        if (!ligneTabIA.empty()) {
            ensembleActuel = ligneTabIA;
        }
        else {
            //Si un nouveau mot formé sur cette ligne vide ou le cas précédent que nous avons vu
            //On passe directement par le dictionnaire
            ensembleActuel = dictPourIA;
        }
        for (std::string motDansEnsemble : ensembleActuel) {
                std::vector <int> tabFreqNouveauMot = calculeTableauFrequence(nouveauMot);
                std::vector <int> tabFreqMotDansEnsemble = calculeTableauFrequence(motDansEnsemble);
                //Si le tableau de fréquence du mot dans ensemble >= tableau de fréquence du nouveau mot
                //Autrement dit, pour tous les lettres 'a' -> 'z':
                //le nombre d'occurrences de chaque lettre dans le mot dans ensemble >= le nombre d'occurrences de cette lettre dans le nouveau mot   
                //Par exemple tabFreq de "aab" >= tabFreq de "a" 
                if (compareTableauFrequence(tabFreqMotDansEnsemble, tabFreqNouveauMot, false)) {
                    //On l'ajoute dans le nouveau ensemble
                    nouveauEnsemble.insert(motDansEnsemble);
                }
        }
        ligneTabIA = nouveauEnsemble;
    }
    return;
}
void misAJourTabIAPourUneLignePourTousIA(int joueur, int ligne, std::string nouveauMot, const std::vector <std::set <std::string>>& dictPourIA,
                                                                                              std::vector <std::vector <std::vector <std::set <std::string>>>>& tabIA) {
    for (int i = 0; i < tabIA.size(); i++) {
        misAJourTabIAPourUneLigne(nouveauMot, dictPourIA[i], tabIA[i][joueur][ligne]);
    }
    return;
}
void misAJourTabIAPourUnPlateau(const std::vector <std::string>& plateau, const std::set <std::string>& dictPourIA, std::vector <std::set <std::string>>& plateauTabIA) {
    for (int ligne = 0; ligne < plateau.size(); ligne++) {
        misAJourTabIAPourUneLigne(plateau[ligne], dictPourIA, plateauTabIA[ligne]);
    }
    return;
}

std::string meuilleurMotAFormer(std::string precedentMot, std::vector <char> reserve, std::set <std::string> surEnsemble, const std::set <std::string>& dictPourIA, int minLongueurMot, int maxColonne) {
    std::string meuilleurMot = "";
    if (surEnsemble.empty()) surEnsemble = dictPourIA;
    //Tous les mots dans surEnsemble sont toujours valides car ils appartiennent au dictionnaire
    for (std::string mot : surEnsemble) {
        if (possibleFormeMot(precedentMot, reserve, mot)) {
            if (minLongueurMot <= mot.length() && mot.length() <= maxColonne && meuilleurMot.length() < mot.length() &&  precedentMot.length() < mot.length())
                meuilleurMot = mot;
        }
    }
    //Si meuilleurMot == "" -> il est impossible de former un mot valide
    return meuilleurMot;
}

std::vector <std::string> listeMotsPossiblesAIPourUnePlateau(const std::vector <std::string>& plateauUnJoueur, std::vector <char> reserve, const std::vector <std::set <std::string>>& plateauTabIA, const std::set <std::string>& dictPourIA, int minLongueurMot, int maxColonne) {
    std::vector <std::string> listeMots;
    bool arretChercher = false;
    for (int ligne = 0; ligne < plateauUnJoueur.size(); ligne++) {
        if (arretChercher && plateauUnJoueur[ligne] == "") {
            listeMots.push_back("");
            continue;
        }
        std::string mot = meuilleurMotAFormer(plateauUnJoueur[ligne], reserve, plateauTabIA[ligne], dictPourIA, minLongueurMot, maxColonne);
        listeMots.push_back(mot);
        if (plateauUnJoueur[ligne] == "") arretChercher = true;
    }
    return listeMots;
}

std::vector <std::vector <std::string>> listePossibilitesMotAITousPlateaux(const std::vector <std::vector <std::string>>& plateau, std::vector <std::vector <char>> reserve,
                                                                           const std::vector <std::vector <std::set <std::string>>>& tabIA, const std::set <std::string> dictPourIA, int minLongueurMot, int maxColonne) {
    std::vector <std::vector <std::string>> listeMotsTousPlateaux;
    for (int joueur = 0; joueur < plateau.size(); joueur++) {
        listeMotsTousPlateaux.push_back(listeMotsPossiblesAIPourUnePlateau(plateau[joueur], reserve[joueur], tabIA[joueur], dictPourIA, minLongueurMot, maxColonne));
    }
    return listeMotsTousPlateaux;
}
int indiceMeuilleurMot(const std::vector <std::string>& listeMots) {
    int indice = 0;
    for (int i = 0; i < listeMots.size(); i++) {
        if (listeMots[i].length() > listeMots[indice].length()) {
            indice = i;
        }
    }
    return indice;
}
bool possibleJarnac(const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, int tourIA) {
    for (int joueur = 0; joueur < listeMeuilleursMotsIATousPlateaux.size(); joueur++) {
        if (tourIA == joueur) continue;
        int indice = indiceMeuilleurMot(listeMeuilleursMotsIATousPlateaux[joueur]);
        if (listeMeuilleursMotsIATousPlateaux[joueur][indice] != "") return true;
    }
    return false;
}
std::pair <int,int> meuilleurMotPourJarnacIA(const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, int tourIA, const std::vector <std::vector <std::string>>& plateau) {
    //pair.first = numero plateau du joueur; pair.second = indice
    std::pair <int,int> meuilleur = std::make_pair(0,0);
    for (int joueur = 0; joueur < plateau.size(); joueur++) {
        if (tourIA == joueur) continue;
        int indice = indiceMeuilleurMot(listeMeuilleursMotsIATousPlateaux[joueur]);
        if (listeMeuilleursMotsIATousPlateaux[joueur][indice].length() > plateau[meuilleur.first][meuilleur.second].length()) {
            meuilleur = std::make_pair(joueur, indice);
        }
    }
    return meuilleur;
}
bool possibleIAFormerMot(const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, int tourIA) {
    int indice = indiceMeuilleurMot(listeMeuilleursMotsIATousPlateaux[tourIA]);
    if (listeMeuilleursMotsIATousPlateaux[tourIA][indice] != "") return true;
    return false;
}
bool plusDeConsonnesQueVoyelles(std::vector <char> reserve, int nombre) {
    int nombreVoyelles = 0, nombreConsonnes = 0;
    for (int i = 0; i < reserve.size(); i++) {
        if (reserve[i] == 'a' || reserve[i] == 'e' || reserve[i] == 'i' || reserve[i] == 'o' || reserve[i] == 'u' || reserve[i] == 'y') {
            nombreVoyelles++;
        }
        else nombreConsonnes++;
    }
    return (nombreConsonnes - nombreVoyelles >= nombre);
}
std::vector <char> premieresConsonnesReserve(std::vector <char> reserve, int nombre) {
    int cmp = 0;
    std::vector <char> liste;
    for (int i = 0; i < reserve.size(); i++) {
        if (reserve[i] != 'a' && reserve[i] != 'e' && reserve[i] != 'i' && reserve[i] != 'o' && reserve[i] != 'u' && reserve[i] != 'y') {
            cmp++;
            liste.push_back(reserve[i]);
        }
        if (cmp == nombre) break;
    }
    return liste;
}
char decisionIA(std::map <char,int> possibilites, const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, std::vector <char> reserveIA, int tourIA) {  
    if (possibilites['J'] > 0 && possibleJarnac(listeMeuilleursMotsIATousPlateaux, tourIA)) {
        return 'J';
    }
    else if (possibilites['E'] > 0 && plusDeConsonnesQueVoyelles(reserveIA,3)) {
        return 'E';
    }
    else if (possibilites['T'] > 0) {
        return 'T';
    }
    else if (possibleIAFormerMot(listeMeuilleursMotsIATousPlateaux, tourIA)) {
        return 'M';
    }
    return 'P';
}
