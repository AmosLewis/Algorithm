/*
109. Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

Example
Given the following triangle:

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Notice
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.

自底部向上更新，倒数第一行不变，循环从倒数第二行开始
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
