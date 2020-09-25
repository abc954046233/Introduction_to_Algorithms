//
// Created by liyang on 2020/9/24.
//

#include "assistance.h"

SquareMatrix::SquareMatrix(Matrix &v): value(v) {
    resizeToPowerOfTwo(v);
    i_begin = 0;
    i_end = v.size();
    j_begin = 0;
    j_end = i_end;
}

SquareMatrix::SquareMatrix(SquareMatrix &m, int pattern): value(m.value) {
    int n = m.i_end - m.i_begin;
    switch (pattern) {
        case 11:
            i_begin = m.i_begin;
            i_end = i_begin + n / 2;
            j_begin = m.j_begin;
            j_end = j_begin + n / 2;
            break;
        case 12:
            i_begin = m.i_begin;
            i_end = i_begin + n / 2;
            j_begin = m.j_begin + n / 2;
            j_end = m.j_end;
            break;
        case 21:
            i_begin = m.i_begin + n / 2;
            i_end = m.i_end;
            j_begin = m.j_begin;
            j_end = j_begin + n / 2;
            break;
        case 22:
            i_begin = m.i_begin + n / 2;
            i_end = m.i_end;
            j_begin = m.j_begin + n / 2;
            j_end = m.j_end;
            break;
    }
}

void resizeToPowerOfTwo(Matrix &v) {
    convertToSquareMatrix(v);

    int n = v.size();

    // n已是2的幂则返回
    // 判断原理：
    // n为2的幂，当且仅当n的二进制表示一定具有"10*"的形式（"10*"为正则表达式）
    // 当且仅当n的二进制数为"10*"的形式时有(n & n - 1) == 0
    // 因为只有具有"01*"形式的二进制数加1才会使得所有位数反转，从而(n & n - 1) == 0
    if ((n & n - 1) == 0)
        return;

    // log2(n) + 1获得原来n的二进制位数，1左移这个位数后得到比n大的最小的2的幂
    int new_n = 1 << static_cast<int>(log2(n) + 1);
    v.resize(new_n);
    for (int i = 0; i < n; ++i) {
        v[i].resize(new_n);
    }
    for (int i = n; i < new_n; ++i) {
        v[i] = vector<int>(new_n);
    }
}

void convertToSquareMatrix(Matrix &v) {
    int m = v.size();
    int n = v[0].size();
    if (m == n)
        return;

    if (m > n) {
        // 补列
        for (int i = 0; i < m; ++i)
            v[i].resize(m);
        return;
    }

    if (m < n) {
        // 补行
        v.resize(n);
        for (int i = m; i < n; ++i) {
            v[i] = vector<int>(n);
        }
        return;
    }
}

void clearAndResize(vector<vector<int>> &v, int n) {
    v.clear();
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        v[i].resize(n);
    }
}

void matrixAdd(SquareMatrix &a, SquareMatrix &b, SquareMatrix &c) {
    int a_i = a.i_begin;
    int b_i = b.i_begin;
    int c_i, c_j;
    for (c_i = c.i_begin; c_i < c.i_end; ++c_i) {
        int a_j = a.j_begin;
        int b_j = b.j_begin;
        for (c_j = c.j_begin; c_j < c.j_end; ++c_j) {
            c.value[c_i][c_j] = a.value[a_i][a_j] + b.value[b_i][b_j];
            a_j++;
            b_j++;
        }
        a_i++;
        b_i++;
    }
}

void matrixSub(SquareMatrix &a, SquareMatrix &b, SquareMatrix &c) {
    int a_i = a.i_begin;
    int b_i = b.i_begin;
    int c_i, c_j;
    for (c_i = c.i_begin; c_i < c.i_end; ++c_i) {
        int a_j = a.j_begin;
        int b_j = b.j_begin;
        for (c_j = c.j_begin; c_j < c.j_end; ++c_j) {
            c.value[c_i][c_j] = a.value[a_i][a_j] - b.value[b_i][b_j];
            a_j++;
            b_j++;
        }
        a_i++;
        b_i++;
    }
}
