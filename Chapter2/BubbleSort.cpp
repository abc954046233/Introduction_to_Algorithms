//
// Created by liyang on 2020/9/20.
//

#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int> &a) {
    // flag用来标记每一趟是否进行过交换操作
    // 若一趟没有进行交换则已经有序
    int flag = 1;
    int i = 0;      // 指向未排序部分第一个元素
    int j;
    int n = a.size();
    while (flag) {
        flag = 0;
        for (j = n - 1; j >= i + 1; --j) {
            if (a[j] < a[j - 1]) {
                int t = a[j];
                a[j] = a[j - 1];
                a[j - 1] = t;
            }
            flag = 1;
        }
        ++i;
    }
}

int main() {
    vector<int> a = {5, 2, 8, 7, 9, 4, 10};
    bubbleSort(a);
    for (int i : a) {
        cout << i << ' ';
    }
}