class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        //combination O(n*2^n)
        //permutation O(n*n!)﻿
        vector<int> result;
        vector<vector<int>> results;
        
        // 遍历四种情况，result中应该有几个元素 0 1 2 3
        // [ [], [1], [2], [3],   [1,2], [1,3],[2,3],   [1, 2 ,3]]
        for(int n = 0; n <= nums.size(); n++)
        {
            DFS(nums, n, 0, result, results);
        }
        return results;
    }
    
    void DFS(vector<int>& nums, 
            int n,                          // result中应该有几个元素， 0 1 2 3
            int start,                      // result 应该以nums的哪个元素开始
            vector<int>& result,            // 输出：一个子集
            vector<vector<int>>& results)   // 输出：子集集合
    {
        // 当result元素个数满足设定的个数n时， 返回， 否则就开始尝试插入新的值
        if(n == result.size())
        {
            results.push_back(result);
            return;
        }
        
        // 把从start开始的元素一次result放入尝试完在拿出来
        for(int i = start; i < nums.size(); i++)
        {
            // start = 0, n = 1 时第一次
            result.push_back(nums[i]);
            // i+1 是第二层DFS时， result 放入 nums[i+1]
            DFS(nums, n, i + 1, result, results);
            result.pop_back();
        }
    }
};

// 外for
// n 0{}                                 {}
// n 1{}              
// n 2{}                   
// n 3{}   

// n 0{}                                 {}
// n 1{}              {1}               {2}             {3}
// n 2{}                
// n 3{}  

// n 0{}                                 {}
// n 1{}              {1}               {2}             {3}
// n 2{}        {1,2}     {1,3}       {2,3}             
// n 3{} 

// n 0{}                                 {}
// n 1{}              {1}               {2}             {3}
// n 2{}        {1,2}     {1,3}       {2,3}             
// n 3{}   {1,2,3}

// 法二 位运算
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> results;
        int n = nums.size();
        
        // 枚举所有情况2^n 种
        for(int i = 0; i < 1 << n; i++)
        {
            vector<int> result;
            for(int s = 0; s < n; s++)
            {
                // 找出i的哪一位为1，找到，那么对应的nums的位就是s
                if(i & (1 << s))
                {
                    result.push_back(nums[s]);
                }
            }
            results.push_back(result);
        }
        return results;
    }
};

// 法3 来offer递归求子集通解 最优解
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> results;
        vector<int> temp;
        findSubSet(nums, 0, temp, results);
        return results;
    }
    void findSubSet(vector<int>& nums, // 输入数组
                    int level,  // 是否+了nums[level - 1]
                    vector<int>& temp, // 零时存放一个结果
                    vector<vector<int>>& results)// 满足条件的所有结果
    {
        // out put the result at last level 最后一层才满足条件，中间层都不操作
        if(level == nums.size())
        {
            results.push_back(temp);
            return;
        }
        
        temp.push_back(nums.at(level));
        findSubSet(nums, level + 1, temp, results);
        temp.pop_back();
        findSubSet(nums, level + 1, temp, results);
    }
};

// level 0                              {}
// level 1                  {1}                     {}
// level 2          {1,2}        {1}        {2}             {}
// level 3   {1,2,3}     {12}  {1,2} {1}  {2,3} {2}       {3}   {}
// level 3 is the output
// space complexity: O(n)
// tiem complexity: 2^0 + 2^1 + ... 2^n = 1(1-2^n)/(1-2) = 2^n
