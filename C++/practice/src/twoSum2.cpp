/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.
Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
*/

// 法1
// 两根指针 相向而行 O(n)
// while(left <= right)
// sum == target 返回
// sum < target left ++
// sum > target right--

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while( l <= r)
        {
            int sum = numbers[l] + numbers[r];
            if (sum == target){
                return {l + 1, r + 1};
            }
            else if(sum < target)
            {
                l++;
            }
            else if(sum > target)
            {
                r--;
            }
        }
        return {};
    }
};


// 法2 二分查找 O(NlogN)
// 因为一定有结果，所以遍历每个数字
// 依旧与twoSum 的思路一样， 要找 sum - target,
// 只是这次用二分查找，上次用map 的BST函数查找
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for(int i = 0; i < numbers.size(); i++)
        {
            int new_target = target - numbers[i];
            int left = i + 1, right = numbers.size() - 1;
            while(left + 1 < right)
            {
                int mid = left + (right - left) / 2;
                if(new_target == numbers[mid])
                {
                    return{i+1, mid+1};
                }else if(new_target > numbers[mid])
                {
                    left = mid;
                }else
                {
                    right = mid;
                }
            }
            if(numbers[left] == new_target)
            {
                return {i + 1, left + 1};
            }
            if(numbers[right] == new_target)
            {
                return {i + 1, right + 1};
            }
        }
        return {};
    }
};




