//
// Created by at991 on 10/27/2024.
//
#include <iostream>
#include "Heap.h"
#include "HeapSort.h"

using namespace std;

int main() {
    int arr[5] = {6,5,3,8,1};
    HeapSort<int>hs(5, arr);
    int *asc = hs.asc();
    int *des = hs.des();
    for (int i = 0; i < 5; i++)
        cout << asc[i] << ' ';
    cout << endl;
    for (int i = 0; i < 5; i++)
        cout << des[i] << ' ';
}