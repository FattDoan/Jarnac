#pragma once

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>

/**
 * Transforme un caractère en majuscule
 * @param lettre  lettre en minuscule
 * @return lettre lettre en majuscule
 */
char lettreEnMajuscules(char lettre);

/**
 * Transforme une chaîne de caractères en minuscule
 * @param mot   ligne en majuscule  
 * @return mot  ligne en minuscule       
 */
std::string motEnMinuscules(std::string mot); 

/**
 * Transforme une chaîne de caractères en majuscule
 * @param mot   ligne en minuscule  
 * @return mot  ligne en majuscule       
 */
std::string motEnMajuscules(std::string mot); 
/**
 * Vérifie si le mot est dans le dictionnaire de type set
 * @param mot   mot à vérifier
 * @param dict  dictionnaire de type set
 * @return true si le mot est dedans ou false sinon
 */
bool estDansDict(std::string mot, std::set<std::string> dict);

/**
 * Initialise les lettres du jeu et leur occurrence
 * @return nombreLettre le tableau des lettres du jeu
 */
std::vector<int> nombreLettresDuJeu();

/**
 * Mélange les lettres du sac
 * Méthode : pour mélanger avec shuffle, on convertit queue en vector
 * @param sac   une queue de lettres
 * @return sac  sac mélangé
 */
std::queue<char> melangeSac(std::queue<char> sac);

/**
 * Crée le sac avec le nombreLettresDuJeu
 * @param nombreLettre  tableau de lettres du jeu
 * @return sac          prêt à jouer     
 */
std::queue<char> initialiseSac(std::vector<int> nombreLettre);

/**
 * Prends une lettre du sac
 * @param sac                   une queue de lettres
 * @param nombreLettrePioche    entier du nb de lettres que le joueur veut piocher
 * @param reserve               tableau de la réserve du joueur
 * @return reserve              réserve du joueur avec les lettres ajoutées
 */
std::vector<char> piocheDansSac(std::queue<char> sac, int nombreLettrePioche, std::vector<char> reserve);

/**
 * Retire des lettres dans la réserve du joueur
 * @param lettresAEnlever   tableau de lettres à retirer
 * @param reserve           tableau de lettres de la réserve du joueur
 * @return reserve          réserve du joueur avec les lettres retirées
 */
std::vector<char> enleveLettresDansReserve(std::vector<char> lettresAEnlever, std::vector<char> reserve);

/**
 * Remettre des lettres dans le sac
 * @param lettreAAjouter    tableau des lettres à mettre au sac
 * @param sac               une queue de lettre
 * @return sac              sac avec lettres rajoutées
 */
std::queue<char> ajouteLettresAuSac(std::vector<char> lettresAAjouter, std::queue<char> sac);

/**
 * Comptabilise les points du plateau d'un joueur
 * @param plateau   un tableau de chaîne de caractères du plateau d'un joueur
 * @return points   entier du total des points du joueur
 */
int comptePoints(std::vector <std::string> plateau);

/**
 * Ajout d'un mot à une ligne du plateau
 * @param plateau           tableau de mots du plateau d'un joueur
 * @param ligne             entier de la ligne à modifier
 * @param mot               mot à modifier à cette ligne
 * @return plateauModifie   le plateau avec le mot modifié à cette ligne
 */
std::vector <std::string> modifiePlateau(std::vector <std::string> plateau, int ligne, std::string mot);

/**
 * Détermine la première ligne vide du plateau du joueur
 * @param plateau   tableau de mots du plateau du joueur
 * @return ligne    entier de la première ligne vide du plateau
 */
int premiereLigneVide(std::vector <std::string> plateau);

/**
 * Compare 2 tableaux de fréquence (tableau de nombres entiers représentant le nombre d'occurrences de chaque lettre)
   On définit tab1 >= tab2 ssi pour tout i dans [0,25]: tab1['a' + i] >= tab2['a' + i]
 * @param tab1              première tableau de fréquence
 * @param tab2              deuxième tableau de fréquence
 * @param strictement       un booléen si == true : pour tout i dans [0,25]: tab1['a' + i] > tab2['a' + i]
 * @return un booléen       true si la condition est satisfaite, false sinon
 */
bool compareTableauFrequence(std::vector <int> tab1, std::vector <int> tab2, bool strictement);

/**
 * Calcule un tableau de fréquence en extrayant d'un mot et d'une reserve (un tableau de caractères)
 * Par défault, le mot et la reserve sont vides
   Pour calculer seulement l'un entre deux :
   Seulement le mot: calculeTableauFrequence(mot)
   Seulement la reserve: calculeTableauFrequence("", reserve) 
   En specifiant les deux arguments, la fonction les combine pour former le tableau de fréquence 
 * @param mot               un mot dont on veult calculer le tableau de fréquence 
 * @param liste             un tableau de caractères dont on veult calculer le tableau de fréquence  
 * @return vector<int>      le tableau de fréquence
 */
std::vector <int> calculeTableauFrequence(std::string mot = "", std::vector <char> liste = {});

/**
 * Vérifie si tous les caractères d'une liste sont contenus dans la réserve
   en calculant les tableaux de fréquence de la liste et de la réserve et les comparant.
 * @param liste         un tableau des caractères 
 * @param reserve       un tableau des caractères 
 * @return un booléen   compareTableauFrequence(reserve, liste, false) (tabFreq de la liste <= tabFreq de la reserve)
 */
bool estDansReserve(std::vector <char> liste, std::vector <char> reserve);

/**
 * Vérifie si le mot est possible à formé étant donné la reserve et le mot courant
 * @param motAModifier          le mot courant
 * @param reserve               la reserve du joueur
 * @param motAFormer            le mot que l'on veut vérifier
 * @return un booléen           true si (tabFreq de motAModifier <= tabFreq de motAFormer) && (tabFreq de motAFormer <= tabFreq de vrac (motAModifer + reserve))
 */
bool possibleFormeMot(std::string motAModifier, std::vector <char> reserve, std::string motAFormer);

/**
 * Modifie la réserve du joueur après la formation d'un nouveau mot sur le plateau
 * @param motAModifier      le mot courant sur le plateau que le joueur souhaite modifier
 * @param reserve           la réserve du joueur
 * @param motAFormer        le nouveau mot formé par le joueur
 * @return reserve          la réserve du joueur après la modification
 */
std::vector <char> modifieReserveApresFormerMot(std::string motAModifier, std::vector <char> reserve, std::string motAFormer);

/**
 * Vérifie si un nouveau mot proposé par le joueur est valide 
   (en comprenant estDansDict et possibleFormeMot avec les restriction de longueur mininale de mots et le nombre maximale des colonnes)
 * @param precedentMot          le mot précédent
 * @param nouveauMot            le nouveau mot
 * @param reserveDuJoueur       la réserve actuelle du joueur
 * @param dict                  le dictionnaire
 * @param minLongueurMot        longueur minimale requise pour un mot valide
 * @param maxColonne            longueur maximale requise pour un mot valide
 * @return un booléen           true si le nouveau mot est valide, false sinon.
 */
bool motValide(std::string precedentMot, std::string nouveauMot, std::vector <char> reserveDuJoueur, std::set <std::string> dict, int minLongueurMot, int maxColonne);

/**
 * Met à jour les possibilités de jeu en fonction de l'option spécifiée.
 * @param option                un caractère spécifiant l'action à effectuer
 * @param possibilites          une liste des possibilités actuelle avec ses valeurs
 * @return possibilites         une liste des possibilités actuelle avec ses valeurs après la mise à jour 
 */
std::map <char,int> metAJourPossibilites(char option, std::map <char,int> possibilites);
/**
 * Initialise les possibilités de jeu pour chaque lettre au début d'un tour
 * @param nombreTours               le nombre total de tours actuel dans la partie
 * @param nombreEquipes             le nombre d'équipes dans la partie
 * @param nombreJarnacChaqueTour    le nombre maximum de fois où Jarnac est annoncé à chaque tour
 * @param aideDeIA                  un booléen pour spécifier si l'aide de l'IA est activée
 * @param laisseIAJouer             un booléen pour spécifier si l'IA peut jouer directement des mots
 * @return possibilites             une liste des possibilités actuelle avec ses valeurs
 */
std::map <char, int> initialisePossibilites(int nombreTours, int nombreEquipes, int nombreJarnacChaqueTour, bool aideDeIA, bool laisseIAJouer);

/**
 * Met à jour le plateau, la réserve et les possibilités du joueur qui compose un nouveau mot sur le plateau
 * @param tourIDJoueurComposeMot            ID du joueur composant le mot               (0 -> nombreEquipes - 1)
 * @param ligneAModifier                    la ligne du plateau où le mot est composé   (0 -> nombreEquipes - 1)
 * @param ancienMot                         le mot précédent sur la ligne à modifier
 * @param nouveauMot                        le nouveau mot composé par le joueur
 * @param plateauJoueurComposeMot           le plateau du joueur qui compose le mot
 * @param reserveJoueurComposeMot           la réserve du joueur qui compose le mot
 * @param possibilites                      les possibilités du joueur qui compose le mot
 * @param actionsDuTour                     les actions effectuées pendant le tour
 *
 */
void metAJourPlateauComposerMot(int tourIDJoueurComposeMot, int ligneAModifier, std::string ancienMot, std::string nouveauMot,
                                std::vector <std::string>& plateauJoueurComposeMot, std::vector <char>& reserveJoueurComposeMot, std::map <char, int>& possibilites,
                                std::string& actionsDuTour);
/**
 * Met à jour les plateaux, la réserve et les possibilités du joueur qui annonce et du joueur sur lequel Jarnac est effectué
 * @param tourIDJoueurAnnonceJarnac         ID du joueur annonçant Jarnac                   (0 -> nombreEquipes - 1)
 * @param tourIDJoueurEtreJarnac            ID du joueur sur lequel Jarnac est effectué     (0 -> nombreEquipes - 1)
 * @param ligneAModifier                    la ligne du plateau où Jarnac est effectué
 * @param ancienMot                         le mot précédent sur la ligne à modifier
 * @param nouveauMot                        le nouveau mot pour Jarnac
 * @param plateau                           les plateaux de tous les joueurs
 * @reserveJoueurEtreJarnac                 la réserve du joueur sur lequel Jarnac est effectué
 * @possibilites                            les possibilités du joueur qui annonce Jarnac
 * @param actionsDuTour                     les actions effectuées pendant le tour
 */
void metAJourPlateauxJarnac(int tourIDJoueurAnnonceJarnac, int tourIDJoueurEtreJarnac, int ligneAModifier, std::string ancienMot, std::string nouveauMot, 
                            std::vector <std::vector <std::string>>& plateau, std::vector <char>& reserveJoueurEtreJarnac, std::map <char,int>& possibilites,
                            std::string& actionsDuTour); 

/**
 * Met à jour la réserve du joueur après avoir pioché un certain nombre de lettres du sac.
 * @param reserveJoueurPioche               la réserve du joueur qui pioche des lettres
 * @param nombreLettresAPiocher             le nombre de lettres que le joueur pioche
 * @param sac                               le sac de lettres
 * @param possibilites                      les possibilités du joueur qui pioche des lettres
 * @param actionsDuTour                     les actions effectuées pendant le tour
 */
void metAJourReserveApresPiocherLettres(std::vector <char>& reserveJoueurPioche, int nombreLettresAPiocher, std::queue <char>& sac,
                                        std::map <char,int>& possibilites, std::string& actionsDuTour);

/**
 * Met à jour la réserve du joueur après avoir échangé un ensemble spécifié de lettres avec le sac.
 * @param reserveJoueurEchange              la réserve du joueur qui échange des lettres
 * @param listeLettres                      la liste des lettres échangées
 */
void metAJourReserveApresEchangeLettres(std::vector <char>& reserveJoueurEchange, std::vector <char> listeLettres, std::queue <char>& sac,
                                        std::map <char, int>& possibilites, std::string& actionsDuTour);

