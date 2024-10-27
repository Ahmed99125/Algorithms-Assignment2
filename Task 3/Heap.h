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
    bool (*compare)(T a, T b);
    static bool defaultComp(T a, T b) {
        return a < b;
    }

public:
    Heap(int capacity, int type, bool (*func)(T a, T b) = defaultComp);
    Heap(int n, int type, T *arr, bool (*func)(T a, T b) = defaultComp);
    void insert(T val);
    void remove();
    T getMax();
    T getMin();
    int size();

    T *heapsortAsc();
    T *heapsortDes();
};

template <class T>
T *Heap<T>::heapsortAsc() {
    // build heap max
    for (int i = (count - 1) / 2; i >= 0; i--)
        heapifyDownMax(i, count);
    for (int i = count - 1; i > 0; i--) {
        std::swap(array[0], array[i]);

        heapifyDownMax(0, i);
    }
    T *sortedArray = new T[count];
    for (int i = 0; i < count; i++)
        sortedArray[i] = array[i];
    buildHeap(count);
    return sortedArray;
}

template <class T>
T *Heap<T>::heapsortDes() {
    // build heap max
    for (int i = (count - 1) / 2; i >= 0; i--)
        heapifyDownMin(i, count);
    for (int i = count - 1; i > 0; i--) {
        std::swap(array[0], array[i]);

        heapifyDownMin(0, i);
    }
    T *sortedArray = new T[count];
    for (int i = 0; i < count; i++)
        sortedArray[i] = array[i];
    buildHeap(count);
    return sortedArray;
}

template <class T>
Heap<T>::Heap(int capacity, int type, bool (*func)(T a, T b))
    : capacity{capacity}, count{0}, heapType{type} {
    if (this->capacity <= 0) this->capacity = 1;
    array = new T[this->capacity];
    this->compare = func;
}

template <class T>
Heap<T>::Heap(int n, int type, T *arr, bool (*func)(T a, T b))
    : Heap(1, type, func) {
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
    if (left < n && compare(array[maxi], array[left]))
        maxi = left;
    if (right < n && compare(array[maxi], array[right]))
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
    if (left < n && compare(array[left], array[maxi]))
        maxi = left;
    if (right < n && compare(array[right], array[maxi]))
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
    while (index > 0 && compare(array[parent] > array[index])) {
        std::swap(array[index], array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template <class T>
void Heap<T>::heapifyUpMin(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && compare(array[index], array[parent])) {
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