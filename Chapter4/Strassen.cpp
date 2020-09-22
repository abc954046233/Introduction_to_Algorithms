//
// Created by liyang on 2020/9/22.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 实际上Matrix的实际含义并不是一个矩阵
// 这里为了可读性如此设置
// 假定输入到函数squareMatrixMultiply中的矩阵都为 n * n 方阵
// 其中n >= 1
using Matrix = vector<vector<int>>;

Matrix squareMatrixMultiply(Matrix a, Matrix b) {
    Matrix c;

    int n = a.size();
    // 基本情况，即1*1矩阵相乘
    if (n == 1) {
        vector<int> v;
        v.push_back(a[0][0] * b[0][0]);
        c.push_back(v);
        return c;
    }

    // Strassen算法假定n为2的幂
    // 故若n不是2的幂，则补零使n成为2的幂
    if ((n & n - 1) == 0) {
        // 判断是否为2的幂的原理：
        // 一个数为2的幂，当且仅当它的二进制表示是10*的形式。(10*为正则表达式)
        // 一个二进制数是10*的形式当且仅当(n & n -1) == 0
        // 因为只有具有01*形式的二进制位加1会使得所有位全部反转

        // newN为大于n且为2的幂的数里最小的那一个
        int newN = 1 << static_cast<int>(log2(n) + 1);
    }

}

int main() {

}