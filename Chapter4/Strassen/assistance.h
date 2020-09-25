//
// Created by liyang on 2020/9/24.
//

/*
 * 该文件声明了为了方便实现Strassen算法而定义的一些辅助函数和一个辅助类
 */

#ifndef CHAPTER4_MATRIX_H
#define CHAPTER4_MATRIX_H

#include <vector>
#include <cmath>
using namespace std;

// 约定以Matrix声明的二维数组具有矩阵的形式，在传入Matrix类型的参数的时候需要保证这一点
// 即对于二维数组v有：
// 1. v不为空
// 2. v的所有元素的size相等且不为0
using Matrix = vector<vector<int>>;

// 该类表示一个方阵，该方阵是value表示的方阵或value的子方阵
struct SquareMatrix {
    // 该矩阵会在调用构造函数时被补零成为n*n方阵，其中n是2的幂
    Matrix &value;
    // 通过以下四个变量限定方阵的范围
    // _begin指向第一个，_end指向最后一个的下一个
    int i_begin, i_end;
    int j_begin, j_end;

    // 调用该构造函数时，会首先把v转换为n*n方阵，其中n是2的幂
    explicit SquareMatrix(Matrix &v);

    // 生成m的四分之一方阵
    // 根据pattern来确定_begin, _end字段，从而确定方阵是哪个四分之一
    SquareMatrix(SquareMatrix &m, int pattern);
};

// 通过补零把矩阵v转换为最小方阵
void convertToSquareMatrix(Matrix &v);
// 通过补零把矩阵v转换为最小n*n方阵，其中n是2的幂
void resizeToPowerOfTwo(Matrix &v);
// 把二维数组v清空，并使之成为全零的n*n方阵
void clearAndResize(vector<vector<int>> &v, int n);

// 方阵a, b相加，结果存到c中
void matrixAdd(SquareMatrix &a, SquareMatrix &b, SquareMatrix &c);
// 方阵a, b相减，结果存到c中
void matrixSub(SquareMatrix &a, SquareMatrix &b, SquareMatrix &c);

#endif //CHAPTER4_MATRIX_H
