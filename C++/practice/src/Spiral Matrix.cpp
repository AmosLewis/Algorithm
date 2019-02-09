class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 每打印一行, 想象成指针向后面移动一行， 打印新的matrix
        // 每打印一列，想象成指针向后面移动一列， 打印新的matrix
        //           left                       right
        //  up   ->[ *        *        *        *        ]
        //         [ %        @        @        &        ]
        //         [ %        !        #        &        ]
        //  down ->[ +        +        +        &        ]
        
        if(matrix.size() == 0 || matrix[0].size() == 0) return {};
        
        vector<int> result;
        int up = 0;
        int left = 0;
        int down = matrix.size() - 1;
        int right = matrix[0].size() - 1;

        // while(start_row <= end_row && start_col <= end_col)
        while(true)
        {
            for(int j = left; j <= right; j++)
            {
                result.push_back(matrix[up][j]);
            }
            if(++up > down ) break;
            
            for(int i = up; i <= down; i++)
            {
                result.push_back(matrix[i][right]);
            }
            if(--right < left) break;
            
            for(int j = right; j >= left; j--)
            {
                result.push_back(matrix[down][j]);
            }
            if(--down < up) break;
            
            for(int i = down; i >= up; i--)
            {
                result.push_back(matrix[i][left]);
            }
            if(++left > right) break;
        }
        
        return result;
    }
};
