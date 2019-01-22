/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 

这道题让我们求最接近给定值的三数之和，是在之前那道 3Sum 三数之和的基础上又增加了些许难度，那么这道题让我们返回这个最接近于给定值的值，
即我们要保证当前三数和跟给定值之间的差的绝对值最小，所以我们需要定义一个变量diff用来记录差的绝对值，然后我们还是要先将数组排个序，
然后开始遍历数组，思路跟那道三数之和很相似，都是先确定一个数，然后用两个指针left和right来滑动寻找另外两个数，每确定两个数，
我们求出此三数之和，然后算和给定值的差的绝对值存在newDiff中，然后和diff比较并更新diff和结果closest即可，代码如下：
*/
// O(n2)
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        // 边界检查
        if(nums.size() < 3)
        {
            return 0;
        }
        
        // 排序
        sort(nums.begin(), nums.end());
        // 随机取三个数初始化 sum 与diff用于迭代更新, 返回值是sum
        int sum = nums[0] + nums[1] + nums[2];
        int diff = abs(sum - target);
        
        // 遍历每一个数字，取出后面一个数和最后一个数进行  相向双指针
        for(int i = 0; i < nums.size() - 1; i++)
        {
            int left = i + 1, right = nums.size() - 1;
            // 双指针更新
            while(left < right)
            {
                // 新三数和，差值
                int new_sum = nums[i] + nums[left] + nums[right];
                int new_diff = abs(new_sum - target);
                // 比较差值，如果差值更小，满足题意，更新
                if(new_diff < diff)
                {
                    diff = new_diff;
                    sum = new_sum;
                }
                
                // 根据新三数和 相向移动双指针，注意不是用全局三数和
                if(new_sum < target) 
                {
                    left++;
                }else
                {
                    right--;
                };
            }
        }
        return sum;
    }
};
