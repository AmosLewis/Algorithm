class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        // 这题与game of life有几分相似，都是四重循环，
        // 图像的卷积操作，对于边界的处理也是同样的方法 max-min 请熟练记住这个用法
        // 注意不能在源数组上操作，要另外开辟一个
        int row = M.size();
        int col = row ? M[0].size() : 0;
        if(!row) return {};
        
        vector<vector<int>> result(row, vector<int>(col, 0));
        
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                int num = 0;
                int sum = 0;
                for(int y = max(0, i - 1); y < min(row, i + 2); y++)
                {
                    for(int x = max(0, j - 1); x < min(col, j + 2); x++)
                    {
                        num++;
                        sum += M[y][x];
                    }
                }

                result[i][j] = floor(sum / num);
            }   
        }

        
        return result;
    }
};
