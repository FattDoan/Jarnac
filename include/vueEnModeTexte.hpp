#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>


/*
 *  Toutes les fonctions de le fichier vueEnModeTexte.cpp servent à afficher et à recevoir les données du joueur. 
 *  Toutes les entrées sont normalisées par la fonction entreeLigne :
 *  que l'entrée que le joueur doit saisir soit un entier ou une chaîne de caractères, 
 *  l'entrée sera récupérée sous forme de chaîne de caractères et l'entier pourra être extrait par la fonction extraitInt.
 *  
 *  Toutes les entrées sont formatées en minuscules. Uniquement converti en majuscule lors de l'affichage.
 *
 *
 *
 */

void remplie(char caractere, int longueur, std::string texte = "", std::string position = "");
void afficheEcartEntrePlateaux(std::string texte = "");
void afficheTitreJeu(int maxColonne);
void afficheNomEtPoints(std::string nomA, int pointA, std::string nomB, int pointB, int minLongueurMot, int maxColonne);
void afficheListeDePoints(int minLongueurMot, int maxColonne);
void affichePlateaux(std::vector <std::string> plateau1, std::vector <std::string> plateau2, int minLongueurMot, int maxColonne);
void afficheReserves(std::vector <char> reserve1, std::vector <char> reserve2);
void afficheEtatDuJeu(std::vector <std::vector <std::string>> plateau, std::vector <std::vector <char>> reserve, std::vector <std::vector <std::string>> nomEquipes, int maxLigne, int minLongueurMot, int maxColonne, std::string actionsDuTour);
int numeroDeLigne(std::string input);
int extraitInt(std::string input);
std::string entreeLigne();
char reponseDuJoueurPossibilites(std::map <char,int> possibilites); 
std::string reponseDuJoueurFormeMot(std::string precedentMot, std::vector <char> reserveDuJoueur, std::set <std::string> dict, int minLongueurMot, int maxColonne);
int reponseDuJoueurLigne(std::vector <std::string> plateauDuJoueur); 
std::vector <char> reponseDuJoueurEchanger(std::vector <char> reserve, int nombre);
int reponseDuJoueurNomAnnonceJarnac(std::vector <std::vector <std::string>> nomEquipes, int equipe);
std::vector <std::vector <std::string>> reponsesDesJoueursDemandeDePrenom(); 
std::string reponseDuJoueurDemandeDictionnaire(std::vector <std::string> listeLangue);
int reponseDuJoueurDemandeNombreLignesPlateau();
int reponseDuJoueurDemandeColonnesPlateau();
int reponseDuJoueurDemandeLongueurMinimaleMot();
bool reponseDuJoueurDemandeAideIAPlateau();
bool reponseDuJoueurDemandeLaisserIAJouer();
int reponseDuJoueurDemandeNombreJarnacChaqueTour();
std::string reponseDuJoueurDifficulteIA();
std::string afficheNomUneEquipe(std::vector <std::string> listeNom);
void afficheConfigurationActuelle(std::string langue, int maxLigne, int minLongueurMot, int maxLongueurMot, int nombreJarnacChaqueTour, std::vector <std::vector <std::string>> nomEquipes, bool aideDeIA, bool laisseIAJouer);
void afficheJoueurGagnant(std::vector<std::vector <std::string>> plateau, std::vector <std::vector <std::string>> nomEquipe);
void afficheAideDeIA(std::vector <std::string> listeMots); 
void afficheOptionNonValide();
void afficheFichierTexte(std::string nomFichier); 
void videEcran();
