//
// Created by at991 on 10/27/2024.
//

#include "Heap.h"

#ifndef TASK_3_HEAPSORT_H
#define TASK_3_HEAPSORT_H

template <class T>
class HeapSort : public Heap<T> {
private:
    void buildHeapMax();
    void buildHeapMin();
public:
    HeapSort(int n, T *arr);
    T * asc();
    T * des();
};

template <class T>
HeapSort<T>::HeapSort(int n, T *arr)
    : Heap<T>(n, 0, arr) {
}

template <class T>
void HeapSort<T>::buildHeapMax() {
    for (int i = (Heap<T>::count - 1) / 2; i >= 0; i--)
        heapifyDownMax(i, Heap<T>::count);
}

template <class T>
void HeapSort<T>::buildHeapMin() {
    for (int i = (Heap<T>::count - 1) / 2; i >= 0; i--)
        heapifyDownMin(i, Heap<T>::count);
}

template <class T>
T * HeapSort<T>::asc() {
    buildHeapMax();
    for (int i = 0; i < Heap<T>::count; i++)
        std::cout << Heap<T>::array[i] << ' ';
    std::cout << std::endl;
    for (int i = Heap<T>::count - 1; i > 0 ; i--) {
        std::swap(Heap<T>::array[0], Heap<T>::array[i]);
        Heap<T>::heapifyDownMax(0, i);
    }

    return Heap<T>::array;
}

template <class T>
T * HeapSort<T>::des() {
    buildHeapMin();
    for (int i = Heap<T>::count - 1; i > 0 ; i--) {
        std::swap(Heap<T>::array[0], Heap<T>::array[i]);
        Heap<T>::heapifyDownMin(0, i);
    }
    return Heap<T>::array;
}

#endif //TASK_3_HEAPSORT_H
