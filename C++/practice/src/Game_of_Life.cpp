/*
https://leetcode.com/problems/game-of-life/
https://www.youtube.com/watch?v=juGxbF-eadU
*/

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        // 这题用board[i][j]倒数第一个bit位表示当前的状态，倒数第二个bit位表示下一个状态
        // 用|1 置位1
        // 用&1 判断1
        // 用 >>= 1 右移1位改变状态
        
        int row = board.size();
        // 如果row>=1，取列数, 否则row = 0 数组为空， board[0]不存在，数组访问越界
        int col = row ? board[0].size() : 0; 
        if(row == 0) return;
        
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                // 活着的个数
                int lives = 0;
                
                // 计算lives个数
                // 3*3内循环 board[y][x] [i][j]
                // 下面三种情况可以一次用 [max(0, i-1) ... ...]min(biggest, i+2) 写过来
                // 四个边角只取4个数      四条边取6个数         中间取9个数
                // [&*. ... .&*]      [... *&* ...]      [... ... ...]
                // [**. ... .**]      [**. *** .**]      [... *** ...]
                // [... ... ...]      [&*. ... .*&]      [... *&* ...]
                // [**. ... .**]      [**. *** .**]      [... *** ...]
                // [&*. ... .&*]      [... *&* ...]      [... ... ...]
                for(int y = max(0, i - 1); y < min(row, i + 2); y++)
                {
                    for(int x = max(0, j - 1); x < min(col, j + 2); x++)
                    {
                        // if(board[y][x] == 1) lives++; 与下面这句等价，但下面位操作这句更快
                        // int默认int32 占4byte,32bit；要是64位的平台也一样，占64 bit, 这里我们只用最低的两位bit
                        // 32bit int 1/0: 0000 0000 0000 000[1/0] & 0000 0000 0000 0001
                        // &1后，第1位原来数字0/1不变，高位永远都是0，
                        // 所以&完后，board[y][x]只能是1/0，不会出现其他情况
                        // 刚好lives也只要 +1/0
                        lives += board[y][x] & 1;
                    }
                }
                
                // 设置倒数第二个bit位是死是活，默认值是0，是死
                // 只要判断是否要变活的情况就可以了，
                // 下面这里的cell == board[i][j]
                //          lives == 3                      lives == 4
                // cell = 0          cell =1        cell = 1        cell =0
                // 死邻3->活          活邻2 ->活      活邻3->活        活邻4->死
                // [0    0   0]      [0    0   0]   [0     1   0]   [0     1   0]
                // [0   (0)  1]      [1   (1)  1]   [1    (1)  1]   [1    (0)  1]
                // [0    1   1]      [0    0   0]   [0     0   0]   [0     1   0]
                if(lives == 3 || lives -board[i][j] == 3) //这句也行，花花用了这句
                //if(lives == 3 || (lives == 4 && board[i][j] == 1))
                {
                    // C++中用0b前缀接01表示2进制数，这个数本质是int型
                    // 0b10 == 0000 0000 0000 0010
                    // |1 表示无论是0还是1 都置位1，
                    // 即无论该点原来是死是活，都使其活
                    board[i][j] |= 0b10;
                }
            }
        }
        
        // 全部处理完以后，要再次遍历一边数组，使第二个bit移动到第一个bit,
        // 即整个数字右移一位，高位补0，低位挤出
        // (0)[0000 0000 0000 0011] ->
        //    [(0)0.. ...  ...  0001](1)
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                // 右移1位,扔掉最低位，扔掉上一个状态
                board[i][j] >>= 1;
            }
        }
        
        return;
    }
};
