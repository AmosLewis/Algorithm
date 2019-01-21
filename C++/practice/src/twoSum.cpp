/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You *may* assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

//O(n)的
// hash表记录每个值的位置
// hash查找 【sum-target】 的位置
// 一次遍历，先查找结果，然后建hash table
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 返回值 两个数
        vector<int> indices;
        // hash表，记录每个值的下表
        // 用map 因为BST 查找时间为log(n), 哈希表是O(1)-O(n)不稳定
        map<int, int> value_indices;
        
        // 一次遍历所有数字
        for(int i = 0; i < nums.size(); i++)
        {
            // 查找sum - target的值
            if(value_indices.find(target - nums[i]) != value_indices.end())
            {
                indices.push_back(value_indices[target-nums[i]]);
                indices.push_back(i);
                return indices;
            }
            // 保存下所有数字的 index，用于上面的查找插入
            value_indices[nums[i]] = i;
        }
        
        return indices;
    }
};
