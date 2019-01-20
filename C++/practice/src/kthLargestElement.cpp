class Solution {
public:
    /**
     * @param n: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    int kthLargestElement(int n, vector<int> &nums) {
        // write your code here
        // 法1 最小堆方法
        // 1 构造一个最小堆，顶部为最小数
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for(int i = 0; i < nums.size(); i++)
        {
            // 2 堆的大小是k
            if(min_heap.size() < n)
            {
                // 3 先初始化K个数字进去
                min_heap.push(nums[i]);//  push() is O(log(N)) 
            } 
            else if(nums[i] > min_heap.top())// top(),O(1)
            {
                //4 对第K + 1 个数字，>堆顶(最小的数)，替换（a 弹出堆顶，压入新数）
               min_heap.pop();// pop() is O(log(N)),
               min_heap.push(nums[i]);
            }
        }
        
        // 5. 返回堆顶即为第K大的数
        return min_heap.top();// top(),O(1)
    }
};
// 时间复杂度是 NlogK,
// 因为priority_queue插入是logN的
// 空间复杂度
/*
5. Kth Largest Element
Find K-th largest element in an array.

Example
In array [9,3,2,4,8], the 3rd largest element is 4.

In array [1,2,3,4,5], the 1st largest element is 5, 2nd largest element is 4, 3rd largest element is 3 and etc.

Challenge
O(n) time, O(1) extra memory.

Notice
You can swap elements in the array
*/
