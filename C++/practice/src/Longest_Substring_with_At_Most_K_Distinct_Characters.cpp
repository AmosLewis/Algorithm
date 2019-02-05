/*
https://www.youtube.com/watch?v=RHFrVNmlyA8
*/

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        // 两个指针同向而行，
        // 两根指针之差表示substring 的长度
        // hash表记录每个指针出现的次数，用end创建与添加
        // 用start 删除多余字符
        // hash表的长度表示substring 不重复的长度
        // max_len 记录满足要求(<=k)的substring最大的长度
        int start = 0, end = 0;
        int max_len = 0;
        unordered_map<char, int> dic;
        
        // 遍历知道end 指向最后一个char之后
        while(end < s.size())
        {
            // 用end创建与添加
            char c = s[end];
            // 更新/创建hash表
            if(dic.count(c)  >0)
            {
                // 添加
                dic[c]++;
            }else
            {
                // 创建
                dic[c] = 1;
            }
            
            // 循环判断 substring是否满足条件
            while(dic.size() > k)
            {
                // 用start 删除多余字符
                c = s[start];
                if(--dic[c] == 0)
                {
                    dic.erase(c);
                }
                // start 向前移动直到满足 <=k
                start++;
            }
            // 上面的循环已经保证当前得到的新的substr.length一定满足 <=k 的条件
            // 但是新的substr.length可能没有旧的大，所以套用一层max
            // 更新max_len， 保证满足条件的
            max_len = max(max_len, end - start + 1);
            // end向前移动，这个是大循环，遍历所有字符
            end++;
        }
        
        return max_len;
    }
};
