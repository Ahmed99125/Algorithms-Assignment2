//
// Created by at991 on 10/27/2024.
//

#include <algorithm>

#ifndef TASK_3_HEAP_H
#define TASK_3_HEAP_H

template <class T>
class Heap {
protected:
    T *array;
    int capacity;
    int count;
    int heapType;

    void resizeHeap();
    void heapifyDown(int index, int n);
    void heapifyDownMax(int index, int n);
    void heapifyDownMin(int index, int n);
    void heapifyUp(int index);
    void heapifyUpMax(int index);
    void heapifyUpMin(int index);
    void buildHeap(int n);

public:
    Heap(int capacity, int type);
    Heap(int n, int type, T *arr);
    void insert(T val);
    void remove();
    T getMax();
    T getMin();
    int size();
};

template <class T>
Heap<T>::Heap(int capacity, int type)
    : capacity{capacity}, count{0}, heapType{type} {
    if (this->capacity <= 0) this->capacity = 1;
    array = new T[this->capacity];
}

template <class T>
Heap<T>::Heap(int n, int type, T *arr)
    : Heap(1, type) {
    count = n;
    while (n > capacity)
        this->resizeHeap();
    for (int i = 0; i < n; i++)
        array[i] = arr[i];
    buildHeap(n);
}

template <class T>
void Heap<T>::resizeHeap() {
    T *oldArr = array;
    capacity *= 2;
    array = new T[capacity];
    for (int i = 0; i < count; i++)
        array[i] = oldArr[i];
}

template <class T>
void Heap<T>::buildHeap(int n) {
    for (int i = (n - 1) / 2; i >= 0; i--)
        heapifyDown(i, n);
}

template <class T>
void Heap<T>::heapifyDown(int index, int n) {
    heapType ? heapifyDownMax(index, n) : heapifyDownMin(index, n);
}

template <class T>
void Heap<T>::heapifyDownMax(int index, int n) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int maxi = index;
    if (left <= n && array[left] > array[maxi])
        maxi = left;
    if (right <= n && array[right] > array[maxi])
        maxi = right;
    if (maxi != index) {
        std::swap(array[index], array[maxi]);
        heapifyDownMax(maxi, n);
    }
}

template <class T>
void Heap<T>::heapifyDownMin(int index, int n) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int maxi = index;
    if (left <= n && array[left] < array[maxi])
        maxi = left;
    if (right <= n && array[right] < array[maxi])
        maxi = right;
    if (maxi != index) {
        std::swap(array[index], array[maxi]);
        heapifyDownMin(maxi, n);
    }
}

template <class T>
void Heap<T>::heapifyUp(int index) {
    heapType ? heapifyUpMax(index) : heapifyUpMin(index);
}

template <class T>
void Heap<T>::heapifyUpMax(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && array[index] > array[parent]) {
        std::swap(array[index], array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template <class T>
void Heap<T>::heapifyUpMin(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && array[index] < array[parent]) {
        std::swap(array[index], array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template <class T>
void Heap<T>::insert(T val) {
    if (count >= capacity)
        this->resizeHeap();

    array[count] = val;
    heapifyUp(count);
    count++;
}

template <class T>
void Heap<T>::remove() {
    count--;
    array[0] = array[count];
    heapifyDown(0, count);
}

template <class T>
T Heap<T>::getMax() {
    if (heapType)
        return array[0];

    T maxi = array[count-1];
    for (int i = (count - 1) / 2 + 1; i < count; i++)
        maxi = std::max(maxi, array[i]);
    return maxi;
}

template <class T>
T Heap<T>::getMin() {
    if (!heapType)
        return array[0];

    T mini = array[count-1];
    for (int i = (count - 1) / 2 + 1; i < count; i++)
        mini = std::min(mini, array[i]);
    return mini;
}

template <class T>
int Heap<T>::size() {
    return count;
}

#endif //TASK_3_HEAP_H