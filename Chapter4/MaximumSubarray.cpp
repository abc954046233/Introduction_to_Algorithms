//
// Created by liyang on 2020/9/20.
//

#include <iostream>
#include <vector>
using namespace std;

const int NEGATIVE_INF = -2000000000;

// 约定v[0]存子数组的左端，v[1]存右端，v[2]存子数组的和
vector<int> findMaxCrossingSubarray(vector<int> &a, int low, int mid, int high) {
    // a[i..mid]的sum中的最大值
    int left_sum = NEGATIVE_INF;
    // 使a[i..mid]的sum最大的i
    int max_left;
    int sum = 0;
    for (int i = mid; i >= low; --i) {
        sum += a[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    int right_sum = NEGATIVE_INF;
    int max_right;
    sum = 0;
    for (int j = mid + 1; j <= high; ++j) {
        sum += a[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }

    vector<int> v;
    v.push_back(max_left);
    v.push_back(max_right);
    v.push_back(left_sum + right_sum);
    return v;
}

// 约定v[0]存子数组的左端，v[1]存右端，v[2]存子数组的和
vector<int> findMaximumSubarray(vector<int> &a, int low, int high) {
    if (high == low) {
        vector<int> v0;
        v0.push_back(low);
        v0.push_back(high);
        v0.push_back(a[low]);
        return v0;
    } else {
        int mid = (low + high) / 2;
        vector<int> v1 = findMaximumSubarray(a, low, mid);
        vector<int> v2 = findMaximumSubarray(a, mid + 1, high);
        vector<int> v3 = findMaxCrossingSubarray(a, low, mid, high);

        if (v1[2] >= v2[2] && v1[2] >= v3[2])
            return v1;
        else if (v2[2] >= v1[2] && v2[2] >= v3[2])
            return v2;
        else
            return v3;
    }
}

int main() {
    vector<int> a = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    vector<int> v = findMaximumSubarray(a, 0, 15);
    cout << v[0] << ' ' << v[1] << ' ' << v[2] << endl;
}