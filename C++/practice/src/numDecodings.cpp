/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/
// 这是最开始的解法，记忆化递归，4 ms
// 每个字符串(index = 0)的对应解码个数，等于下一位开始的string + 下下位开始的string对应解码个数
// (index = 0) =（index = 1） + （index = 2)——的子串对应个数
class Solution {
public:
    int numDecodings(string s) {
        if(s.size() == 0) return 0;
        mp[""] = 1;
        return recursionNumDecodings(s);
    }
    
    int recursionNumDecodings(string& s)
    {
        if(mp.count(s)) return mp[s];// 已经处理过这个字符，直接返回其对应值
        if(s[0] == '0') return 0;
        if(s.length() == 1) return 1;
        
        string s1 = s.substr(1);// 获得从index = 1开始的子串
        string s2 = s.substr(2);// 获得从index = 2开始的字串
        
        // 对index = 1开始的子串递归求其个数
        int w = recursionNumDecodings(s1);
        const int prefix = stoi(s.substr(0,2));
        
        if( prefix <= 26) // 接下来的字符可以解码
        {
            // 对index = 2开始的子串递归求其个数
            // 最终结果应该 (index = 0) =（index = 1） + （index = 2)——的子串对应个数
            w += recursionNumDecodings(s2);
        }

        mp[s] = w;
        return w;
    }
    
private:
    unordered_map<string, int> mp;// string, count
};


// solution 2 优化一下空间复杂度
class Solution {
public:
    int numDecodings(string s) {
        if(s.size() == 0) return 0;
        //mp[""] = 1;
        return recursionNumDecodings(s, 0, s.size() - 1);
    }
    
    int recursionNumDecodings(const string& s, int left, int right)
    {
        if(mp.count(left)) return mp[left]; // 该位置字符已经处理过
        if(s[left] == '0') return 0; // 起始位置为'0'， 无法解码，应为解码要从1开始
        if(left >= right) return 1; // == 时候说明是一个字符，>说明字符为空
        
        int w = recursionNumDecodings(s, left + 1, right);
        const int prefix = (s[left] - '0') * 10 + (s[ left + 1] - '0');
        
        if(prefix <= 26)
        {
            w += recursionNumDecodings(s, left + 2, right);
        }
        
        mp[left] = w;
        return w;
        
    }
    
private:
    unordered_map<int, int>  mp;// left, count
};

// solution 3 DP 0ms
// O(n) O(n) 这里空间负责度还可以优化
/*
dp[i]= 
1 0                       s[i] s[i-1]s[i] all invalid
2 dp[i-1]                 s[i] valid
3 dp[i-2]                 s[i-1]s[i] valid
4 dp[i-1] + dp[i-2]       s[i] s[i-1]s[i] valid
s[i] valid : s[i] != '0'
s[i-1]s[i] valid: [10 26]
*/
class Solution {
public:
    int numDecodings(string s) {
        size_t n = s.size();
        if(n == 0 || s[0] == '0') return 0;
        if(n == 1) return 1;
        
        vector<int> dp(n, 0);
        int dp_negative = 1;
        dp[0] = 1;
        for(int i = 1; i < s.size(); i++)
        {
            // 连续两位数字都不可以解析，后面的就不用解析了，返回0就行
            if(!isValid(s[i]) && !isValid(s[i-1],s[i-1 ])) return 0;
            // 先处理当前位置，如果可以解析，那么其结果等于前一个字符的结果
            if(isValid(s[i])) dp[i] = dp[i-1];
            // 再处理当前位置和前一位置，如果可以解析，结果应该加上前前一个字符的结果
            if(isValid(s[i-1], s[i])) 
            {
                if(i<2)
                {
                    dp[i] += dp_negative;
                }else{
                    dp[i] += dp[i-2];
                }
            }
        }
        return dp[n-1];
    }
    
private:
    bool isValid(const char c)
    {
        return c != '0';
    }
    bool isValid(const char c1, const char c2)
    {
        const int prefix = (c1 - '0') * 10 + (c2 - '0');
        return prefix >= 10 && prefix <= 26;
    } 
};

// Solution 4 DP 
// 优化了solution 3 DP的空间
// dp1     dp2     dp3
// dp[i-2] dp[i-1] dp[i]
class Solution {
public:
    int numDecodings(string s) {
        size_t n = s.size();
        if(n == 0 || s[0] == '0') return 0;
        if(n == 1) return 1;
        
        int dp1 = 1, dp2 = 1;
        for(int i = 1; i < s.size(); i++)
        {
            int dp3 = 0;
            // 连续两位数字都不可以解析，后面的就不用解析了，返回0就行
            if(!isValid(s[i]) && !isValid(s[i-1],s[i-1 ])) return 0;
            // 先处理当前位置，如果可以解析，那么其结果等于前一个字符的结果
            if(isValid(s[i])) dp3 += dp1;
            // 再处理当前位置和前一位置，如果可以解析，结果应该加上前前一个字符的结果
            if(isValid(s[i-1], s[i])) dp3 += dp2;
            dp2 = dp1;
            dp1 = dp3;
        }
        return dp1;
    }
    
private:
    bool isValid(const char c)
    {
        return c != '0';
    }
    bool isValid(const char c1, const char c2)
    {
        const int prefix = (c1 - '0') * 10 + (c2 - '0');
        return prefix >= 10 && prefix <= 26;
    }
    
};

