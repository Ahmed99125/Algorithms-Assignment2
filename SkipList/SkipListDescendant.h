//
// Created by asus on 12/11/2024.
//

#ifndef SKIPLIST_SKIPLISTDESCENDANT_H
#define SKIPLIST_SKIPLISTDESCENDANT_H
#include "SkipList.h"
#include <iostream>
using namespace std;

template <typename T>
class SkipListDescendant : public SkipList<T>{
protected:
    void createNewLevel(Node<T>* &curLevel, Node<T>* &newNode_atLevel_i, Node<T>* &previousLevelNode);
public:
    SkipListDescendant();
    ~SkipListDescendant() = default;
    pair<bool, Node<T>*> search(T target);
};


#endif //SKIPLIST_SKIPLISTDESCENDANT_H
