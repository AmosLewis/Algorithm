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

// 法一 最小堆
// 时间复杂度是 O(NlogK),
// 因为priority_queue插入是logN的
// 空间复杂度 O(n)
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


// 法二 双指针 快速排序，这是最优解，模版，背
// O(n) time, O(1) extra memory.
class Solution {
public:
    /**
     * @param n: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    int kthLargestElement(int n, vector<int> &nums) {
        // write your code here
        if(nums.size() == 0 || n < 0 || n > nums.size())
        {
            return -1;
        }
        // 第k大，那么如果数组最终升序，则返回的index = nums.size() - k
        // 比如[1,2,3,4,5], k = 2时候， index = 5 - 2 = 3， 
        // nums[index] = nums[3] = 4
        return partition(nums, 0, nums.size() - 1, nums.size() - n);
    }
    
    int partition(vector<int> &nums, int start, int end, int target_index)
    {
        if(start == end)
        {
            // [5 1 3 2 4] 2 -> [2 1 3 4(start end) 5]
            return nums[target_index];
        }
        
        // pivot 是快速排序中的驻点，可以选择首部，尾部，中间，或者随机
        // geekforgeek.com 中quickSort用的是尾部, 不太好理解记忆
        // 养成好习惯，自己写以后都用中间
        int pivot = nums[(start + end) / 2];
        // 为什么要新建一个left 和right，而不是用start 和 end?
        // 因为后面的递归，需要用到开始的start, end 的值与
        // 移动过的left,right共同划分区间
        int left = start, right = end;
        
        // partition 模板
        // 注意，这里有=，确保left 和right 正好落在该落的位置
        while(left <= right)
        {
            // 跳过左右两边满足 左< pivot < 右 的点
            // 注意这里无=
            while(left <= right && nums[left] < pivot)
            {
                left++;
            }
            while(left <= right && nums[right] > pivot)
            {
                right--;
            }
            
            // 交换不满足左< pivot < 右条件的两个点
            // 使得已经走过的点一定 左< pivot < 右
            if(left <= right)
            {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        // 此时 right < left
        // [start <= target_index <= right < left] 
        // 在[start                  right]之间排序 
        if(target_index <= right)
        {
             // [5 1 3 2 4] 2 
             // ->[2 1 3 4(start, target) 5(right)] 
             // ->[2 1 3 4(start tartget right) 5]
            return partition(nums, start, right, target_index);
        }
        // [right < left <= target_index <= end] 
        // 在       [left                   end]之间排序 
        if(target_index >=left)
        {
            return partition(nums, left, end, target_index);
        }
        
        // right <index <left
        //[5 1 3 2 4] 3 -> [2 1(right) 3(target) 5(right) 4]
        return nums[target_index];
        
    }
    
};


