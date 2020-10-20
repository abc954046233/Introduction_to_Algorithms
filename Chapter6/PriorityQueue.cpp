//
// Created by liyang on 2020/10/20.
//
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

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

int heapMaximum(vector<int> &A) {
    if (A.back() < 1) {
        cerr << "heap underflow\n";
        abort();
    }
    return A.front();
}

int heapExtractMax(vector<int> &A) {
    if (A.back() < 1) {
        cerr << "heap underflow\n";
        abort();
    }
    int max = A.front();
    A.front() = A[A.back() - 1];
    --A.back();
    maxHeapify(A, 0);
    return max;
}

void heapIncreaseKey(vector<int> &A, int i, int key) {
    if (key < A[i]) {
        cerr << "new key is smaller than current key\n";
        return;
    }

    A[i] = key;
    while (i > 0 && A[parent(i)] < A[i]) {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

void maxHeapInsert(vector<int> &A, int key) {
    ++A.back();
    A[A.back() - 1] = INT_MIN;
    heapIncreaseKey(A, A.back() - 1, key);
}

int main() {
    vector<int> A = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    buildMaxHeap(A);
    cout << heapMaximum(A) << "\n";
    cout << heapExtractMax(A) << "\n";
    heapIncreaseKey(A, 3, 100);
    maxHeapInsert(A, 30);
}