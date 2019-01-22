/*
Given an array consists of non-negative integers, your task is to count the number of triplets chosen from 
the array that can make triangles if we take them as side lengths of a triangle.

Example 1:

Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
 

Note:

The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].

threeSumSmaller 变种
排序之后，从数字末尾开始往前遍历，将left指向首数字，将right之前遍历到的数字的前面一个数字，
然后如果left小于right就进行循环，循环里面判断如果left指向的数加上right指向的数大于当前的数字的话，
那么right到left之间的数字都可以组成三角形，这是为啥呢，相当于此时确定了i和right的位置，
可以将left向右移到right的位置，中间经过的数都大于left指向的数，所以都能组成三角形，
加完之后，right自减一，即向左移动一位。
如果left和right指向的数字之和不大于nums[i]，那么left自增1，即向右移动一位
*/

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        // a<b<c a+b>c
        // fix c
        if(nums.size() < 3)
        {
            return 0;
        }
        int count = 0;
        sort(nums.begin(), nums.end());
        
        // 这里与threeSumSmaller不同的是，从最后一个数开始往前倒着循环
        // 因为我们fix的是最大的数c,c 作为target
        for(int i = nums.size() - 1;i > 1; i--)
        {
            int left = 0, right = i-1;
            while(left < right)
            {
                if(nums[left] + nums[right] > nums[i])
                {
                    // 与threeSumSmaller相似的trick，
                    // left 与right满足，则[left 到 right]的也一定满足 a + b >c
                    count += right - left;
                    right--;
                }else
                {
                    left++;
                }
            }
        }
        
        return count;
    }
};
