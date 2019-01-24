/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

*/
// 方法1 DP 
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 因为要query， vector 并不适合做query, 我们换一个更快的 hash set
        unordered_set<string> dict(wordDict.cbegin(), wordDict.cend());
        int n = s.length();
        // 这题是DP题， 先对 s做一个padding
        s = " " + s; // s[1...n] 
        // 建立一个 DP数组，用于记录该分割点能不能成功
        vector<int> dp(n + 1, 0); // 初始值都是0，表示都不能分割
        //任意空字符串都是可以分割的
        dp[0] = 1;
        
        // 二重循环
        for(int i = 0; i <= n; i++){
            for(int j = 0; j < i; j++)
            {
                if(dp[j] == 1 && dict.count(s.substr(j+1, i-j))) // s[j+1, i] i-j 是其长度
                {
                    dp[i]=1;
                    break;//跳出内循环
                }
            }
        }
        
        return dp[n];
    }
};
// 方法2 递归
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.cbegin(), wordDict.cend());
        
        return wordBreak(s, dict);
    }
    
    bool wordBreak(const string& s, unordered_set<string>& dict)
    {
        // 这个字符串以前看到过，直接返回
        if(mp.count(s)) return mp[s];
        // 整个字符串是dic, 赋值后，直接返回
        if(dict.count(s)) return mp[s] = true;
        
        // 尝试每一个断词点
        for(int j = 1; j < s.length();j++)
        {
            const string left = s.substr(0,j);
            const string right = s.substr(j);
            // 核心公式
            // 如果右边的string 在字典里面存在，左边的string 可以递归分割
            if(dict.count(right) && wordBreak(left, dict))
            {
                return mp[s] = true;
            }
        }
        
        return mp[s] = false;
    }
private:
    unordered_map<string, bool> mp;//[string, is_a_word]
};
