//
// Created by at991 on 10/27/2024.
//

#include "Heap.h"

#ifndef TASK_3_PRIORITYQUEUE_H
#define TASK_3_PRIORITYQUEUE_H

template <class T>
class PriorityQueue : public Heap<std::pair<T, int>> {
private:
    static bool defaultComp(std::pair <T, int> a, std::pair <T, int> b) {
        return a.second < b.second;
    }
public:
    PriorityQueue();
    void push(T val, int priority);
    T top();
    void pop();
};

template <class T>
PriorityQueue<T>::PriorityQueue()
    : Heap<std::pair <T, int>>(1, 1, defaultComp) {

}

template <class T>
T PriorityQueue<T>::top() {
    return this->getMax().first;
}

template <class T>
void PriorityQueue<T>::push(T val, int priority) {
    std::pair<T, int> el = {val, priority};
    this->insert(el);
}

template <class T>
void PriorityQueue<T>::pop() {
    this->remove();
}

#endif //TASK_3_PRIORITYQUEUE_H
