class Solution {
public:
    string minWindow(string s, string t) {
        string result = "";
        if(s.empty() || t.empty())
        {
            return result;
        }
        
        // 存放t的每一个char需要找几个，后面每找到一个对其--，
        unordered_map<char, int> hash_map;
        for(const auto& ch : t) ++hash_map[ch];
        
        int slow = 0, min_len = INT_MAX, cnt = 0;
        for(int fast = 0; fast < s.size(); fast++)
        {
            // t中的ch = s[fast]还有剩余的个数没找到，对每个s[fast]都--
            if(--hash_map[s[fast]] >= 0)
            {
                cnt++;
            }
            // t中的字符被找全了
            while(cnt == t.size())
            {
                // 找到的这个substr比之前的更段
                if(fast - slow + 1 < min_len)
                {
                    min_len = fast - slow + 1;
                    result = s.substr(slow, min_len);
                }
                // 如果slow这个点移走，发现hash_map剩余的要找的个数 >0 个
                // 说明t被找到的个数减少了
                if(++hash_map[s[slow]] > 0)
                {
                    cnt--;
                }
                slow++;
            }
        }
        return result;
    }
};
