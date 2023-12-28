#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>

/* On définit tabIA pour permettre IA à stocker les listes de possibilités de mots à former pour chaque ligne de chaque plateau de chaque joueur dans la partie.
 * std::vector <std::vector <std::vector <std::set <std::string>>>> tabIA(nombreIA, 
                                                                              std::vector <std::vector <std::set <std::string>>> (nombreEquipes, 
                                                                              std::vector <std::set <std::string>> (maxLigne)    )  
                                                                          );
 
 *  tabIA [ nombreIA ] [ nombreEquipes ] [ maxLigne ]   est un set <string>: l'ensemble de mots ayant ses tableau de fréquence >= tableau de fréquence de mot sur cette ligne
 *             ^               ^              ^
 *          ID de IA      ID de joueur      numéro de ligne 
 *    (0 -> nombreIA)  (0 -> nombreEquipes) (0 -> maxLigne - 1)
 *
 *  Exemple:
 *  Si la ligne 2 du plateau de joueur avec ID = 1 contenant le mot: bon
 *  alors, l'ensemble de mots ayant ses tableau de fréquence >= tableau de fréquence de mot "bon" est:
 *      bon, bonne, bonbon, bonjour, bonsoir, noble, ...
 *  Du coup, pour toutes les IA, ses tabIA[ID de IA][ID de joueur = 1][ligne = 1] seront : {"bon","bonne","bonbon","bonjour","bonsoir", "noble", ...}
 *
 *  Grâce à tabIA, au lieu de faire une boucle chaque mot dans le dictionnaire de l'IA pour vérifier s'il est possible de former ce mot
 *  en fonctionne de la reserve actuelle et le mot courant sur la ligne,
 *  IA peut simplement faire une boucle vérifier chaque mot dans l'ensemble (qui est sensiblement plus petit que le dictionnaire).
 *
 * Chaque fois qu'un joueur modifie un mot sur le plateau, il faut mettre à jour tabIA pour toutes les IA sur la ligne spécifique du plateau sur laquelle se trouve le mot.
 *
 * Plus le mot est long, plus l'ensemble est petit, ce qui permet à l'IA de rechercher plus rapidement le meilleur mot possible pour former sur son plateau ainsi
 * annoncer Jarnac contre d'autres joueurs 
 * <!> Si une ligne est vide et le joueur y met son nouveau mot, l'AI n'a pas d'autre choix que de chercher dans tout le dictionnaire pour cette seule fois <!>
 */

/**
 * Extrait la difficulté spécifiée dans le nom de l'IA
 * @param nomIA                 le nom de l'IA, contenant l'indication de la difficulté
 * @return                      la difficulté extraite (Facile, Moyen, Difficile, Impossible)
 */
std::string extraitDifficulte(std::string nomIA);

/**
 * Initialise les probabilités pour la formation de mots en fonction de la difficulté
 * @param difficulte            le niveau de difficulté de l'IA
 * @param maxColonne            la longueur maximale d'un mot autorisée
 * @return                      un vecteur représentant les probabilités pour chaque longueur de mot
 */
std::vector <int> initialiseProbabilitieDict(std::string difficulte, int maxColonne); 

/**
 * Initialise le dictionnaire de mots pour l'IA en fonction de la difficulté
 * @param difficulte            le niveau de difficulté de l'IA
 * @param dictPourJoueurs       le dictionnaire de mots utilisé par les joueurs
 * @param maxColonne            la longueur maximale d'un mot autorisée
 * @return                      le dictionnaire de l'IA extrayant du dictionnaire pour les joueurs selon la difficulté de l'IA
 */
std::set <std::string> initialiseDictPourIA(std::string difficulte, const std::set <std::string>& dictPourJoueurs, int maxColonne);

/**
 * Met à jour l'ensemble des mots d'une IA pour une ligne spécifique
 * @param nouveauMot            le nouveau mot formé sur la ligne
 * @param dictPourIA            le dictionnaire de l'IA
 * @param ligneTabIA            l'ensemble de mots pour la ligne spécifié
 */
void misAJourTabIAPourUneLigne(std::string nouveauMot, const std::set <std::string>& dictPourIA, std::set <std::string>& ligneTabIA); 

/**
 * Met à jour tous ensembles des mots des IAs pour une ligne spécifique.
 * @param joueur                    ID du joueur IA.
 * @param ligne                     la ligne spécifique à mettre à jour
 * @param nouveauMot                le nouveau mot formé sur la ligne
 * @param dictPourIA                le dictionnaire de mots pour les IA
 * @param tabIA                     les tableaux globals des ensembles des mots pour toutes les IA.
 */
void misAJourTabIAPourUneLignePourTousIA(int joueur, int ligne, std::string nouveauMot, const std::vector <std::set <std::string>>& dictPourIA, std::vector <std::vector <std::vector <std::set <std::string>>>>& tabIA);

/**
 * Met à jour l'ensemble des mots d'une IA pour un plateau spécifique.
 * @param plateau                   le plateau spécifié
 * @param dictPourIA                le dictionnaire de l'IA
 * @param plateauTabIA              le tableau des ensembles des mots d'une IA pour le plateau spécifié
 */
void misAJourTabIAPourUnPlateau(const std::vector <std::string>& plateau, const std::set <std::string>& dictPourIA, std::vector <std::set <std::string>>& plateauTabIA);

/**
 * Trouve le meilleur mot possible à former sur une ligne en fonctionne de l'ensemble des mots, de la reserve actuelle et le mot précédent.
 * @param precedentMot              le mot précédent sur la ligne
 * @param reserve                   la réserve de lettres
 * @param surEnsemble               l'ensemble de mots pour la ligne
 * @param dictPourIA                le dictionnaire de l'IA
 * @param minLongueurMot            la longueur minimale du mot à former
 * @param maxColonne                la longueur maximale autorisée pour le mot
 * @return                          le meilleur mot possible à former
 */
std::string meuilleurMotAFormer(std::string precedentMot, std::vector <char> reserve, std::set <std::string> surEnsemble, const std::set <std::string>& dictPourIA, int minLongueurMot, int maxColonne);

/**
 * Génère une liste de meuilleurs mots possibles pour chaque ligne d'un plateau.
 * @param plateauUnJoueur           le plateau d'un joueur spécifique
 * @param reserve                   la réserve de lettres de l'IA
 * @param plateauTabIA              les ensembles des mots sur le plateau
 * @param dictPourIA                le dictionnaire de mots pour l'IA
 * @param minLongueurMot            la longueur minimale du mot à former
 * @param maxColonne                la longueur maximale autorisée pour le mot
 * @return                          une liste de meuilleurs mots possibles pour chaque ligne du plateau
 */
std::vector <std::string> listeMotsPossiblesAIPourUnePlateau(const std::vector <std::string>& plateauUnJoueur, std::vector <char> reserve, const std::vector <std::set <std::string>>& plateauTabIA, const std::set <std::string>& dictPourIA, int minLongueurMot, int maxColonne);

/**
 * Génère une liste de meuilleurs mots possibles pour chaque ligne de tous plateaux.
 * @param plateau                   les plateaux des joueurs
 * @param reserve                   les réserves des joueurs
 * @param tabIA                     les tableaux des ensembles des mots pour toutes les IA
 * @param dictPourIA                le dictionnaire de l'IA
 * @param minLongueurMot            la longueur minimale du mot à former
 * @param maxColonne                la longueur maximale autorisée pour le mot
 * @return                          une liste des mots possibles pour chaque joueur sur tous les plateaux.
 */
std::vector <std::vector <std::string>> listePossibilitesMotAITousPlateaux(const std::vector <std::vector <std::string>>& plateau, std::vector <std::vector <char>> reserve,
                                                                           const std::vector <std::vector <std::set <std::string>>>& tabIA, const std::set <std::string> dictPourIA, int minLongueurMot, int maxColonne);


/**
 * Trouve l'indice du meilleur mot dans une liste de mots généré par listeMotsPossiblesAIPourUnePlateau.
 * @param listeMots                 la liste des meuilleurs mots possible à former
 * @return                          l'indice du meilleur mot dans la liste.
 */
int indiceMeuilleurMot(const std::vector <std::string>& listeMots);

/**
 * Vérifie s'il est possible d'annocer Jarnac pour l'IA.
 * @param listeMeuilleursMotsIATousPlateaux         la liste des meilleurs mots possibles pour tous les plateaux
 * @param tourIA                                    ID de l'IA
 * @return                                          true si Jarnac est possible, sinon false
 */
bool possibleJarnac(const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, int tourIA);

/**
 * Trouve le meilleur mot pour annoncer Jarnac contre un autre joueur.
 * @param listeMeuilleursMotsIATousPlateaux             la liste des meilleurs mots possibles pour tous les plateaux.
 * @param tourIA                                        ID de l'IA
 * @param plateau                                       les plateaux des joueurs
 * @return                                              une paire représentant le numéro du plateau et l'indice du meilleur mot pour le plateau.
 */
std::pair <int,int> meuilleurMotPourJarnacIA(const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, int tourIA, const std::vector <std::vector <std::string>>& plateau);

/**
 * Vérifie si l'IA peut former un mot
 * @param listeMeuilleursMotsIATousPlateaux             la liste des meilleurs mots possibles pour tous les plateaux.
 * @param tourIA                                        ID de l'IA
 * @return                                              true si l'IA peut former un mot, sinon false.
 */
bool possibleIAFormerMot(std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, int tourIA);

/**
 * Vérifie s'il y a plus de consonnes que de voyelles dans la réserve
 * @param reserve                       la réserve de l'IA.
 * @param nombre                        la différence minimale entre le nombre de consonnes et de voyelles.
 * @return                              true s'il y a plus de consonnes que de voyelles, sinon false.
 */
bool plusDeConsonnesQueVoyelles(std::vector <char> reserve, int nombre);

/**
 * Retourne les premières consonnes dans la réserve de l'IA jusqu'à un certain nombre.
 * @param reserve                       la réserve de l'IA.
 * @param nombre                        le nombre de premières consonnes à extraire.
 * @return                              un tableau contenant les premières consonnes extraites.
 */
std::vector <char> premieresConsonnesReserve(std::vector <char> reserve, int nombre);

/**
 * Prend une décision sur l'action à effectuer pour un tour spécifique de l'IA.
 * @param possibilites                          les possibilités d'action de l'IA (J, M, T, E, P)
 * @param listeMeuilleursMotsIATousPlateaux     la liste des meilleurs mots possibles pour tous les plateaux
 * @param reserveIA                             la réserve de l'IA
 * @param tourIA                                ID de l'IA
 * @return                                      une caractère représentant l'action choisie par l'IA
 */
char decisionIA(std::map <char,int> possibilites, const std::vector <std::vector <std::string>>& listeMeuilleursMotsIATousPlateaux, std::vector <char> reserveIA, int tourIA);


