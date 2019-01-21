/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

/*
这道题让我们求三数之和，比之前那道Two Sum要复杂一些，
考虑过先fix一个数，然后另外两个数使用Two Sum那种HashMap的解法，但是会有重复结果出现，
就算使用set来去除重复也不行，会TLE，看来此题并不是考我们Two Sum的解法。

三个数且和为0，那么除了三个数全是0的情况之外，肯定会有负数和正数，我们还是要先fix 最小的那个数，然后去找另外两个数，
我们只要找到两个数且和为第一个fix数的相反数就行了，既然另外两个数不能使用Two Sum的那种解法来找，如果能更有效的定位呢？
我们肯定不希望遍历所有两个数的组合吧，所以如果数组是有序的，那么我们就可以用【双指针】以线性时间复杂度来遍历所有满足题意的两个数组合。

我们对原数组进行【排序】，
然后开始遍历排序后的数组，这里注意不是遍历到最后一个停止，而是到倒数第三个就可以了。
这里我们可以先做个剪枝优化，就是当遍历到正数的时候就break，因为我们的数组现在是有序的了，
如果第一个要fix的数就是正数了，那么后面的数字就都是正数，就永远不会出现和为0的情况了。
然后我们还要加上重复就跳过的处理，处理方法是从第二个数开始，如果和前面的数字相等，就跳过，因为我们不想把相同的数字fix两次。
对于遍历到的数nums[k]，用0减去这个fix的数得到一个target = 0 - nums[k]，
然后只需要再之后找到两个数之和等于target即可。
我们用【两个指针】分别指向fix数字之后开始的数组首尾两个数，如果两个数和正好为target，则将这两个数和fix的数一起存入结果中。
然后就是跳过重复数字的步骤了，两个指针都需要检测重复数字。
如果两数之和小于target，则我们将左边那个指针i右移一位，使得指向的数字增大一些。
同理，如果两数之和大于target，则我们将右边那个指针j左移一位，使得指向的数字减小一些
/*

// 83ms
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 因为 a + b + c = 0 && a < b < c
        // 所以必有 a < 0，
        // 固定 a, 找target = 0 - a
        // 对 target 用两个指针，用两跟指针就要排序数组
        
        // 数组排序
        sort(nums.begin(), nums.end());
        // 边界检查 先排序，再加上首位检查，leetcode上会快12ms
        if(nums.size() < 3 || nums.back() < 0 || nums.front() > 0) {return {};}
        // 返回值
        vector<vector<int>> results;
        
        // 遍历到倒数第3个数就行，加一个 -2 leetcode 快了4ms
        for(int k = 0; k < nums.size()-2; k++)
        {
            // 先剪枝， 如果 a >0,则后面所有数字>0，则没有可行解(首字母>0 的情况包含在内了)
            if(nums[k] > 0) {continue;}
            // 如果当前值与前一个值一样，则跳过
            if(k && nums[k] == nums[k-1]){continue;}
            
            // twoSum 思路，写出target
            int target = 0 - nums[k];
            // 两个指针，相向而行，类似quickSort的partition的两个while 结构
            int left = k + 1, right = nums.size() - 1;
            while(left < right)
            {
                if(nums[left] + nums[right] == target)
                {
                    results.push_back({nums[k], nums[left], nums[right]});
                    // 应为sort过了所以相同的结果应该在一起，下一个数字可能与当前数字相同
                    // 用while 去重复
                    while(left < right && nums[left] == nums[left+1])
                    {
                        left++;
                    }
                    while(left < right && nums[right] == nums[right-1])
                    {
                        right--;
                    }
                    // 跳到下一个与当前数字不同的数字位置
                    left++;
                    right--;
                }else if(nums[left] + nums[right] > target){
                    right--;
                }else
                {
                    left ++;
                }
            }
        }
        return results;
    }
};


// 法2 无sort的解法 660ms
// 用map[nums[i], count]记录frequency
// 把map里所有的key放在一个vector里，重复的会连在一起，可以跳过
// twoSum 从下一个数start 开始搜索，unordered_set 记录某个值 是否存在 与 是否被访问过
// tmp 值回溯

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 无sort的解法
        
        vector<vector<int>> res;
        if(nums.size() < 3) return res;
        
        // 用map[nums[i], count]记录frequency
        unordered_map<int, int> mp;
        for(int i : nums)
            mp[i]++;
        
        // 把map里所有的key放在一个vector里，重复的会连在一起，可以跳过
        vector<int> arr(nums.size());
        int k = 0;
        for(auto& it : mp) 
        {
            for(int i = 0; i < it.second; i++) 
            {
                arr[k++] = it.first;
            }
        }
        
        vector<int> tmp;
        for(int i = 0; i <= arr.size() - 3; i++) 
        {
            // 重复的会连在一起 可以判断跳过
            if(i != 0 && arr[i] == arr[i - 1]) continue;
            // 简单的twoSum
            tmp.push_back(arr[i]);
            // 起始点不是0 而是 i+1， 即当前数字的下个点
            twoSum(arr, i + 1, arr.size() - 1, tmp, res, -arr[i]);
            tmp.pop_back();
        }
        return res;
        
    }
private:
    void twoSum(vector<int>& arr, 
                int start, 
                int end, 
                vector<int>& tmp, 
                vector<vector<int>>& res, 
                int target) {
        unordered_set<int> st;// 记录某个 数是否存在
        unordered_set<int> visited; // 记录某个数是否被访问过
        
        for(int i = start; i <= end; i++) {
            if(st.find(target - arr[i]) != st.end() && //存在
               visited.find(target - arr[i]) == visited.end()) {//没被访问过
                tmp.push_back(target - arr[i]);
                tmp.push_back(arr[i]);
                res.push_back(tmp);
                tmp.pop_back();
                tmp.pop_back();
                
                visited.insert(arr[i]);
                visited.insert(target - arr[i]);
            }
            st.insert(arr[i]);
        }
    }
};
