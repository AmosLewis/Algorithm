/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

[-2, 0, 1]
[-2, 0, 3]
Follow up:
Could you solve it in O(n2) runtime?
我们借鉴之前那两道题3Sum Closest和3Sum中的方法，采用双指针来做，
这里面有个trick就是当判断三个数之和小于目标值时，此时结果应该加上right-left，
因为数组排序了以后，如果加上num[right]小于目标值的话，那么加上一个更小的数必定也会小于目标值，
然后我们将左指针右移一位，否则我们将右指针左移一位，参见代码如下：
*/

// O(n^2)
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if(nums.size() < 3)
        {
            return 0;
        }
        int count = 0;
        
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < nums.size() - 2; i++)
        {
            int left = i + 1, right = nums.size() - 1;
            while(left < right)
            {
                // 这里和threeSumClosest一样，只是不用初始化比较大小
                int sum = nums[i] + nums[left] + nums[right];
                // 小于target 就行
                if(sum < target)
                {
                    // 这里很关键，right左边全部满足，所以加上right-left
                    count += right - left ;
                    left++;
                }else{
                    right--;
                }
            }
        }
        
        return count;
        
    }
};
