#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <cctype>
#include <random>
#include "IA.hpp"
#include "moteur.hpp"
#include "vueEnModeTexte.hpp"

char lettreEnMajuscules(char lettre) {
    return std::toupper(lettre);
}
std::string motEnMajuscules(std::string mot) {
    for (int i = 0; i < mot.length(); i++)
        mot[i] = std::toupper(mot[i]);
    return mot;
}
std::string motEnMinuscules(std::string mot) {
    for (int i = 0; i < mot.length(); i++)
        mot[i] = std::tolower(mot[i]);
    return mot;
}
bool estDansDict(std::string mot, std::set <std::string> dict) {
    return (dict.find(mot) != dict.end());
}

std::vector <int> nombreLettresDuJeu() {
    //Déclarer et allouer le tableau nombreLettre de taille 26
    std::vector <int> nombreLettre(26);

    //Initialiser
    nombreLettre[0] = 14; // A
    nombreLettre[1] = 4;  // B
    nombreLettre[2] = 7;  // C
    nombreLettre[3] = 5;  // D
    nombreLettre[4] = 19; // E
    nombreLettre[5] = 2;  // F
    nombreLettre[6] = 4;  // G
    nombreLettre[7] = 2;  // H
    nombreLettre[8] = 11; // I
    nombreLettre[9] = 1;  // J
    nombreLettre[10] = 1; // K
    nombreLettre[11] = 6; // L
    nombreLettre[12] = 5; // M
    nombreLettre[13] = 9; // N
    nombreLettre[14] = 8; // O
    nombreLettre[15] = 4; // P
    nombreLettre[16] = 1; // Q
    nombreLettre[17] = 10;// R
    nombreLettre[18] = 7; // S
    nombreLettre[19] = 9; // T
    nombreLettre[20] = 8; // U
    nombreLettre[21] = 2; // V
    nombreLettre[22] = 1; // W
    nombreLettre[23] = 1; // X
    nombreLettre[24] = 1; // Y
    nombreLettre[25] = 2; // Z

    return nombreLettre;
} 

std::queue <char> melangeSac(std::queue <char> sac) {
    //Un tableau temporaire pour mélanger car queue sac ne permet pas de le faire
    std::vector <char> tab; // Déclaration vector tab
    
    // Conversion queue sac en vector tab
    while (!sac.empty()){
    	tab.push_back(sac.front());
    	sac.pop();
    }
    
	// Mélanger
    std::shuffle(std::begin(tab), std::end(tab), std::random_device());
    
    // Remettre les valeurs de vecteur tab dans la queue sac
    for (int lettre : tab){
    	sac.push(lettre);
    }
    
    return sac;
}

std::queue <char> initialiseSac(std::vector <int> nombreLettre) {
    std::queue <char> sac;
    
    // Remplissage du sac en fonction des quantités spécifiées
    for (int i = 0; i < nombreLettre.size(); i++) { // nombreLettre.size() = 26 car 26 lettres dans l'alphabet
        char lettre = 'a' + i; // Commence avec la lettre 'A' (puis jusqu'à 'Z')

        for (int j = 0; j < nombreLettre[i]; j++) {
            sac.push(lettre); // Insère la lettre dans le sac le nombre de fois spécifié
        }
    }

    sac = melangeSac(sac);
    return sac;
}

std::vector<char> piocheDansSac(std::queue <char> sac, int nombreLettrePioche, std::vector <char> reserve) {    
    // Vérification si le joueur a des lettres à piocher
    if (nombreLettrePioche > 0 && !sac.empty()) {
        // Pioche des lettres du sac et ajout à la réserve du joueur
        for (int i = 0; i < nombreLettrePioche; i++) {
            char lettrePiochee = sac.front();
            reserve.push_back(lettrePiochee);
            sac.pop();
        }
    }
    return reserve;
}

std::vector <char> enleveLettresDansReserve(std::vector <char> lettresAEnlever, std::vector <char> reserve) {
    // Parcours des lettres à enlever
    for (char lettre : lettresAEnlever) {
        // Suppression de la lettre de la réserve du joueur si elle est présente
        auto it = std::find(reserve.begin(), reserve.end(), lettre);
        if (it != reserve.end()) {
            reserve.erase(it);
        }
    }
    return reserve;
}

std::queue <char> ajouteLettresAuSac(std::vector <char> lettresAAjouter, std::queue <char> sac) {
    // Ajout des lettres spécifiées au sac
    for (char lettre : lettresAAjouter) {
        sac.push(lettre);
    }

    // Mélange du sac
    sac = melangeSac(sac);

    return sac;
}

int comptePoints(std::vector <std::string> plateau) {
    int points = 0;
    for (int i = 0 ; i < plateau.size() ; i++){
        points += plateau[i].size() * plateau[i].size();
    }
    return points;
}

std::vector <std::string> modifiePlateau(std::vector <std::string> plateau, int ligne, std::string mot) {
    std::vector <std::string> plateauModifie = plateau;
    plateauModifie[ligne] = mot;
    return plateauModifie;
} 

int premiereLigneVide(std::vector <std::string> plateau) {
    int ligne = plateau.size();
    for (int i = 0 ; i < plateau.size() ; i++){
        if (plateau[i].length() == 0) {
            return i;
        }
    }
    return ligne;
}
bool compareTableauFrequence(std::vector <int> tab1, std::vector <int> tab2, bool strictement) {
    //renvoie true si tab1 >= tab2 (if strictement == true donc renvoie true si tab1 > tab2), false sinon
    for (int i = 0; i < 26; i++) {
        if (tab1[i] <= tab2[i]) { 
            if ((tab1[i] == tab2[i] && strictement) || (tab1[i] < tab2[i]))
                return false;
        }
    }
    return true;
}
std::vector <int> calculeTableauFrequence(std::string mot, std::vector <char> liste) {
    //Cette fonction accepte le mot (string) et la liste de caractere en tant qu'arguments
    //Par defaut, le mot et la reserve sont vides
    //Pour calculer seulement l'un d'entre deux :
    //Seulement le mot: calculeTableauFrequence(mot)
    //Seulement la liste: calculeTableauFrequence("", liste) 
    //En specifiant les deux arguments, la fonction les combine pour former le tableau de frequence
    std::vector <int> tabFrequence(26,0);
    for (int i = 0; i < mot.length(); i++)
        tabFrequence[mot[i] - 'a']++;
    for (int i = 0; i < liste.size(); i++) 
        tabFrequence[liste[i] - 'a']++;
    return tabFrequence;
}
bool estDansReserve(std::vector <char> liste, std::vector <char> reserve) {
    std::vector <int> tabFreqListe = calculeTableauFrequence("", liste);
    std::vector <int> tabFreqReserve = calculeTableauFrequence("", reserve);
    return compareTableauFrequence(tabFreqReserve, tabFreqListe, false);
}
bool possibleFormeMot(std::string motAModifier, std::vector <char> reserve, std::string motAFormer) {
    std::vector <int> tabFreqVrac = calculeTableauFrequence(motAModifier, reserve);
    std::vector<int> tabFreqMotAFormer = calculeTableauFrequence(motAFormer);  
    std::vector <int> tabFreqMotAModifier = calculeTableauFrequence(motAModifier);

    return (compareTableauFrequence(tabFreqVrac, tabFreqMotAFormer, false) && compareTableauFrequence(tabFreqMotAFormer, tabFreqMotAModifier, false));
}

std::vector <char> modifieReserveApresFormerMot(std::string motAModifier, std::vector <char> reserve, std::string motAFormer) {
    std::vector <char> reserveApres;
    std::vector <int> tabFreqReserve = calculeTableauFrequence("", reserve);
    std::vector <int> tabFreqMotAFormer = calculeTableauFrequence(motAFormer);
    std::vector <int> tabFreqMotAModifier = calculeTableauFrequence(motAModifier);

    for (int i = 0; i < 26; i++) {
        int nombreLettresUtilisees = tabFreqMotAFormer[i] - tabFreqMotAModifier[i];
        //On reduit le nombre des lettres utilisees de la reserve
        tabFreqReserve[i] -= nombreLettresUtilisees;
        
        char lettre = char(i+int('a'));
        for (int j = 0; j < tabFreqReserve[i]; j++)
            reserveApres.push_back(lettre);
    }
    return reserveApres;
}

bool motValide(std::string precedentMot, std::string nouveauMot, std::vector <char> reserveDuJoueur, std::set <std::string> dict, int minLongueurMot, int maxColonne) {
    return (   minLongueurMot <= nouveauMot.length() && nouveauMot.length() <= maxColonne
            && estDansDict(nouveauMot,dict)
            && possibleFormeMot(precedentMot, reserveDuJoueur, nouveauMot)  );
}


std::map <char,int> metAJourPossibilites(char option, std::map <char,int> possibilites) {
    switch (option) {
        case 'J': //Crier Jarnac
            {
                possibilites['J'] = std::max(possibilites['J'] - 1,0); 
                possibilites['T']++;
                break;
            }
        case 'M': //composer Mot
            {
                possibilites['T']++;
                break;
            }
        case 'T': //Tirer une lettre
            {
                if (possibilites['T'] == 1) {
                    possibilites['E'] = std::max(possibilites['E'] - 1, 0);
                }
                possibilites['T'] = std::max(possibilites['T'] - 1, 0);
                break;
            }
        case 'E': //Echanger
            {
                if (possibilites['T'] == 1) {
                    possibilites['T'] = std::max(possibilites['T'] - 1, 0);
                }
                possibilites['E'] = std::max(possibilites['E'] - 1, 0);
                break;
            }
        case 'V': //Aide de l'IA
            {
                possibilites['V'] = std::max(possibilites['V'] - 1, 0);
                break;
            }
        case 'L': //Laisser IA jouer à la place du joueur
            {
                possibilites['L'] = std::max(possibilites['L'] - 1, 0);
                break;
            }
        default:
            {
                break;
            }
    }
    return possibilites;
}

std::map <char, int> initialisePossibilites(int nombreTours, int nombreEquipes, int nombreJarnacChaqueTour, bool aideDeIA, bool laisseIAJouer) {
    std::map <char, int> possibilites;
    std::vector <char> liste = {'J','M','T','E','P','V','L','A'};
    for (char x: liste) possibilites[x] = 0;
    //Laisser IA jouer
    if (laisseIAJouer) possibilites['L'] = 1;
    //Voir les coups possibles (aide de l'IA)
    if (aideDeIA) possibilites['V'] = 1;

    //Les joueurs peuvent annoncer Jarnac sauf au premier tour
    if (nombreTours != 0) possibilites['J'] = nombreJarnacChaqueTour;
    
    //Dans tous les tours,les joueurs peuvent toujours composer des mots sur leur plateau, passer leur tour ou abandonner la partie
    possibilites['M'] = 1; possibilites['P'] = 1; possibilites['A'] = 1;
    
    //Apres le premier tour de chaque joueur, chacun peut piocher une lettre ou echanger trois lettres
    if (nombreTours >= nombreEquipes) {
        possibilites['T'] = 1;
        possibilites['E'] = 1;
    }
    return possibilites;
}

void metAJourPlateauComposerMot(int tourIDJoueurComposeMot, int ligneAModifier, std::string ancienMot, std::string nouveauMot,
                                std::vector <std::string>& plateauJoueurComposeMot, std::vector <char>& reserveJoueurComposeMot, std::map <char, int>& possibilites,
                                std::string& actionsDuTour) {
                                
    plateauJoueurComposeMot = modifiePlateau(plateauJoueurComposeMot, ligneAModifier, nouveauMot);

    reserveJoueurComposeMot = modifieReserveApresFormerMot(ancienMot, reserveJoueurComposeMot, nouveauMot);
    
    
    if (nouveauMot.length() > ancienMot.length()) {
        possibilites = metAJourPossibilites('M',possibilites);
    }

    actionsDuTour += "Composé le mot '" + motEnMajuscules(nouveauMot) + "' à la ligne " + std::to_string(ligneAModifier + 1) + "\n";
    return;
}

void metAJourPlateauxJarnac(int tourIDJoueurAnnonceJarnac, int tourIDJoueurEtreJarnac, int ligneAModifier, std::string ancienMot, std::string nouveauMot, 
                            std::vector <std::vector <std::string>>& plateau, std::vector <char>& reserveJoueurEtreJarnac, std::map <char,int>& possibilites,
                            std::string& actionsDuTour) {
    int ligneVidePlateauJoueurAnnonceJarnac = premiereLigneVide(plateau[tourIDJoueurAnnonceJarnac]);

    plateau[tourIDJoueurEtreJarnac] = modifiePlateau(plateau[tourIDJoueurEtreJarnac], ligneAModifier, "");
    plateau[tourIDJoueurAnnonceJarnac] = modifiePlateau(plateau[tourIDJoueurAnnonceJarnac], ligneVidePlateauJoueurAnnonceJarnac, nouveauMot);

    reserveJoueurEtreJarnac = modifieReserveApresFormerMot(ancienMot, reserveJoueurEtreJarnac, nouveauMot);
     
    possibilites = metAJourPossibilites('J', possibilites);

    actionsDuTour += "Chipé le mot '" + motEnMajuscules(nouveauMot) + "' de l'équipe " + std::to_string(tourIDJoueurEtreJarnac) + " à la ligne " + std::to_string(ligneAModifier + 1) + "\n"; 
    return;
}

void metAJourReserveApresPiocherLettres(std::vector <char>& reserveJoueurPioche, int nombreLettresAPiocher, std::queue <char>& sac,
                                        std::map <char,int>& possibilites, std::string& actionsDuTour) {
    reserveJoueurPioche = piocheDansSac(sac, nombreLettresAPiocher, reserveJoueurPioche);
    
    actionsDuTour += "Pioché ";
    for (int i = 0; i < nombreLettresAPiocher; i++) {
        if (sac.empty()) continue;
        actionsDuTour += lettreEnMajuscules(sac.front());
        if (i != nombreLettresAPiocher - 1) {
            actionsDuTour += ',';
        }
        sac.pop();
    }
    actionsDuTour += '\n';
    possibilites = metAJourPossibilites('T', possibilites);

    return;
}

void metAJourReserveApresEchangeLettres(std::vector <char>& reserveJoueurEchange, std::vector <char> listeLettres, std::queue <char>& sac,
                                        std::map <char, int>& possibilites, std::string& actionsDuTour) {
    int nombreLettresEchanges = listeLettres.size(); 
    reserveJoueurEchange = enleveLettresDansReserve(listeLettres, reserveJoueurEchange);
    
    actionsDuTour += "Échangé ";
    for (int i = 0; i < nombreLettresEchanges; i++) {
        actionsDuTour += lettreEnMajuscules(listeLettres[i]);
        if (i != nombreLettresEchanges - 1) {
            actionsDuTour += ',';
        }
    }
    actionsDuTour += " pour ";
    
    sac = ajouteLettresAuSac(listeLettres, sac);
    
    reserveJoueurEchange = piocheDansSac(sac, nombreLettresEchanges, reserveJoueurEchange);
    
    for (int i = 0; i < nombreLettresEchanges; i++) {
        if (sac.empty()) continue;
        actionsDuTour += lettreEnMajuscules(sac.front());
        if (i != nombreLettresEchanges - 1) {
            actionsDuTour += ',';
        }
        sac.pop();
    }
    actionsDuTour += '\n';
    possibilites = metAJourPossibilites('E', possibilites);

    return;
}


