// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

// 此外，你可以假设该网格的四条边均被水包围。

 

// 示例 1：

// 输入：grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// 输出：1
// 示例 2：

// 输入：grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// 输出：3
 

// 提示：

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 300
// grid[i][j] 的值为 '0' 或 '1'
#include <queue>
using namespace std;
class Solution
{
public:
    typedef struct pos
    {
        int row;
        int col;
    } pos_t;
    int numIslands(vector<vector<char>> &grid)
    {
        const unsigned int rows = grid.size();

        if (0 == rows)
            return 0;
        const unsigned int cols = grid[0].size();
        if (0 == cols)
            return 0;
        int label[300][300] = {0};
        // int label[rows][cols] = {0};
        int max_label = 0;
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                if (grid[row][col] != '0' && 0 == label[row][col])
                {
                    max_label++;
                    // execute scope-first search
                    queue<pos_t> pos_queue;
                    pos_queue.push({row, col});
                    while (!pos_queue.empty())
                    {
                        auto pos = pos_queue.front();
                        pos_queue.pop();
                        label[pos.row][pos.col] = max_label;
                        if (pos.row > 0 && grid[pos.row - 1][pos.col] != '0' && 0 == label[pos.row - 1][pos.col])
                        {
                            pos_queue.push({pos.row - 1, pos.col});
                            label[pos.row - 1][pos.col] = max_label;
                        }
                        if (pos.row < rows - 1 && grid[pos.row + 1][pos.col] != '0' && 0 == label[pos.row + 1][pos.col])
                        {
                            pos_queue.push({pos.row + 1, pos.col});
                            label[pos.row + 1][pos.col] = max_label;
                        }
                        if (pos.col > 0 && grid[pos.row][pos.col - 1] != '0' && 0 == label[pos.row][pos.col - 1])
                        {
                            pos_queue.push({pos.row, pos.col - 1});
                            label[pos.row][pos.col - 1] = max_label;
                        }
                        if (pos.col < cols - 1 && grid[pos.row][pos.col + 1] != '0' && 0 == label[pos.row][pos.col + 1])
                        {
                            pos_queue.push({pos.row, pos.col + 1});
                            label[pos.row][pos.col + 1] = max_label;
                        }
                    }
                }
                else
                    continue;
            }
        }
        return max_label;
    }
};