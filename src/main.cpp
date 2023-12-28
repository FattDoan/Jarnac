#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "vueEnModeTexte.hpp"
#include "controleurModeTexte.hpp"
#include "gestionDict.hpp"

int main() {
    
    //Configuration par defaut du jeu
    std::vector <std::string> listeLangue = {"Français", "Anglais"};
    std::string langue = "Français";
    int maxLigne = 8;
    int minLongueurMot = 3;
    int maxLongueurMot = 9;
    int nombreJarnacChaqueTour = 2;
    bool aideDeIA = false;
    bool laisseIAJouer = false;
    std::vector <std::vector <std::string>> nomEquipes = { {"Joueur A"}, {"Joueur B"} };
    std::set <std::string> dictPourJoueurs;
    //====================================
    while (true) {
        afficheConfigurationActuelle(langue, maxLigne, minLongueurMot, maxLongueurMot, nombreJarnacChaqueTour, nomEquipes, aideDeIA, laisseIAJouer);
        std::string input = entreeLigne();
        if (input == "!aide") {
            afficheFichierTexte("docs/tutoriel.txt"); 
            continue;
        }
        int option = extraitInt(input);
        switch (option) {
            case 0: //Lancer le jeu 
                {
                    dictPourJoueurs = extraitDict(langue);
                    bool flag = lanceJeu(dictPourJoueurs, maxLigne, minLongueurMot, maxLongueurMot, nombreJarnacChaqueTour, nomEquipes, aideDeIA, laisseIAJouer);
                    if (!flag) {
                        std::cout << "Vous avez abandonné la partie. \n";
                    } 
                    break;
                }
            case 1 : //Changer la langue du dictionnaire
                {
                    langue = reponseDuJoueurDemandeDictionnaire(listeLangue);
                    break;
                }
            case 2 : //Changer le nombre de lignes du plateau
                {
                    maxLigne = reponseDuJoueurDemandeNombreLignesPlateau();
                    break;
                }
            case 3 :
                {
                    minLongueurMot = reponseDuJoueurDemandeLongueurMinimaleMot();
                    break;
                }
            case 4 : //Changer la longueur maximale des mots
                {
                    maxLongueurMot = reponseDuJoueurDemandeColonnesPlateau();
                    break;
                }
            case 5 :
                {
                    nombreJarnacChaqueTour = reponseDuJoueurDemandeNombreJarnacChaqueTour();
                    break;
                }
            case 6 : //Afficher aide de l'IA
                {
                    aideDeIA = reponseDuJoueurDemandeAideIAPlateau(); 
                    break;
                }
            case 7 :
                {
                    laisseIAJouer = reponseDuJoueurDemandeLaisserIAJouer();
                    break;
                }
            case 8 : //Changer nombre d'equipes et ses noms
                {
                    nomEquipes = reponsesDesJoueursDemandeDePrenom();
                    break;
                }
            default:
                {
                    afficheOptionNonValide();
                    break;
                }
        }
    }
    return 0;
}
