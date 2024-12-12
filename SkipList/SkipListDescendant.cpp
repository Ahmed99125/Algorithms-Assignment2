//
// Created by asus on 12/11/2024.
//

#include "SkipListDescendant.h"
#include <iostream>
#include <limits>
#include "SkipListDescendant.h"
#define MAX_VAL std::numeric_limits<T>::max()
#define MIN_VAL std::numeric_limits<T>::min()
using namespace std;

template <typename T>
SkipListDescendant<T>::SkipListDescendant() : SkipList<T>(){
    this->head = new Node(MAX_VAL);
    this->head->next = new Node(MIN_VAL);
    this->tail = this->head;
    srand(time(nullptr));
}

template <typename T>
pair<bool, Node<T> *> SkipListDescendant<T>::search(T target) {
    Node<T>* cur = this->tail;
    while (cur->val > target){
        if (cur->next->val < target){   //go down if there's still levels
            if (cur->LevelDown == nullptr){
                return {false, cur};
            }
            cur = cur->LevelDown;
        }

        else if (cur->next->val > target){  // continue searching in the same level
            cur = cur->next;
        }

        else{
            return {true, cur->next};   //target found
        }
    }
}

template<typename T>
void SkipListDescendant<T>::createNewLevel(Node<T>* &curLevel, Node<T>* &newNode_atLevel_i, Node<T>* &previousLevelNode) {
    curLevel = new Node<T>(MAX_VAL, newNode_atLevel_i, nullptr, nullptr, this->tail);
    this->tail->LevelUp = curLevel;
    newNode_atLevel_i->next = new Node<T>(MIN_VAL, nullptr, newNode_atLevel_i, nullptr, nullptr);
    newNode_atLevel_i->LevelDown = previousLevelNode;
    previousLevelNode->LevelUp = newNode_atLevel_i;
    newNode_atLevel_i->prev = curLevel;
    this->tail = curLevel;
}

template class SkipListDescendant<int>;
