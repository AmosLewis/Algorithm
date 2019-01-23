/*
174. Dungeon Game
Hard

560

12

Favorite

Share
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

 

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)	-3	3
-5	-10	1
10	30	-5 (P)
 

Note:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.


source
[-2] 	[-3]	[3]
[-5]	[-10]	[1]
[10]	[30]	[a]

dp
[]         []         []      [INT_MAX]
[]         []         []      [INT_MAX]
[]         []         [a]     [1 a2]
[INT_MAX]  [INT_MAX]  [1 a1]  [INT_MAX]

a = max(1, min(a1, a2)- source(a))

*/

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int row = dungeon.size(), col = dungeon[0].size();
        // 为了加最后一行一列为INT_MAX,直接把整个dp都初始化为INT_MAX，
        // 这样对于边界的比较，取最小值的时候，一定能取到原来边界的值
        vector<vector<int>> dp(row+1,vector<int>(col+1, INT_MAX)); 
        // 对于原来数组的最后一个值，其正下方，正右方都赋值为1，因为最终血量最少为1
        dp[row][col-1] = 1;
        dp[row-1][col] = 1;
        for(int i = row -1; i >=0; i--)
        {
            for(int j = col-1; j >= 0; j--)
            {
                dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]);
                // max是因为后一个值可能为负数，因为dungeon[i][j]太大，加血太多，
                // 减去它以后就是负数，而血量不能为负数，至少为1
            }
        }
        return dp[0][0];
    }
};
