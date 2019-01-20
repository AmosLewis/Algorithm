int partitionArray(vector<int> &nums, int k) {
    // write your code hered
    // 相向双指针问题，快速排序的一部分，要背下这个模版
    
    // 1. 定义首位双指针
    int start = 0, end = nums.size() - 1;
    // 2. 开始循环，循环条件为指针相遇前，
    //    相遇时刻也要进行一次循环（有等于号），即 左指针 <=  右指针
    while(start <= end) // 为什么要有等于，因为在 [start][][end]的时候，可以再做一次，让start，end 停在该停的位置。start >= K 的第一个数
    {
        // 3. 循环跳过左边满足条件的点
        while(start <= end && nums[start] < k)
        {
            start++;
        }
        // 4. 循环跳过右边满足条件的点
        while(start <= end && nums[end] >= k)
        {
            end--;
        }
        
        // 5. 交换不满足条件的点（想象在左右阵营交换人质）
        //    要记住这里要加上判断左指针小于等于右指针，
        //    如果不加if，什么情况下 左指针 > 右指针 我也不知道，反正之前没加在Lintcode上报错了
        if(start <= end){
            int tmp = nums[start];
            nums[start] = nums[end];
            nums[end] = tmp;
            start++;
            end--;
        }
    }
    return start;
}
/*
Given an array nums of integers and an int k, partition the array (i.e move the elements in "nums") such that:

All elements < k are moved to the left
All elements >= k are moved to the right
Return the partitioning index, i.e the first index i nums[i] >= k.

Example
If nums = [3,2,2,1] and k=2, a valid answer is 1.

Challenge
Can you partition the array in-place and in O(n)?

Notice
You should do really partition in array nums instead of just counting the numbers of integers smaller than k.

If all elements in nums are smaller than k, then return nums.length
*/
