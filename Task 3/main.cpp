//
// Created by at991 on 10/27/2024.
//
#include <iostream>
#include "Heap.h"
#include "PriorityQueue.h"
#include <string>

using namespace std;

int main() {
    PriorityQueue<string> pq{};
    pq.push("ahmed", 100);
    pq.push("nour", 200);
    pq.push("mohamed", 1);
    while (pq.size()) {
        cout << pq.top() << endl;
        pq.pop();
    }
}