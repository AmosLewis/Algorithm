// https://www.youtube.com/watch?v=jfb72FfxWKU
// https://www.youtube.com/watch?v=cG1rZPIo3ww

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 本质上是桶排序，对应位置放对应的数
        for(int i = 0; i < nums.size(); i++)
        {
            // 3 4 -1 1
            // i nums[i] nums[i]-1 nums[nums[i] - 1]
            // 0    3       2           nums[2] = -1
            // swap
            
            // -1 4 3 1
            // i nums[i] nums[i]-1 nums[nums[i] - 1]
            // 0    -1 < 0 
            
            // i nums[i] nums[i]-1 nums[nums[i] - 1]
            // 1    4      3            nums[3] = 1
            // swap
            
            // -1 1 3 4
            // i nums[i] nums[i]-1 nums[nums[i] - 1]
            // 1    1      0            nums[0] = -1
            // swap
            
            // 1 -1 3 4 下面多次while直接跳过不执行 因为nums[i] == nums[nums[i]-1] 
            // nums[i] != nums[nums[i]-1] 表示3 不在3该在的位置(index=3-1=2)上
            // 注意这里是while 而不是if
            while(nums[i] > 0 && nums[i] < nums.size() && nums[i] != nums[nums[i]-1])
            {
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        
        for(int i = 0; i < nums.size();i++)
        {
            // [1 -1 3 4 ] 少2
            if(nums[i] != i+1)
            {
                return i+1;
            }
        }
        
        // [1 2 3]少4 
        return nums.size()+1;
    }
};
