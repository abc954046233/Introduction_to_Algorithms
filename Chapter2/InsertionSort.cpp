//
// Created by liyang on 2020/9/20.
//
#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int> &a) {
    int key;
    // 0..0已排序，从[1..a.size()-1]选第一个元素插入已排序区间
    for (int i = 1; i < a.size(); ++i) {
        key = a[i];     // 要插入元素
        // 把a[i]插入已排序区间a[0..i-1]
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        // 此时要么 j == -1 要么 a[j] <= key
        // 而[j+1..i-1]的元素全部向后挪了一位
        a[j + 1] = key;
    }
}

int main() {
    vector<int> a = {5, 2, 8, 7, 9, 4, 10};
    insertionSort(a);
    for (int i : a) {
        cout << i << ' ';
    }
}