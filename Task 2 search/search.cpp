//
// Created by asus on 10/27/2024.
//
#include <iostream>
#include <vector>
using namespace std;

template <class T>
int sequentialSearch(vector<T>& arr, T target){
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

template <class T>
int recursiveSequential(vector<T>& arr, int idx, T target){
    if (idx == arr.size())
        return -1;

    if (arr[idx] == target)
        return idx;
    return recursiveSequential(arr, idx+1, target);
}

template <class T>
int binarySearch(vector<T>& arr, int l, int r, T target){
    int mid;
    while (l <= r){
        mid = (l+r)/2;
        if (arr[mid] == target)
            return mid;
        else if(arr[mid] > target)
            r = mid - 1;
        else
            l = mid + 1;
    }

    return -1;
}

template <class T>
int recursiveBinarySearch(vector<T>& arr, int l, int r, T target){
    if (l > r)
        return -1;

    int mid = (l+r)/2;
    if (arr[mid] == target)
        return mid;
    else if(arr[mid] > target)
        return recursiveBinarySearch(arr, l, mid - 1, target);
    else
        return recursiveBinarySearch(arr, mid + 1, r, target);
}


int main(){
    vector<int> arr = {1, 3, 4, 5, 8};
    int target = 7;
    cout << sequentialSearch(arr, target) << '\n';
    cout << recursiveSequential(arr, 0, target) << '\n';
    cout << binarySearch(arr, 0, arr.size()-1, target) << '\n';
    cout << recursiveBinarySearch(arr, 0, arr.size()-1, target) << '\n';
}
