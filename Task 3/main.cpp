//
// Created by at991 on 10/27/2024.
//
#include <iostream>
#include "Heap.h"

using namespace std;

int main() {
    int arr[5] = {4, 2, 1, 3, 5};
    Heap<int>h(5, 0, arr);
    int *arr1 = h.heapsortAsc();
    for (int i = 0; i < 5; i++)
        cout << arr1[i] << ' ';
    cout << endl;
    int *arr2 = h.heapsortDes();
    for (int i = 0; i < 5; i++)
        cout << arr2[i] << ' ';
    cout << endl;
}