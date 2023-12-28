#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <sstream>
#include <map>
#include "IA.hpp"
#include "vueEnModeTexte.hpp"
#include "moteur.hpp"

void remplie(char caractere, int longueur, std::string texte, std::string position) {
    //Une implementation plus agreable que setfill et setw
    //3 positions possibles: gauche, centre, droite
    //La fonction n'affiche pas le texte si la position n'est pas specifie
    longueur -= texte.length();
    if (position == "gauche") {
        std::cout << texte;
        for (int i = 0; i < longueur; i++) {
            std::cout << caractere;
        }
    }
    else if (position == "droite") {
        for (int i = 0; i < longueur; i++) {
            std::cout << caractere;
        }
        std::cout << texte;
    }
    else if (position == "centre") {
        for (int i = 0; i < longueur/2; i++) {
            std::cout << caractere;
        }
        std::cout << texte;
        if (longueur % 2 != 0) {
            std::cout << caractere;
        }
        for (int i = 0; i < longueur/2; i++) {
            std::cout << caractere;
        }
    } else {
        for (int i = 0; i < longueur + texte.length(); i++) {
            std::cout << caractere;
        }
    }
    return;
}

void afficheEcartEntrePlateaux(std::string texte) {
    remplie(' ', 16, texte, "centre");
    return;
}

void afficheTitreJeuCosmetique() {
    //En C++, la syntaxe R"(...)" est utilisée pour créer un littéral de chaîne brute. 
    //Un littéral de chaîne brute permet d'inclure des caractères spéciaux,
    //tels que des caractères de retour à la ligne et des séquences d'échappement, 
    //sans qu'il soit nécessaire d'utiliser des caractères d'échappement supplémentaires tels que des barres obliques inverses.
    std::cout << R"(
                   ___                ___                             
                  |_  |              |_  |                            
                    | | ___ _   _      | | __ _ _ __ _ __   __ _  ___ 
                    | |/ _ \ | | |     | |/ _` | '__| '_ \ / _` |/ __|
                /\__/ /  __/ |_| | /\__/ / (_| | |  | | | | (_| | (__ 
                \____/ \___|\__,_| \____/ \__,_|_|  |_| |_|\__,_|\___| )" << "\n \n";
}
void afficheTitreJeu(int maxColonne) {
    std::cout << '|'; remplie('=', 2 * 4 * maxColonne + 16); std::cout << '|' << '\n';
    std::cout << '|'; remplie(' ', 2 * 4 * maxColonne + 16, "Jeu Jarnac", "centre"); std::cout << '|' << '\n';
    std::cout << '|'; remplie('=', 2 * 4 * maxColonne + 16); std::cout << '|' << '\n';
    return;
}
void afficheNomEtPoints(std::vector <std::string> equipeA, int pointA, std::vector <std::string> equipeB, int pointB, int maxColonne) {
    //Si le nom du joueur est trop long par rapport à la longueur de l'ensemble des colonnes -> bug
    //donc maxColonne doit etre minimum à 6 pour eviter des bugs
    std::string s_pointA = std::to_string(pointA) + " points";
    std::string s_pointB = std::to_string(pointB) + " points";

    int longueurDesColonnes = 4 * maxColonne - 1;
    
    //On suppose que le max point est 9999 -> On lui reserve 11 espaces -> Le reste est pour le nom
    //equipe[0] ... equipe[equpie.size()-1] -> nom de joueur de cette equipe
    std::cout << '|'; remplie(' ', longueurDesColonnes - 11, equipeA[0], "gauche"); remplie(' ', 11, s_pointA, "droite"); std::cout << '|';
    afficheEcartEntrePlateaux();
    std::cout << '|'; remplie(' ', longueurDesColonnes - 11, equipeB[0], "gauche"); remplie(' ', 11, s_pointB, "droite"); std::cout << '|' << '\n';

    for (int i = 1; i < std::max(equipeA.size(),equipeB.size()); i++) {
        std::string nomA = (i < equipeA.size()) ? equipeA[i] : "";
        std::string nomB = (i < equipeB.size()) ? equipeB[i] : "";
        std::cout << '|'; remplie(' ', longueurDesColonnes, nomA, "gauche"); std::cout << '|';
        afficheEcartEntrePlateaux();
        std::cout << '|'; remplie(' ', longueurDesColonnes, nomB, "gauche"); std::cout << '|' << '\n';
    }
   
    //--------------------------------------------------------------------------------------//
    
    std::cout << '|'; remplie('_', longueurDesColonnes); std::cout << '|';
    afficheEcartEntrePlateaux(); 
    std::cout << '|'; remplie('_', longueurDesColonnes); std::cout << '|' << '\n';
    return;
}
void afficheListeDePoints(int minLongueurMot, int maxColonne) {
    std::vector <int> listePoints;
    for (int i = 1; i <= maxColonne; i++) {
        listePoints.push_back(i*i);
    }

    std::cout << '|';
    for (int i = 0; i < listePoints.size(); i++) {
        std::string p = (i < minLongueurMot - 1) ? "": std::to_string(listePoints[i]);
        remplie(' ', 3, p, "droite"); std::cout << '|';
    }
    afficheEcartEntrePlateaux();
    std::cout << '|';
    for (int i = 0; i < listePoints.size(); i++) {
        std::string p = (i < minLongueurMot - 1) ? "": std::to_string(listePoints[i]);
        remplie(' ', 3, p, "droite"); std::cout << '|';
    }
    std::cout << '\n';
    
    //---------------------------------------------------------------------------------------//
    
    std::cout << '|'; 
    for (int i = 0; i < maxColonne; i++) {
        std::cout << "___|";
    }
    afficheEcartEntrePlateaux();
    std::cout << '|';
    for (int i = 0; i < maxColonne; i++) {
        std::cout << "___|";
    }
    std::cout << '\n';
    return;
}
void affichePlateaux(std::vector <std::string> plateau1, std::vector <std::string> plateau2, int minLongueurMot, int maxColonne) {
    std::vector <std::string> nomDeLigne = {"alpha","beta","gamma","delta","epsilon","dzeta","eta","theta","iota",
                                            "kappa","lambda","mu","nu","ksi","omicron","pi","rho","sigma","tau"};   
    
    for (int ligne = 0; ligne < plateau1.size(); ligne++) {
        std::cout << '|';
        for (int colonne = 0; colonne < maxColonne; colonne++) {
            std::string lettre = "";
            if (colonne < plateau1[ligne].length()) {
                lettre = lettreEnMajuscules(plateau1[ligne][colonne]);
            }
            remplie(' ', 3, lettre, "centre"); std::cout << '|';
        }
        afficheEcartEntrePlateaux(nomDeLigne[ligne]);
        std::cout << '|';
        for (int colonne = 0; colonne < maxColonne; colonne++) {
            std::string lettre = "";
            if (colonne < plateau2[ligne].length()) {
                lettre = lettreEnMajuscules(plateau2[ligne][colonne]);
            }
            remplie(' ', 3, lettre, "centre"); std::cout << '|';
        }
        std::cout << '\n';        
        //-----------------------------------------------------------------------------------------------//
        std::cout << '|'; 
        for (int i = 0; i < maxColonne; i++) {
            std::cout << "___|";
        }
        afficheEcartEntrePlateaux();
        std::cout << '|';
        for (int i = 0; i < maxColonne; i++) {
            std::cout << "___|";
        }
        std::cout << '\n';
    }
    return;
}
void afficheReserves(std::vector <char> reserve1, std::vector <char> reserve2, int maxColonne) {
    int longueurDesColonnes = 4 * maxColonne - 2;
    
    std::cout << '|'; remplie(' ',longueurDesColonnes + 1, "Reserve :", "gauche"); std::cout << '|'; 
    afficheEcartEntrePlateaux();
    std::cout << '|'; remplie(' ',longueurDesColonnes + 1, "Reserve :", "gauche"); std::cout << '|' << '\n';
    
    sort(reserve1.begin(),reserve1.end());
    sort(reserve2.begin(),reserve2.end());
    
    int i = 0, j = 0, maxNombreDesLettres = longueurDesColonnes / 2;
    while (i < reserve1.size() || j < reserve2.size()) {
        std::cout << '|';
        for (; i < maxNombreDesLettres; i++) {
            char lettre = ' ';
            if (i < reserve1.size()) {
                lettre = lettreEnMajuscules(reserve1[i]);
            }
            std::cout << lettre << ' ';
        }

        std::cout << " |";afficheEcartEntrePlateaux();std::cout << '|';
        
        for (; j < maxNombreDesLettres; j++) {
            char lettre = ' ';
            if (j < reserve2.size()) {
                lettre = lettreEnMajuscules(reserve2[j]);
            }
            std::cout << lettre << ' ';
        }
        
        std::cout << " |" << '\n';
        
        maxNombreDesLettres += longueurDesColonnes / 2;
    }
    
    std::cout << '|'; remplie('=', 2 * 4 * maxColonne + 16); std::cout << '|' << '\n';
 
    return;
}

void afficheEtatDuJeu(std::vector <std::vector <std::string>> plateau, std::vector <std::vector <char>> reserve, std::vector <std::vector <std::string>> nomEquipes, int maxLigne, int minLongueurMot, int maxColonne, std::string actionsDuTour) {    
    afficheTitreJeu(maxColonne);
    std::vector <std::string> plateauA, plateauB, plateauVide(maxLigne, "");
    std::vector <char> reserveA, reserveB, reserveVide = {};
    std::vector <std::string> nomEquipeA, nomEquipeB, nomEquipeVide = {"PLATEAU VIDE!"};
    for (int equipe = 0; equipe < plateau.size(); equipe += 2) {
            //----------
            nomEquipeA = nomEquipes[equipe];
            nomEquipeB = (equipe + 1 == plateau.size()) ? nomEquipeVide: nomEquipes[equipe+1]; 
            //----------
            plateauA = plateau[equipe]; 
            plateauB = (equipe + 1 == plateau.size()) ? plateauVide: plateau[equipe+1];    
            //---------
            reserveA = reserve[equipe];
            reserveB = (equipe + 1 == plateau.size()) ? reserveVide: reserve[equipe+1];
            //---------
            afficheNomEtPoints(nomEquipeA, comptePoints(plateauA), nomEquipeB, comptePoints(plateauB),maxColonne);
            afficheListeDePoints(minLongueurMot, maxColonne);
            affichePlateaux(plateauA, plateauB, minLongueurMot, maxColonne);
            afficheReserves(reserveA, reserveB, maxColonne);
    }
    std::cout << '\n' << actionsDuTour << '\n';
    return;
}

int numeroDeLigne(std::string input) {
    std::vector <std::string> nomDeLigne = {"alpha","beta","gamma","delta","epsilon","zeta","eta","theta","iota","kappa","lambda",
                                            "mu","nu","xi","omicron","pi","rho","sigma","tau","upsilon","phi","chi","psi","omega"};
    
    for (int i = 0; i < nomDeLigne.size(); i++) {
        if (nomDeLigne[i] == input)
            return i;
    }
    return -1;
}
int extraitInt(std::string input) {
    if (!('0' <= input[0]  && input[0] <= '9'))
        return -1;
    int x;
    std::stringstream ss(input);
    ss >> x;
    return x;
}
std::string entreeLigne() {
    std::string input;
    getline(std::cin,input);
    if (!input.empty() && input[input.length()-1] == '\n') {
        input.erase(input.length()-1);
    }
    return input;
}
char reponseDuJoueurPossibilites(std::map <char,int> possibilites) {
    std::cout << "Taper un nombre parmi les options possible au-dessous pour piloter la manche." << '\n';
    std::vector <std::pair <char, std::string>>  listeOptions = { {'J', "Crier Jarnac"},
                                                                  {'M', "Composer un Mot (former un nouveau ou modifier l'ancien)"},
                                                                  {'T', "Tirer une lettre"},
                                                                  {'E', "Échanger trois lettre"},
                                                                  {'P', "Passer son tour"},
                                                                  {'V', "Voir les coups possibles (aide de l'IA)"},
                                                                  {'L', "Laisser l'IA jouer à ma place"},
                                                                  {'A', "Abandonner la partie"}
                                                                };
    for (auto option: listeOptions) {
        if (possibilites[option.first] > 0) {
            std::cout << option.first << "    : " << option.second;
            if ((option.first == 'J' || option.first == 'T' || option.first == 'E') && possibilites[option.first] > 0) {
                std::cout << " (il vous reste " << possibilites[option.first] << " fois)";
            }
            std::cout << '\n';
        }
    }

    std::cout << "Votre choix: ";
    char option;
    while (true) {
        std::string input = entreeLigne();
        option = lettreEnMajuscules(input[0]);
        if (possibilites.find(option) != possibilites.end()) break;
        afficheOptionNonValide();
    }   
    return option;
}

std::string reponseDuJoueurFormeMot(std::string precedentMot, std::vector <char> reserveDuJoueur, std::set <std::string> dict, int minLongueurMot, int maxColonne) {
    std::cout << "*** Vous pouvez taper la lettre P ou p pour passer le tour ***\n";
    std::cout << "Votre nouveau mot: ";
    std::string nouveauMot;
    while (true) {
        nouveauMot = motEnMinuscules(entreeLigne());
        if (nouveauMot == "p") break;
        if (motValide(precedentMot, nouveauMot, reserveDuJoueur, dict, minLongueurMot, maxColonne))
            break;
        std::cout << "Le mot " << "'" << nouveauMot << "'" << " n'est pas valide. Veuillez réessayer : ";
    } 
    return nouveauMot;
}

int reponseDuJoueurLigne(std::vector <std::string> plateauDeEquipe) {
    std::cout << "La ligne que vous souhaitez modifier: ";
    int ligne;
    std::string input;
    while (true) {
        input = entreeLigne();
        ligne = numeroDeLigne(input);
        if (ligne == -1) ligne = extraitInt(input) - 1;
        if (0 <= ligne && ligne <= premiereLigneVide(plateauDeEquipe)) break;
        afficheOptionNonValide();
    }
    return ligne;
}
std::vector <char> reponseDuJoueurEchanger(std::vector <char> reserve, int nombreLettre) {
    std::cout << nombreLettre << " mots que vous souhaitez échanger (séparés par un coma ou un espace) :";
    while (true) {
        std::string input = motEnMinuscules(entreeLigne());
        std::vector <char> listeLettres;
        for (int i = 0; i < input.length(); i += 2) {
            if (!('a' <= input[i] && input[i] <= 'z')) break;
            listeLettres.push_back(input[i]);
        }
        std::vector <int> tabFreqListe = calculeTableauFrequence("",listeLettres);
        std::vector <int> tabFreqReserve = calculeTableauFrequence("",reserve);
        if (listeLettres.size() == nombreLettre && compareTableauFrequence(tabFreqReserve, tabFreqListe, false))
            return listeLettres;
        afficheOptionNonValide();
    }
}
int reponseDuJoueurNomAnnonceJarnac(std::vector <std::vector <std::string>> nomEquipes, int equipe) {
    std::cout << "Le nom du joueur (ou le numéro de l'équipe) dont vous souhaitez modifier le plateau :" << '\n';
    std::string nom;
    while (true) {
        nom = entreeLigne();
        int numeroDeEquipe = extraitInt(nom);
        for (int i = 0; i < nomEquipes.size(); i++) {
            for (int j = 0; j < nomEquipes[i].size(); j++) {
                if (motEnMinuscules(nom) == motEnMinuscules(nomEquipes[i][j])) {
                    return i;
                }
            }
        }
        if (1 <= numeroDeEquipe && numeroDeEquipe <= nomEquipes.size() && numeroDeEquipe != (equipe+1)) {
            return numeroDeEquipe - 1;
        }
        afficheOptionNonValide();
    }
}
std::string reponseDuJoueurDifficulteIA() {
    std::cout << "(F) Facile || (M) Moyen || (D) Difficile || (I) Impossible \n"; 
    std::cout << "Veuillez indiquer la difficulté pour cet IA (F, M, D ou I) : ";
    std::vector <std::string> difficulte = {"Facile","Moyen","Difficile","Impossible"};
    while (true) {
        std::string input = entreeLigne();
        char premiereLettre = lettreEnMajuscules(input[0]);
        for (std::string tmp: difficulte) {
            if (premiereLettre == tmp[0]) {
                return tmp;
            }
        }
        afficheOptionNonValide();
    }
    return "Facile";
}
std::vector <std::vector <std::string>> reponsesDesJoueursDemandeDePrenom() {    
    int nombreEquipe, nombreJoueur, idIA = 1;
    std::cout << "Veuillez taper le nombre d'équipes (2, 3 ou 4): ";
    while (true) {
        nombreEquipe = extraitInt(entreeLigne());
        if (2 <= nombreEquipe && nombreEquipe <= 4) break;
        afficheOptionNonValide(); 
    }

    std::vector <std::vector <std::string>> nomEquipe(nombreEquipe);
    std::cout << "|================================================================================================|\n";
    std::cout << "|Si vous voulez que l'IA joue pour une équipe, taper 0 pour le nombre de joueurs de cette équipe.|\n";
    std::cout << "|================================================================================================|\n";
    for (int i = 0; i < nombreEquipe; i++) {
        std::cout << "Le nombre de joueurs dans l'équipe " << i+1 <<": "; 
        while (true) {
            nombreJoueur = extraitInt(entreeLigne());
            if (0 <= nombreJoueur) break;
            afficheOptionNonValide();
        }
        if (nombreJoueur == 0) {
            std::string difficulte = reponseDuJoueurDifficulteIA();
            nomEquipe[i].push_back("[IA " + std::to_string((idIA++)) + "] - " + difficulte); 
        }
        else for (int j = 0; j < nombreJoueur; j++) {
            std::cout << "Joueur " << j+1 << " de l'equipe " << i+1 <<", votre prénom est : ";
            nomEquipe[i].push_back(entreeLigne());
        }
    }
    return nomEquipe;
}

std::string reponseDuJoueurDemandeDictionnaire(std::vector <std::string> listeLangue) {
    std::cout << "Choisir la langue du dictionnaire du jeu." << '\n';
        for (int i = 0; i < listeLangue.size(); i++) {
        std::cout << i+1 << "   : " << listeLangue[i] << '\n'; 
    }
    bool arret = false;
    std::string input;
    while (!arret) {
        input = entreeLigne();
        int numeroDuDictionnaire = extraitInt(input);
        
        for (int i = 0; i < listeLangue.size(); i++)
            if (input == listeLangue[i]) {
                arret = true;
            }

        if (1 <= numeroDuDictionnaire && numeroDuDictionnaire <= listeLangue.size()) {
            return listeLangue[numeroDuDictionnaire-1];
        }
        afficheOptionNonValide();
    }
    return input;
}

int reponseDuJoueurDemandeNombreLignesPlateau() {
    std::cout << "Nombre de lignes du plateau (minimum 1) : ";
    int maxLigne;
    while (true) {
        maxLigne = extraitInt(entreeLigne());
        if (maxLigne >= 1) break;
        afficheOptionNonValide();
    }
    return maxLigne;
}

int reponseDuJoueurDemandeColonnesPlateau() {
    std::cout << "Longueur maximale des mots (minimum 6) : ";
    int maxColonne;
    while (true) {
        maxColonne = extraitInt(entreeLigne());
        if (maxColonne >= 6) break;
        afficheOptionNonValide();
    }
    return maxColonne;
}

int reponseDuJoueurDemandeLongueurMinimaleMot() {
    std::cout << "Longueur minimale des mots (minimum 2) : ";
    int minLongueurMot;
    while (true) {
        minLongueurMot = extraitInt(entreeLigne());
        if (minLongueurMot >= 2) break;
        afficheOptionNonValide();
    }
    return minLongueurMot;
}

bool reponseDuJoueurDemandeAideIAPlateau() {
    std::cout << "Pour activer l'aide de l'IA, taper 1, sinon taper 0: ";
    bool aideDeIA = false;
    while (true) {
        int option = extraitInt(entreeLigne());
        if (option == 0 || option == 1) {
            aideDeIA = option;
            break;
        }
        afficheOptionNonValide(); 
    }
    return aideDeIA;
}

bool reponseDuJoueurDemandeLaisserIAJouer() {
    std::cout << "Pour permettre à l'IA de jouer à votre place, taper 1, sinon taper 0: ";
    bool laisseIAJouer = false;
    while (true) {
        int option = extraitInt(entreeLigne());
        if (option == 0 || option == 1) {
            laisseIAJouer = option;
            break;
        }
        afficheOptionNonValide(); 
    }
    return laisseIAJouer;
}

int reponseDuJoueurDemandeNombreJarnacChaqueTour() {
    std::cout << "Le nombre des coups de Jarnac à chaque tour: ";
    int nombreJaracChaqueTour;
    while (true) {
        nombreJaracChaqueTour = extraitInt(entreeLigne());
        if (0 <= nombreJaracChaqueTour) break;
        afficheOptionNonValide();
    }
    return nombreJaracChaqueTour;
}
std::string afficheNomUneEquipe(std::vector <std::string> listeNom) {
    std::string s = "";
    for (int i = 0; i < listeNom.size(); i++) {
        s += listeNom[i];
        if (i == listeNom.size() - 2) s += " et ";
        else if (i != listeNom.size() - 1) s += " , ";
    }
    return s;
}

void afficheConfigurationActuelle(std::string langue, int maxLigne, int minLongueurMot, int maxLongueurMot, int nombreJarnacChaqueTour, std::vector <std::vector <std::string>> nomEquipes, bool aideDeIA, bool laisseIAJouer) {
    videEcran();
    afficheTitreJeuCosmetique();
    std::cout << "(1) Langue du dictionnaire : " << langue << '\n';
    std::cout << "(2) Nombre de lignes du plateau : " << maxLigne << '\n';
    std::cout << "(3) Longueur minimale des mots : " << minLongueurMot << '\n';
    std::cout << "(4) Longueur maximale des mots: " << maxLongueurMot << '\n';
    std::cout << "(5) Nombre des coups de Jarnac possibles à chaque tour: " << nombreJarnacChaqueTour << '\n';
    std::string aideIA = (aideDeIA) ? "Activée" : "Désactivé";
    std::cout << "(6) Aide de l'IA: " << aideIA << '\n';
    std::string IAJouer = (laisseIAJouer) ? "Activée" : "Désactivé";
    std::cout << "(7) Laisser l'IA jouer à votre place: " << IAJouer << '\n';
    std::cout << "(8) Nombre d'équipes : " << nomEquipes.size() << '\n';
    for (int i = 0; i < nomEquipes.size(); i++) {
        std::cout << "    Équipe " << i+1 << " : ";
        std::cout << afficheNomUneEquipe(nomEquipes[i]); 
        std::cout << '\n';
    }
    
    std::cout << "|============================================================================================================================|\n";
    std::cout << "|Pour lire le tutoriel, taper !aide                                                                                          |\n";
    std::cout << "|Pour modifier la configuration, taper le numéro (1, 2, 3, ...) correspondant à la configuration que vous souhaitez changer. |\n";
    std::cout << "|Si tout est bon, taper 0 pour commencer le jeu.                                                                             |\n";
    std::cout << "|============================================================================================================================|\n";
    std::cout << "Votre option : ";
    return;
}
void afficheAideDeIA(std::vector <std::string> listeMots) {
    std::cout << '|'; remplie('=',32,"Suggestions de l'IA","centre"); std::cout << "|\n";
    for (int i = 0; i < listeMots.size(); i++) {
        if (listeMots[i] == "") continue;
        std::cout << '|'; remplie(' ',32,motEnMajuscules(listeMots[i]),"gauche"); std::cout << "|\n";
    }
    std::cout << '|'; remplie('=',32); std::cout << "|\n";
    return;
}
void afficheJoueurGagnant(std::vector<std::vector <std::string>> plateau, std::vector <std::vector <std::string>> nomEquipe) {
    std::vector <int> points;
    for (int i = 0; i < plateau.size(); i++)
        points.push_back(comptePoints(plateau[i]));
    int equipeAyantMaxPoints = 0;
    for (int i = 1; i < points.size(); i++)
        if (points[i] > points[equipeAyantMaxPoints]) {
            equipeAyantMaxPoints = i;
        }
    std::cout << "L'équipe " << equipeAyantMaxPoints + 1 << " ( ";
    std::cout << afficheNomUneEquipe(nomEquipe[equipeAyantMaxPoints]) << " ) a gagné la partie avec le score " << points[equipeAyantMaxPoints] << "! \n";
    return;
}
void afficheOptionNonValide() {
    std::cout << "Votre choix n'est pas valide. Veuillez réessayer : ";
    return;
}

void afficheFichierTexte(std::string nomFichier) {
    std::fstream fichier(nomFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur d'ouverture de fichier !" << '\n';
        std::cin.get();
        return;
    }
    videEcran();
    std::string ligne;
    int ligneAffichee = 0;
    while (std::getline(fichier, ligne)) {
        std::cout << ligne << '\n';
        ligneAffichee++;
        if (ligneAffichee % 40 == 0) {
            std::cout << "\n(!) Appuyer sur Entrée pour continuer... \n";
            std::cin.get();
            videEcran();
        }
    }
    std::cout <<"\n(!) Appuyer sur Entrée pour revenir au menu principal.\n";
    std::cin.get();
    fichier.close();
    return;
}
void videEcran() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        // Suppose POSIX
        std::system("clear");
    #endif
}
