//
//  DobbeltLenketSirkulærListe.hpp
//  Lab1 (prog.3)
//
//  Created by Øyvind Nordbø on 22/09/2024.
//

#ifndef DobbeltLenketSirkul_rListe_hpp
#define DobbeltLenketSirkul_rListe_hpp
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std; //angra fort, men for lat til å bytte om.
//-----------------------------------------------------------------------------------------------------------
class Node {
public:
    int ID;
    string NAME;
    shared_ptr<Node> NEXT;
    shared_ptr<Node> PREV;

    //--Konstruktør-----------
    Node(int id, string name)
        : ID{ id }, NAME{ name }, NEXT{ nullptr }, PREV{ nullptr } {}
};
//-----------------------------------------------------------------------------------------------------------
class DobbeltLenketSirkulaerListe{
public:
    shared_ptr<Node> HEAD;
    shared_ptr<Node> TAIL;

    DobbeltLenketSirkulaerListe(): HEAD{nullptr}, TAIL{nullptr}{}
    //--------------------------------
    void leggTil(int id, string name);
    void slett(int id);
    void slett(string name);
    friend ostream& operator<<(ostream& ost, const DobbeltLenketSirkulaerListe& list);
    unsigned long finnLengde();
    
    //sorterings funksjoner
    vector<shared_ptr<Node>> lagVektor(); //for å dele opp listen til sortering
    vector<shared_ptr<Node>> merge(vector<shared_ptr<Node>> &left, vector<shared_ptr<Node>> &right);
    vector<shared_ptr<Node>> mergeSort(vector<shared_ptr<Node>> &liste);
    void oppdaterListe(const vector<shared_ptr<Node>> &sortedNodes);
    void doMergeSort();
};
//-----------------------------------------------------------------------------------------------------------

#endif /* DobbeltLenketSirkul_rListe_hpp */
