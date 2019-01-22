/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

A solution set is:
(-1,  0, 0, 1)
(-2, -1, 1, 2)
(-2,  0, 0, 2)

和twoSum几乎一样，还是用hashmap,在O(n) 时间内
只不过新的target有两种情况，都查找一边就好了
*/


class Solution {
public:
    /**
     * @param nums: an array of Integer
     * @param target: an integer
     * @return: [index1 + 1, index2 + 1] (index1 < index2)
     */
    vector<int> twoSum7(vector<int> &nums, int target) {
        // write your code here
        if(nums.size() < 2)
        {
            return {};
        }
        
        unordered_map<int, int> hash_map;
        for(int i = 0; i < nums.size(); i++)
        {
            int tmp_target = nums[i] - target;
            if(hash_map.count(tmp_target))
            {
                return {hash_map[tmp_target] + 1, i + 1};
            }
            
            tmp_target = nums[i] + target;
            if(hash_map.count(tmp_target))
            {
                return {hash_map[tmp_target] + 1, i + 1};
            }
            
            hash_map[nums[i]] = i;
        }
        
        return {};
    }
};
