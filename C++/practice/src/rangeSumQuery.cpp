/*
303. Range Sum Query - Immutable
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.

// Solution 1: brute-force, time O(m*n), space O(n) 96ms
// Solution 2: 建一个2Dsum 记录, time O(n^3) space MLE
// Solution 3: DP 建立一个一维的sum_dp[] 每个表示之前的所有数字的和
//              time O(n + m),spave O(n) 16ms
*/

class NumArray {
// Solution 3: DP 建立一个一维的sum_dp[] 每个表示之前的所有数字的和
//              time O(n + m),spave O(n) 16ms
public:
    NumArray(vector<int> nums) {
        int n = nums.size();
        if(n == 0) return;
        
        //sums_ = std::move(nums); // 用这句下面两句就不用了，速度不影响
        sums_ = vector<int>(n, 0); // sums_ 要初始化
        sums_[0] = nums[0];
        
        for(int i = 1; i < n; i++)
        {
            sums_[i] += sums_[i-1] + nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        if( i == 0) return sums_[j];
        return sums_[j] - sums_[i-1];
    }
private:
    vector<int> sums_;  
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */

class NumArray {
// Solution 1: brute-force, time O(m*n), space O(n) 96ms

public:
    NumArray(vector<int> nums) {
        // 把nums给nums, 然后销毁指向nums的指针
        nums_ = std::move(nums);
    }
    
    int sumRange(int i, int j) {
        int sum = 0;
        for(int indice = i; indice <= j; indice++)
        {
            sum += nums_[indice];
        }
        return sum;
    }
private:
    vector<int> nums_;  
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
