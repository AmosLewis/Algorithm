/*
https://www.youtube.com/watch?v=VSq4wxSpbTc
看这个讲解前面的动画就行
*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // 快慢指针问题
        // 用快指针做循环， 遇到不同的点就++慢，s[慢] = s[快]
        if(nums.size() == 0) return 0;
        
        int i = 0; // 慢
        for(int j = 1; j < nums.size(); j++) // 快
        {
            if(nums[i] != nums[j])
            {
                i++;
                nums[i] = nums[j];
            }
        }
        return i+1;
    }
};
