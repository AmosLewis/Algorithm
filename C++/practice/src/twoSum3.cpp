/*
Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

Example 1:

add(1); add(3); add(5);
find(4) -> true
find(7) -> false
Example 2:

add(3); add(1); add(2);
find(3) -> true
find(6) -> false
*/
//哈希表的解法，我们把每个数字和其出现的次数建立映射，然后我们遍历哈希表，
//对于每个值，我们先求出此值和目标值之间的差值t，
//然后我们需要分两种情况来看，
//如果当前值不等于差值t，那么只要哈希表中有差值t就返回True，
//或者是当差值t等于当前值时，如果此时哈希表的映射次数大于1，
//则表示哈希表中还有另一个和当前值相等的数字，二者相加就是目标值，

// 法1
// 用unordered_map 存<数据,其出现的次数>
// 别用map leetcode 测试以后速度明显变慢
// 因为可能有重复，所以对重复的情况分类讨论
// 依旧用到twoSum 中 遍历数组，查找的target = sum - nums[i]
class TwoSum {
public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    unordered_map<int, int> nums;
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        nums[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        // 遍历数组
        for(auto a: nums)
        {
            // 目标
            int target = value - a.first;
            // 重复的情况，查看是否确实有多个重复数字可以使用
            if(target == a.first && a.second > 1)
            {
                return true;
            }else if(target != a.first && nums.count(target)) // 一般情况，无重复数字，直接查找是否有这个数字
            {
                return true;
            }
        }
        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * bool param_2 = obj.find(value);
 */
 
 // 法2 用unordered_multiset  存储数据， 思路一样，但是速度显然慢了。
 
 class TwoSum {
public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    unordered_multiset<int> nums;
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        nums.insert(number);
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for(auto a: nums)
        {
            int target = value - a;
            if(target == a && nums.count(target) > 1)
            {
                return true;
            }else if(target != a && nums.count(target))
            {
                return true;
            }
        }
        return false;
    }
};
 
 
 
