class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) { 
        // 最优解
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

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) { 
        // 法三 同向双指针，维护一个sliding windows [left, right]
        // 不过这次不能用数组下表访问left
        // 这次用一个Q记录下所有的0的位置， 用right记录，然后最先push进的的就是left
        // 移动left 后要pop
        int res = 0;
        int left = 0;
        int zeros = 0;
        int k = 1;
        queue<int> Q;
        for(int right = 0; right < nums.size(); right++)
        {
            if(nums[right] == 0) Q.push(right);
            while(Q.size() > k)
            {
                // 移动left 
                left = Q.front() + 1;
                Q.pop();
            }
            
            res = max(res, right - left + 1);
        }
        return res;
    }
};

