//
//  main.cpp
//  Lab1 (prog.3)
//
//  Created by Øyvind Nordbø on 12/09/2024.
//
#include <iostream>
#include "DobbeltLenketSirkulærListe.hpp"

int main() {
    DobbeltLenketSirkulaerListe theList;
    DobbeltLenketSirkulaerListe emptyList;

    theList.leggTil(1, "Olav");
    theList.leggTil(9, "Lars");
    theList.leggTil(2, "Olav");
    theList.leggTil(3, "Mohammed");
    theList.leggTil(3, "Salah");
    theList.leggTil(8, "Trent Alexander");
    theList.leggTil(4, "Arnold");
    theList.leggTil(0, "Virgil");
    theList.leggTil(5, "Van Dijk");
    theList.leggTil(6, "Gakpo");

    std::cout << theList << std::endl;

    theList.slett("Olav"); // Deletes the first occurrence of "Olav"
    theList.slett(3);       // Deletes both nodes with ID 3
    theList.slett("Gakpo"); // Deletes Gakpo

    std::cout << theList << std::endl;
    std::cout << emptyList << std::endl;

    return 0;
}
