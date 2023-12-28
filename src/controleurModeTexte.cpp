#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

#include "IA.hpp"
#include "moteur.hpp"
#include "vueEnModeTexte.hpp"


bool lanceJeu(std::set <std::string> dictPourJoueurs, int maxLigne, int minLongueurMot, int maxColonne, int nombreJarnacChaqueTour, std::vector <std::vector <std::string>> nomEquipes, bool aideDeIA, bool laisseIAJouer) {
    // -----------------------
    // |Initialisation du jeu|
    // -----------------------
    int nombreEquipes = nomEquipes.size();
    std::vector<std::vector <std::string>> plateau(nombreEquipes, std::vector <std::string> (maxLigne,""));
    std::vector<std::vector <char>> reserve(nombreEquipes, std::vector <char> (0));
    std::queue<char> sac = initialiseSac(nombreLettresDuJeu());
    std::vector <bool> dejaPioche6Lettres(nombreEquipes,false);
    std::vector <std::vector <std::set <std::string>>> tabAideIA(nombreEquipes, std::vector <std:: set <std::string>> (maxLigne));
    int tour = 0, nombreTours = 0, option;
    bool tourChange = false;
    //===========================================================================================//
    // ------------------------
    // |Initialisation de l'IA|
    // ------------------------
    int nombreIA = 0;
    std::vector <int> idIA(nombreEquipes,-1);
    std::vector <std::set <std::string>> dictPourIA;
    std::vector <std::vector <std::string>> listeMeuilleursMotsIA;
    for (int i = 0; i < nombreEquipes; i++) {
        if (nomEquipes[i][0].substr(1,2) == "IA") {
            idIA[i] = nombreIA++;
            std::string difficulte = extraitDifficulte(nomEquipes[i][0]);
            dictPourIA.push_back(initialiseDictPourIA(difficulte, dictPourJoueurs, maxColonne));
        }
    } 
    std::vector <std::vector <std::vector <std::set <std::string>>>> tabIA(nombreIA, 
                                                                              std::vector <std::vector <std::set <std::string>>> (nombreEquipes, 
                                                                              std::vector <std::set <std::string>> (maxLigne)    )  
                                                                          );
    //===========================================================================================//
    //Preparer pour le premier tour
    std::map <char,int> possibilites = initialisePossibilites(nombreTours, nombreEquipes, nombreJarnacChaqueTour, aideDeIA, laisseIAJouer);
    std::string actionsDuTour = "C'est le tour de " + afficheNomUneEquipe(nomEquipes[0]) + "\n";
    metAJourReserveApresPiocherLettres(reserve[0], 6, sac, possibilites, actionsDuTour);
    dejaPioche6Lettres[tour] = true;
    //===========================================================================================//
    //Boucle du jeu : indefiniment jusqu'a ce qu'un joueur gagne
    while (true) {
        // ---------------------
        // |Rendre le graphique|
        // ---------------------
        videEcran();
        afficheEtatDuJeu(plateau, reserve, nomEquipes, maxLigne, minLongueurMot, maxColonne, actionsDuTour);
             
        // ---------------------------------
        // |Mettre a jour la logique du jeu|
        // ---------------------------------      
        //Determiner quel tour
        //Si c'est le tour de l'IA -> On obtient son choix basé sur son tabIA
        //Si c'est le tour de l'humain -> On lui demande 
        char option;
        bool tourIA = (idIA[tour] != -1);
        if (tourIA) {
            listeMeuilleursMotsIA = listePossibilitesMotAITousPlateaux(plateau, reserve, tabIA[idIA[tour]], dictPourIA[idIA[tour]], minLongueurMot, maxColonne);
            option = decisionIA(possibilites, listeMeuilleursMotsIA, reserve[tour], tour);
        }   
        else {
            option = reponseDuJoueurPossibilites(possibilites);
        }
        //===================================================================================================================================//


        int tourIDJoueurAnnonceJarnac = tour;
        int tourIDJoueurEtreJarnac, ligneAModifier;
        std::string ancienMot, nouveauMot;

        switch (option) {
            case 'J' : //Annoncer Jarnac
                {
                    if (tourIA) {
                        std::pair <int,int> tmp = meuilleurMotPourJarnacIA(listeMeuilleursMotsIA, tour, plateau);
                        tourIDJoueurEtreJarnac = tmp.first;
                        ligneAModifier = tmp.second;
                        ancienMot = plateau[tourIDJoueurEtreJarnac][ligneAModifier];
                        nouveauMot = listeMeuilleursMotsIA[tourIDJoueurEtreJarnac][ligneAModifier];
                    }
                    else {
                        tourIDJoueurEtreJarnac = reponseDuJoueurNomAnnonceJarnac(nomEquipes,tour);
                        ligneAModifier = reponseDuJoueurLigne(plateau[tourIDJoueurEtreJarnac]);
                        ancienMot = plateau[tourIDJoueurEtreJarnac][ligneAModifier];
                        nouveauMot = reponseDuJoueurFormeMot(ancienMot,reserve[tourIDJoueurEtreJarnac],dictPourJoueurs, minLongueurMot, maxColonne);
                        if (nouveauMot == "p") {
                            tourChange = true;
                            break;
                        } 
                    }
                    if (nombreIA > 0) {
                        misAJourTabIAPourUneLignePourTousIA(tourIDJoueurEtreJarnac, ligneAModifier, "", dictPourIA, tabIA);
                        misAJourTabIAPourUneLignePourTousIA(tour, premiereLigneVide(plateau[tour]), nouveauMot, dictPourIA, tabIA);
                    }

                    metAJourPlateauxJarnac(tour,tourIDJoueurEtreJarnac, ligneAModifier, ancienMot, nouveauMot, plateau, reserve[tourIDJoueurEtreJarnac], possibilites, actionsDuTour);
                   break;
                }
            case 'M' : //Composer un nouveau mot
                {
                    if (tourIA) {
                        ligneAModifier = indiceMeuilleurMot(listeMeuilleursMotsIA[tour]);
                        ancienMot = plateau[tour][ligneAModifier];
                        nouveauMot = listeMeuilleursMotsIA[tour][ligneAModifier];
                    }
                    else {
                        ligneAModifier = reponseDuJoueurLigne(plateau[tour]);
                        ancienMot = plateau[tour][ligneAModifier];
                        nouveauMot = reponseDuJoueurFormeMot(ancienMot,reserve[tour],dictPourJoueurs, minLongueurMot, maxColonne);
                        if (nouveauMot == "p") {
                            tourChange = true;
                            break;
                        }
                    }

                    if (nombreIA > 0) {
                        misAJourTabIAPourUneLignePourTousIA(tour, ligneAModifier, nouveauMot, dictPourIA, tabIA);
                    }

                    metAJourPlateauComposerMot(tour, ligneAModifier, ancienMot, nouveauMot, plateau[tour], reserve[tour], possibilites,actionsDuTour);
                    break;
                }
            case 'T' : //Tirer une lettre
                {
                    metAJourReserveApresPiocherLettres(reserve[tour], 1, sac, possibilites, actionsDuTour);
                    break;
                }
            case 'E' : //Echanger 3 lettres de la reserve au sac
                {
                    std::vector <char> listeLettres;
                    if (tourIA) {
                        listeLettres = premieresConsonnesReserve(reserve[tour],3);
                    }
                    else {
                         listeLettres = reponseDuJoueurEchanger(reserve[tour],3);
                    }
                    metAJourReserveApresEchangeLettres(reserve[tour], listeLettres, sac, possibilites, actionsDuTour);
                    break;
                }
            case 'P' : //Passer son tour
                {
                    tourChange = true;
                    break;
                }
            case 'V' : //Voir les coups possibles de l'IA
                {
                    afficheAideDeIA(listeMotsPossiblesAIPourUnePlateau(plateau[tour], reserve[tour], tabAideIA[tour], dictPourJoueurs, minLongueurMot, maxColonne));
                    std::cout << "Appuyer sur Entrée pour continuer ..." << '\n';
                    std::cin.ignore();
                    break;
                }
            case 'L' : //Laisser IA jouer à la place du joueur
                {
                    std::string difficulte = reponseDuJoueurDifficulteIA();
                    idIA[tour] = nombreIA++;
                    dictPourIA.push_back(initialiseDictPourIA(difficulte, dictPourJoueurs, maxColonne));
                    tabIA.push_back(std::vector <std::vector <std::set <std::string>>> (nombreEquipes, std::vector <std::set <std::string>> (maxLigne)));
                    for (int i = 0; i < nombreEquipes; i++) {
                        misAJourTabIAPourUnPlateau(plateau[i], dictPourIA[idIA[tour]], tabIA[idIA[tour]][i]);
                    }
                    break;
                }
            case 'A' : //Abandonner la partie
                {
                    return false;
                    break;
                }
        }
        //Met à jour l'IA qui aide à voir les coups possibles 
        if (aideDeIA) {
            misAJourTabIAPourUnPlateau(plateau[tour], dictPourJoueurs, tabAideIA[tour]);
        }

        //Passer tour logique contrôleur
        if (tourChange) {
            //Quand un joueur passe son tour, il faut mettre a jour les possibilites et les actionsDuTour pour le joueur suivant
            tourChange = false;
            nombreTours++;
            tour = nombreTours % nombreEquipes;
            possibilites = initialisePossibilites(nombreTours, nombreEquipes, nombreJarnacChaqueTour, aideDeIA, laisseIAJouer);
            //Condition gagnant
            if (premiereLigneVide(plateau[tour]) == plateau[tour].size()) {
                afficheJoueurGagnant(plateau,nomEquipes);
                std::cout << "Appuyer sur Entrée pour revenir au menu principal." << '\n';
                std::cin.ignore();
                return true;
            }
            actionsDuTour = "C'est le tour de " + afficheNomUneEquipe(nomEquipes[tour]) + "\n";
        }
        //=========================================================================================================================//
        //Si le joueur n'a pas encore pioche 6 lettre pour son premier tour du jeu
        if (!dejaPioche6Lettres[tour]) {
            metAJourReserveApresPiocherLettres(reserve[tour], 6, sac, possibilites, actionsDuTour);
            dejaPioche6Lettres[tour] = true;
        }
        //==========================================================================================================================//
    }
    return true;
}
