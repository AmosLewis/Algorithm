/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

从右下到左上，递推。
triangle原始值
source
[
[],
[],[],
[],[],[a]
[],[],[],[]
]

dp状态
[
[],
[],[],
[],[],[a], 从这一行开始推到 a = min(a1,a2) + source[a]
[],[],[a1],[a2]  //这一样用原来的值初始化就好了
]

为了节省空间，可以在源数组上操作，不用开辟新空间。
如果从左上右下递推，状态方程要分边界。
*/

class Solution {
public:
    /**
     * @param triangle: a list of lists of integers
     * @return: An integer, minimum path sum
     */
    int minimumTotal(vector<vector<int>> &triangle) {
        // write your code here
        for(int i = triangle.size() - 2; i >=0; i--)
        {
            for(int j = 0; j < i + 1; j++)
            {
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};
