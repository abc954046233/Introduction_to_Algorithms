//
// Created by liyang on 2020/9/24.
//

#include <iostream>
#include "assistance.cpp"
using namespace std;

void Strassen(SquareMatrix &a, SquareMatrix &b, SquareMatrix &c);

// 该函数会改变矩阵a, b和二维数组c
// 具体的变化是：
// a, b, c会变为大小相等且大小为2的幂的三个方阵，不足的地方补零
// 去除这个副作用并不复杂，这里专注于算法本身，所以并没有实现
void matrixMultiply(Matrix &a, Matrix &b,
                    vector<vector<int>> &c) {
    // 单元素矩阵直接计算后返回
    if (a.size() == 1 && a[0].size() == 1) {
        c = {{a[0][0] * b[0][0]}};
        return;
    }

    // 把a, b, c封装为结构体
    SquareMatrix a_struct(a);
    SquareMatrix b_struct(b);
    clearAndResize(c, a.size());
    SquareMatrix c_struct(c);

    Strassen(a_struct, b_struct, c_struct);
}

// Strassen三个参数为结构体
// 因为书中Strassen算法采用了利用下标方阵阵进行划分的方法
// 所以递归函数的参数中必须以某种方式提供方阵的下标来确定方阵的范围
// 这里把方阵的范围封装到了结构体中
// 如果传入matrixMultiply中的两个矩阵a，b正确
// 即：a，b是矩阵，且a，b可以相乘
// 则Strassen中的a, b, c方阵总是具有相同的大小n
void Strassen(SquareMatrix &a, SquareMatrix &b, SquareMatrix &c) {
    // 递归出口，如果方阵大小为1，则计算后直接返回
    if (a.i_end - a.i_begin == 1) {
        c.value[c.i_begin][c.j_begin] =
                a.value[a.i_begin][a.j_begin] * b.value[b.i_begin][b.j_begin];
        return;
    }

    // 分割方阵为四个(n / 2) * (n / 2)的方阵
    SquareMatrix a11(a, 11);
    SquareMatrix a12(a, 12);
    SquareMatrix a21(a, 21);
    SquareMatrix a22(a, 22);
    SquareMatrix b11(b, 11);
    SquareMatrix b12(b, 12);
    SquareMatrix b21(b, 21);
    SquareMatrix b22(b, 22);
    SquareMatrix c11(c, 11);
    SquareMatrix c12(c, 12);
    SquareMatrix c21(c, 21);
    SquareMatrix c22(c, 22);

    int n = a11.i_end - a11.i_begin;
    // s, p中的元素为SquareMatrix要引用的二维数组
    vector<vector<vector<int>>> s(11);
    vector<vector<vector<int>>> p(8);
    // 在引用之前，先把每个二维数组转换为n*n的方阵
    for (int i = 1; i <= 10; ++i) {
        clearAndResize(s[i], n);
    }
    for (int i = 1; i <= 7; ++i) {
        clearAndResize(p[i], n);
    }

    SquareMatrix s1(s[1]);
    SquareMatrix s2(s[2]);
    SquareMatrix s3(s[3]);
    SquareMatrix s4(s[4]);
    SquareMatrix s5(s[5]);
    SquareMatrix s6(s[6]);
    SquareMatrix s7(s[7]);
    SquareMatrix s8(s[8]);
    SquareMatrix s9(s[9]);
    SquareMatrix s10(s[10]);

    SquareMatrix p1(p[1]);
    SquareMatrix p2(p[2]);
    SquareMatrix p3(p[3]);
    SquareMatrix p4(p[4]);
    SquareMatrix p5(p[5]);
    SquareMatrix p6(p[6]);
    SquareMatrix p7(p[7]);

    // 该函数以下全为书上的公式
    matrixSub(b12, b22, s1);
    matrixAdd(a11, a12, s2);
    matrixAdd(a21, a22, s3);
    matrixSub(b21, b11, s4);
    matrixAdd(a11, a22, s5);
    matrixAdd(b11, b22, s6);
    matrixSub(a12, a22, s7);
    matrixAdd(b21, b22, s8);
    matrixSub(a11, a21, s9);
    matrixAdd(b11, b12, s10);

    Strassen(a11, s1, p1);
    Strassen(s2, b22, p2);
    Strassen(s3, b11, p3);
    Strassen(a22, s4, p4);
    Strassen(s5, s6, p5);
    Strassen(s7, s8, p6);
    Strassen(s9, s10, p7);

    // c11
    matrixAdd(p5, p4, c11);
    matrixSub(c11, p2, c11);
    matrixAdd(c11, p6, c11);

    // c12
    matrixAdd(p1, p2, c12);

    // c21
    matrixAdd(p3, p4, c21);

    // c22
    matrixAdd(p5, p1, c22);
    matrixSub(c22, p3, c22);
    matrixSub(c22, p7, c22);
}

void show(vector<vector<int>> &m) {
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}

void show(SquareMatrix &m) {
    for (int i = m.i_begin; i < m.i_end; ++i) {
        for (int j = m.j_begin; j < m.j_end; ++j) {
            cout << m.value[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    Matrix a = {{1, 2, 3},
                {4, 5, 6}};
    Matrix b = {{3, 2},
                {1, 6},
                {5, 4}};
    vector<vector<int>> c;
    matrixMultiply(a, b, c);
    show(c);
}
