//
// Created by liyang on 2020/10/20.
//
#include <iostream>
#include <vector>
using namespace std;

/*
 * 在数组上的堆排序中，heap-sort变量是必须的
 * 这里把heap-sort存储于要排序数组A的末尾后一位置
 */

inline int parent(int i) {
    return i / 2;
}

inline int left(int i) {
    return 2 * i + 1;
}

inline int right(int i) {
    return 2 * i + 2;
}

void maxHeapify(vector<int> &A, int i) {
    int l = left(i);
    int r = right(i);

    int heapSize = A.back();
    int largest = i;
    if (l < heapSize && A[l] > A[i]) {
        largest = l;
    }
    if (r < heapSize && A[r] > A[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(A[i], A[largest]);
        maxHeapify(A, largest);
    }
}

void buildMaxHeap(vector<int> &A) {
    // A后添加一位存heap-size
    A.push_back(A.size());
    for (int i = (A.size() - 2) / 2; i >= 0; --i) {
        maxHeapify(A, i);
    }
}

void heapSort(vector<int> &A) {
    buildMaxHeap(A);

    for (int i = A.size() - 2; i >= 1; --i) {
        swap(A[0], A[i]);
        --A.back();     // heap-size--;
        maxHeapify(A, 0);
    }
    A.pop_back();
}

int main() {
    vector<int> A = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heapSort(A);
    for (auto a : A) {
        cout << a << '\n';
    }
}