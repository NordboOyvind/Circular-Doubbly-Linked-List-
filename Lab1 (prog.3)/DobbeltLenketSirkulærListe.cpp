//
//  DobbeltLenketSirkulærListe.cpp
//  Lab1 (prog.3)
//
//  Created by Øyvind Nordbø on 22/09/2024.
//
#include "DobbeltLenketSirkulærListe.hpp"
#include <iostream>

//====================================================--
//
//         FUNKSJONS IMPLIMENTASJONER.
// ┌───────────────────────────────────
// ▼
//====================================================--


void printLines() {
    std::cout << "-------------------------------------------\n";
}

//=========================================================================================================--
// 1.                 leggTil(id)                    //
//====================================================
void DobbeltLenketSirkulaerListe::leggTil(int id, std::string name) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(id, name);
    if (!HEAD) {
        HEAD = newNode;
        TAIL = newNode;
        newNode->PREV = HEAD;
        newNode->NEXT = HEAD;
    } else {
        newNode->PREV = TAIL;
        newNode->NEXT = HEAD;
        HEAD->PREV = newNode;
        TAIL->NEXT = newNode;
        TAIL = newNode;
    }
    doMergeSort();
}

//=========================================================================================================--
// 2.                slett(id)                       //
//====================================================
void DobbeltLenketSirkulaerListe::slett(int id) {
    if (!HEAD) return;
    unsigned long size = finnLengde();
    std::shared_ptr<Node> temp = HEAD;

    for (int itr = 0; itr < size; ++itr) {
        if (temp->ID == id) {
            if (temp == HEAD) {
                HEAD = temp->NEXT;
                if (HEAD == temp) { // Only one element left
                    HEAD = nullptr;
                    TAIL = nullptr;
                    return;
                }
                TAIL->NEXT = HEAD;
                HEAD->PREV = TAIL;
            } else if (temp == TAIL) {
                TAIL = temp->PREV;
                TAIL->NEXT = HEAD;
                HEAD->PREV = TAIL;
            } else {
                temp->PREV->NEXT = temp->NEXT;
                temp->NEXT->PREV = temp->PREV;
            }
        }
        temp = temp->NEXT;
    }
    doMergeSort();
}

//=========================================================================================================--
// 3.                   slett(name)                  //
//====================================================
void DobbeltLenketSirkulaerListe::slett(std::string name) {
    if (!HEAD) return;
    unsigned long size = finnLengde();
    std::shared_ptr<Node> temp = HEAD;

    for (int itr = 0; itr < size; ++itr) {
        if (temp->NAME == name) {
            if (temp == HEAD) {
                HEAD = temp->NEXT;
                if (HEAD == temp) {
                    HEAD = nullptr;
                    TAIL = nullptr;
                    return;
                }
                TAIL->NEXT = HEAD;
                HEAD->PREV = TAIL;
            } else if (temp == TAIL) {
                TAIL = temp->PREV;
                TAIL->NEXT = HEAD;
                HEAD->PREV = TAIL;
            } else {
                temp->PREV->NEXT = temp->NEXT;
                temp->NEXT->PREV = temp->PREV;
            }
        }
        temp = temp->NEXT;
    }
    doMergeSort();
}

//=========================================================================================================--
// 4.      skrivUt()   "min implementasjon"          //
//====================================================
std::ostream& operator<<(std::ostream& ost, const DobbeltLenketSirkulaerListe& list) {
    if (!list.HEAD) {
        ost << "Your list is empty, add objects using:\n"
            << "'nameoflist'.leggTil('yourID', 'yourNAME')" << std::endl;
        printLines();
    } else {
        std::shared_ptr<Node> temp = list.HEAD;
        int count = 1;
        printLines();
        do {
            ost << "Number: " << count
                << " ID: " << temp->ID
                << " Name: " << temp->NAME << std::endl;
            count++;
            temp = temp->NEXT;
        } while (temp != list.HEAD);
        printLines();
    }
    return ost;
}

//=========================================================================================================--
//  5.                finnLengde();                 //
//===================================================
unsigned long DobbeltLenketSirkulaerListe::finnLengde() {
    if (!HEAD) return 0;
    std::shared_ptr<Node> temp = HEAD;
    unsigned long size = 0;
    do {
        ++size;
        temp = temp->NEXT;
    } while (temp != HEAD);
    return size;
}

//=========================================================================================================--
// ┌──────────────────────────
// ▼ Funksjoner For Merge Sort


std::vector<std::shared_ptr<Node>> DobbeltLenketSirkulaerListe::lagVektor() {
    std::vector<std::shared_ptr<Node>> vector;
    std::shared_ptr<Node> temp = HEAD;
    do {
        vector.push_back(temp);
        temp = temp->NEXT;
    } while (temp != HEAD);
    return vector;
}

// 1. MergeSort
std::vector<std::shared_ptr<Node>> DobbeltLenketSirkulaerListe::mergeSort(std::vector<std::shared_ptr<Node>>& list) {
    if (list.size() <= 1) return list;
    unsigned long halfway = list.size() / 2;
    std::vector<std::shared_ptr<Node>> left(list.begin(), list.begin() + halfway);
    std::vector<std::shared_ptr<Node>> right(list.begin() + halfway, list.end());
    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
}

// 8. Merge, funksjon for MergeSort
std::vector<std::shared_ptr<Node>> DobbeltLenketSirkulaerListe::merge(std::vector<std::shared_ptr<Node>>& left, std::vector<std::shared_ptr<Node>>& right) {
    std::vector<std::shared_ptr<Node>> sortedVec;
    unsigned long i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i]->ID < right[j]->ID) {
            sortedVec.push_back(left[i]);
            ++i;
        } else {
            sortedVec.push_back(right[j]);
            ++j;
        }
    }

    while (i < left.size()) {
        sortedVec.push_back(left[i++]);
    }

    while (j < right.size()) {
        sortedVec.push_back(right[j++]);
    }

    return sortedVec;
}

// 9. Innitialisering av merge sort
void DobbeltLenketSirkulaerListe::doMergeSort() {
    std::vector<std::shared_ptr<Node>> sortedNodes = lagVektor();
    sortedNodes = mergeSort(sortedNodes);
    oppdaterListe(sortedNodes);
}

// 10. Oppdaterer Pekerne Etter Sortering
void DobbeltLenketSirkulaerListe::oppdaterListe(const std::vector<std::shared_ptr<Node>>& sortedNodes) {
    if (sortedNodes.empty()) return;
    
    HEAD = sortedNodes[0];
    TAIL = sortedNodes.back();

    for (size_t i = 0; i < sortedNodes.size(); ++i) {
        std::shared_ptr<Node> current = sortedNodes[i];
        current->PREV = sortedNodes[(i + sortedNodes.size() - 1) % sortedNodes.size()];
        current->NEXT = sortedNodes[(i + 1) % sortedNodes.size()];
    }
}
//=========================================================================================================--
