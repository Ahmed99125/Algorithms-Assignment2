//
// Created by asus on 12/9/2024.
//

#include "SkipList.h"
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <stdexcept>
#define MAX_VAL std::numeric_limits<T>::max()
#define MIN_VAL std::numeric_limits<T>::min()
using namespace std;

template <typename T>
SkipList<T>::SkipList() {
    head = new Node(MIN_VAL);
    head->next = new Node(MAX_VAL);
    tail = head;
    maxHeight = 16;
    srand(time(nullptr));
}

template <typename T>
pair<bool, Node<T>*> SkipList<T>::search(T target) {
    Node<T>* cur = tail;
    while (cur->val < target){

        if (cur->next->val > target){   //go down if there's still levels
            if (cur->LevelDown == nullptr){
                return {false, cur};
            }
            cur = cur->LevelDown;
        }

        else if (cur->next->val < target){  // continue searching in the same level
            cur = cur->next;
        }

        else{
            return {true, cur->next};   //target found
        }
    }
}

template <typename T>
char SkipList<T>::flip(){
    if (static_cast<float>(rand()) / RAND_MAX < 0.5)
        return 'H';
    else
        return 'T';
}

template<typename T>
void SkipList<T>::createNewLevel(Node<T>* &curLevel, Node<T>* &newNode_atLevel_i, Node<T>* &previousLevelNode) {
    curLevel = new Node<T>(MIN_VAL, newNode_atLevel_i, nullptr, nullptr, tail);
    tail->LevelUp = curLevel;
    newNode_atLevel_i->next = new Node<T>(MAX_VAL, nullptr, newNode_atLevel_i, nullptr, nullptr);
    newNode_atLevel_i->LevelDown = previousLevelNode;
    previousLevelNode->LevelUp = newNode_atLevel_i;
    newNode_atLevel_i->prev = curLevel;
    tail = curLevel;
}

template <typename T>
Node<T>* SkipList<T>::insert(T value) {
    //inserting at level 0
    Node<T>* cur = search(value).second;
    Node<T>* temp = cur->LevelDown;
    while (cur->LevelDown != nullptr)
        cur = cur->LevelDown;

    Node<T>* newNode_atLevel0 = new Node<T>(value, cur->next, cur, nullptr, nullptr);
    cur->next->prev = newNode_atLevel0;
    cur->next = newNode_atLevel0;
    //newNodes stores the currentLevel node
    vector<Node<T>*> newNodes;
    newNodes.push_back(newNode_atLevel0);
    Node<T>* curLevel = head;
    int curHeight = 0;
    //coin flipping
    while (flip() == 'H' && curHeight < maxHeight){     //Level up
        curHeight++;
        curLevel = curLevel->LevelUp;
        Node<T>* newNode_atLevel_i = new Node(value);
        Node<T>* previousLevelNode = newNodes.back();

        if (curLevel == nullptr) {     //we reached tail, build a new level
            createNewLevel(curLevel, newNode_atLevel_i, previousLevelNode);
        }
        else{
            /**
             * cur is the node right before newly inserted node, we're trying to get to the node above it
             * so that we can set it's pointers properly with the newly inserted node at the level above
             * if it doesn't have a level up node, we go previous until we find a node that has
             */
            while (cur->LevelUp == nullptr){
                cur = cur->prev;
            }
            cur = cur->LevelUp;
            newNode_atLevel_i->next = cur->next;
            newNode_atLevel_i->prev = cur;
            newNode_atLevel_i->LevelDown = previousLevelNode;
            previousLevelNode->LevelUp = newNode_atLevel_i;
            cur->next->prev = newNode_atLevel_i;
            cur->next = newNode_atLevel_i;
        }
//
//        curLevel = curLevel->LevelUp;
//        head = head->LevelUp;
//        cur = cur->LevelUp;
//        Node* NodeAtPreviousLevel = newNodes.back();
//        Node* newNode_atLevel_i = new Node(value, cur->next, cur, nullptr, NodeAtPreviousLevel);
//        NodeAtPreviousLevel->LevelUp = newNode_atLevel_i;
//        cur->next = newNode_atLevel_i;
        newNodes.push_back(newNode_atLevel_i);

    }
    return newNode_atLevel0;    //used for game class
}

template <typename T>
void SkipList<T>::display() {
    Node<T>* level = tail;
    Node<T>* node;
    int i = 0;
    cout << "Notice that counting of levels is from above, meaning that 0th level will be the highest level in this display\n";
    while (level != nullptr){
        node = level->next;
        cout << "Level " << i << ":-\n";
        while (node->val != MAX_VAL and node->val != MIN_VAL){
            cout << node->val << " -> ";
            node = node->next;
        }
        cout << endl;
        level = level->LevelDown;
        i++;
    }
    cout << "---------------------------------\n";
}

template <typename T>
void SkipList<T>::Delete(T target){
    pair<bool, Node<T>*> cur = search(target);
    if (!cur.first){
        throw runtime_error("Value not found");
    }

    while (cur.second != nullptr){
        Node<T>* temp = cur.second;
        Node<T>* prev = temp->prev;
        Node<T>* next = temp->next;
        prev->next = next;
        next->prev = prev;
        cur.second = cur.second->LevelDown;
        delete temp;
    }

//    while (!nodesToBeDeleted.empty()){
//        Node<T>* node = nodesToBeDeleted.front();
//        Node<T>* prev = node->prev;
//        Node<T>* next = node->next;
//        prev->next = next;
//        next->prev = prev;
//        nodesToBeDeleted.pop();
//        delete node;
//    }
}

template <typename T>
void SkipList<T>::Delete(Node<T>* target) {
    while (target != nullptr){
        Node<T>* temp = target;
        Node<T>* prev = temp->prev;
        Node<T>* next = temp->next;
        prev->next = next;
        next->prev = prev;
        target = target->LevelDown;
        delete temp;
    }
}

template class SkipList<int>;