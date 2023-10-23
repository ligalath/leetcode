// 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

 

// 示例 1：
// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0
// 输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// 输出：4

// 示例 2：
// 0 1
// 1 0
// 输入：matrix = [["0","1"],["1","0"]]
// 输出：1

// 示例 3：
// 0
// 输入：matrix = [["0"]]
// 输出：0

// 提示：
// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 300
// matrix[i][j] 为 '0' 或 '1'
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        if(0 == rows || 0 == cols)
            return 0;
        vector<vector<int>> dp;
        for(int i = 0; i < rows;++i)
        {
            vector<int> row(cols, 0);
            dp.emplace_back(row);
        }
        int max_dp = 0;
        for(int i = rows - 1; i > -1; --i)
        {
            for(int j = cols -1; j > -1; --j)
            {
                if('0' == matrix[i][j])
                    dp[i][j] = 0;
                else if(rows - 1 == i || cols -1 == j)
                    dp[i][j] = ('1' == matrix[i][j]?1:0);
                else
                    dp[i][j] = min(dp[i+1][j], min(dp[i+1][j+1], dp[i][j+1])) + 1;
                max_dp = max_dp > dp[i][j]?max_dp:dp[i][j];
            }
        }
        return max_dp*max_dp;
    }
};