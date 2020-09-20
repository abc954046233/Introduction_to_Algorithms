//
// Created by liyang on 2020/9/20.
//

#include <iostream>
#include <vector>
using namespace std;

const int INF = 2000000000;

// 该函数利用堆底的哨兵牌省去了对堆是否为空的判断，将处理统一
// 注意排序区间为a[p..r]闭区间，而非传统的左闭右开
void merge(vector<int> &a, int p, int q, int r) {
    int n1 = q - p + 1;         // a[p..q]长度
    int n2 = r - q;             // a[q+1..r]长度

    vector<int> L(n1 + 1);   // 多一位放哨兵牌
    vector<int> R(n2 + 1);

    int i, j;
    // a[p..q]->L[0..n1-1]
    for (i = 0; i < n1; ++i) {
        L[i] = a[p + i];
    }
    // a[q+1..r]->L[0..n2-1]
    for (j = 0; j < n2; ++j) {
        R[j] = a[q + 1 + j];
    }
    L[n1] = INF;
    R[n2] = INF;

    // i, j为堆顶位置
    i = 0;
    j = 0;
    int k;
    for (k = p; k <= r; ++k) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            ++i;
        } else {
            a[k] = R[j];
            ++j;
        }
    }
}

void mergeSort(vector<int> &a, int p, int r) {
    // p >= r时无需排序
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(a, p, q);
        mergeSort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

int main() {
    vector<int> a = {5, 2, 8, 7, 9, 4, 10};
    mergeSort(a, 0, a.size() - 1);
    for (int i : a) {
        cout << i << ' ';
    }
}