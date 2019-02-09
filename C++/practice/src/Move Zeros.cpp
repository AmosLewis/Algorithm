class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // 同向双指针
        // 注意 right 不能从1开始
        // 否则 [1 2]-> [2 1]
        for(int left = 0, right = 0; right < nums.size(); right++)
        {
            if(nums[right] != 0)
            {
                swap(nums[left], nums[right]);
                left++;
            }
        }
    }
};
// ij 
// 0 1 0 3 12
//   i j
// 1 0 0 3 12
//   i   j 
// 1 0 0 3 12
//     i   j
// 1 3 0 0 12
