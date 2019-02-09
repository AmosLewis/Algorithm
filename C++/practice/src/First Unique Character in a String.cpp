class Solution {
public:
    int firstUniqChar(string s) {
        // 法2 开辟一个内存空间，存储26个字母的出现首地址
        // -1 表示没有遍历过 -2 表示遍历过1次以上， >-1 表示首地址
        // 找到最小正数就好，这种情况对于string特别大的时候比较好，因为只用时间复杂度O(n+26) 即O（n）,
        // 而不是简单的hash表遍历两次 O(2n)
        if(s.size() == 0) return -1;
        unordered_map<char, int> m; // <char count>
        for(int i = 0; i < 26; i++)
        {
            m['a' + i] = -1;
        }
        
        for(int i = 0; i < s.size(); i++)
        {
            if(m[s[i]] == -1)
            {
                m[s[i]] = i;
            }else if(m[s[i]] > -1)
            {
                m[s[i]] = -2;
            }
        }
        
        int min_val = -1;
        for(const auto& it:m)
        {
            if(min_val == -1 && it.second > -1)
            {
                min_val = it.second;
            }else if(it.second > -1)
            {
                min_val = min(it.second, min_val);
            }
        }
        
        return min_val;
    }
};

