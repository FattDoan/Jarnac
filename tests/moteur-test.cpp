#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <string>
#include <set>
#include <queue>

#include "doctest.h"
#include "moteur.hpp"
#include "gestionDict.hpp"


TEST_CASE("Tester la fonction lettreEnMajuscules") {
    CHECK(lettreEnMajuscules('a') == 'A');
    CHECK(lettreEnMajuscules('A') == 'A');
    CHECK(lettreEnMajuscules('1') == '1');
}

TEST_CASE("Tester la fonction motEnMajuscules") {
    CHECK(motEnMajuscules("sad") == "SAD");
    CHECK(motEnMajuscules("SAD") == "SAD");
    CHECK(motEnMajuscules("3221adaCC") == "3221ADACC");
}
TEST_CASE("Tester la fonction motEnMinuscules") {
    CHECK(motEnMinuscules("TEST") == "test");
    CHECK(motEnMinuscules("test") == "test");
    CHECK(motEnMinuscules("34432sdDSdf") == "34432sddsdf");
}
TEST_CASE("Tester la fonction melangeSac") {
    std::queue <char> sac1 = initialiseSac(nombreLettresDuJeu());
    std::queue <char> sac2 = melangeSac(sac1);
    std::queue <char> sac3 = melangeSac(sac2);
    CHECK(sac1 != sac2);
    CHECK(sac2 != sac3);
}
TEST_CASE("Tester la fonction piocheDansSac") {
    std::queue <char> sac = initialiseSac(nombreLettresDuJeu());
    std::vector <char> reserve(0);
    CHECK(piocheDansSac(sac, 1, reserve) == std::vector <char> {sac.front()});
}
TEST_CASE("Tester la fonction enleveLettresDansReserve") {
    std::vector <char> reserve = {'A','B','B'};
    CHECK(enleveLettresDansReserve(std::vector <char> {'A','B'}, reserve) == std::vector <char> {'B'});
    CHECK(enleveLettresDansReserve(std::vector <char> {'B'}, reserve) == std::vector <char> {'A','B'});
    CHECK(enleveLettresDansReserve(std::vector <char> {'A','B','B'}, reserve) == std::vector <char> {});
}
TEST_CASE("Tester la fonction ajouteLettresAuSac") {
    //Puisque le sac est mélangé, on ne peut que comparer sa taille avant et après
    std::queue <char> sac = initialiseSac(nombreLettresDuJeu());
    CHECK(ajouteLettresAuSac(std::vector <char> {'A','B','C'}, sac).size() == sac.size() + 3);
    CHECK(ajouteLettresAuSac(std::vector <char> {}, sac).size() == sac.size() + 0);
    CHECK(ajouteLettresAuSac(std::vector <char> {'Z'}, sac).size() == sac.size() + 1);
}
TEST_CASE("Tester la onction modifiePlateau") {
    std::vector <std::string> plateau = { "bonjour",
                                          "bon",
                                          "jour"
                                         };
    CHECK(modifiePlateau(plateau, 1, "bonbon") == std::vector <std::string> { "bonjour",
                                                                              "bonbon",
                                                                              "jour"
                                                                            });
    CHECK(modifiePlateau(plateau, 0, "xxxxx") == std::vector <std::string> { "xxxxx",
                                                                             "bon",
                                                                             "jour"
                                                                            });
    CHECK(modifiePlateau(plateau, 2, "") == std::vector <std::string> { "bonjour",
                                                                        "bon",
                                                                        ""
                                                                      });
}
TEST_CASE("Tester la fonction comptePoints") {
    std::vector <std::string> plateau = { "bonjour",
                                          "bon",
                                          "jour"
                                         };
    CHECK(comptePoints(std::vector <std::string> {}) == 0);
    CHECK(comptePoints(plateau) == 74);
    plateau.push_back("modifier");
    CHECK(comptePoints(plateau) == 138);
    plateau = modifiePlateau(plateau,0,"");
    CHECK(comptePoints(plateau) == 89);

}
TEST_CASE("Tester la fonction premiereLigneVide") {
   std::vector <std::string> plateau = { "bonjour",
                                          "",
                                          "jour"
                                         };
   CHECK(premiereLigneVide(plateau) == 1);
   plateau = modifiePlateau(plateau, 0, "");
   CHECK(premiereLigneVide(plateau) == 0);
   plateau = modifiePlateau(plateau, 0, "wqeqw");
   plateau = modifiePlateau(plateau, 1, "adaad");
   CHECK(premiereLigneVide(plateau) == 3);
}
TEST_CASE("Tester la fonction estDansReserve") {
   std::vector <char> reserve = {'a','c','d','a','e'};
   CHECK(estDansReserve(std::vector <char> {'a','c'}, reserve) == true);
   CHECK(estDansReserve(std::vector <char> {'a','a','a'}, reserve) == false);
   CHECK(estDansReserve(std::vector <char> {'a','c','d','a','e','c'}, reserve) == false);
   CHECK(estDansReserve(std::vector <char> {'d'}, reserve) == true);
}
TEST_CASE("Test la fonction possibleFormeMot") {
   std::vector <char> reserve = {'a','a','a','e'};
   CHECK(possibleFormeMot("eee", reserve, "aaaeee") == true);
   CHECK(possibleFormeMot("", reserve, "aae") == true);
   CHECK(possibleFormeMot("c", reserve, "ae") == false);
   CHECK(possibleFormeMot("e", reserve, "aaeee") == false); 
}
