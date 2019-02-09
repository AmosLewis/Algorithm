class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) { 
        // 法二 同向双指针，维护一个sliding windows [left, right]
        int res = 0;
        int left = 0;
        int zeros = 0;
        int k = 1;
        for(int right = 0; right < nums.size(); right++)
        {
            if(nums[right] == 0) zeros++;
            while(zeros > k)
            {
                // 0 的个数多余一个，移动left之前 先判断是否0减去1个
                if(nums[left] == 0)
                {
                    zeros--;
                }
                left++;
            }
            
            res = max(res, right - left + 1);
        }
        return res;
    }
};
