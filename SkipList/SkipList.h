//
// Created by asus on 12/9/2024.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H
#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T val;
    Node* next, *prev, *LevelUp, *LevelDown, *relationBetweenScoreAndID;
    Node(T v = T(), Node* n = nullptr, Node* p = nullptr, Node* up = nullptr, Node*D = nullptr){
        val = v;
        next = n;
        prev = p;
        LevelUp = up;
        LevelDown = D;
    }

    Node(T v, Node* n, Node* p, Node* up, Node*D, Node* s){
        val = v;
        next = n;
        prev = p;
        LevelUp = up;
        LevelDown = D;
        relationBetweenScoreAndID = s;  //for game class
    }
};

template <typename T>
class SkipList {
protected:
    Node<T>* head, *tail;
    char flip();
    virtual void createNewLevel(Node<T>* &curLevel, Node<T>* &newNode_atLevel_i, Node<T>* &previousLevelNode);
    int maxHeight;

public:
    SkipList();
    ~SkipList() = default;
    Node<T>* insert(T value);
    void Delete(T target);
    void Delete(Node<T>* target);
    virtual pair<bool, Node<T>*> search(T target);
    void display();
    Node<T>* getHead(){ return this->head; };
    Node<T>* getTail(){ return this->tail; };
};


#endif //SKIPLIST_SKIPLIST_H
