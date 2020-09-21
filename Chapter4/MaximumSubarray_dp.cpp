//
// Created by liyang on 2020/9/21.
//

#include <iostream>
#include <vector>
using namespace std;

// 调用函数前需确保!a.empty()
int findMaximumSubarray_dp(vector<int> a) {
    // res保存了目前为止最大的连续子数组之和
    int res;
    // dp[i]表示以i结尾的连续子数组中最大的那一个的和
    int dp[a.size()];

    dp[0] = a[0];
    res = dp[0];

    for (int i = 1; i < a.size(); ++i) {
        // 若dp[i-1]是负数，则加上它只会使dp[i]减小
        // 所以dp[i]一定是a[i]更大(相比于dp[i-1] + a[i])
        if (dp[i - 1] < 0)
            dp[i] = a[i];
        // 若dp[i-1]是正数，则加上它会使dp[i]变大
        // 所以dp[i-1] + a[i]更大(相比于a[i])
        else
            dp[i] = dp[i - 1] + a[i];
        // 更新res
        res = max(res, dp[i]);
    }
    return res;
}

int main() {
    vector<int> a = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    cout << findMaximumSubarray_dp(a) << endl;
}

// p.s. 如果允许改变a，则该题可以省去dp的内存空间，之间利用a原址生成dp数组