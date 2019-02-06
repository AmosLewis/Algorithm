class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int a = s.size();
        int b = t.size();
        for(int i = 0; i < min(a,b); i++)
        {
            if(s[i] != t[i])
            {
                if(a < b) // delete
                {
                    return s.substr(i) == t.substr(i+1);
                }else if(a > b) // delete
                {
                    return s.substr(i + 1) == t.substr(i);
                }else // replace
                {
                    return s.substr(i + 1) == t.substr(i + 1);
                }
            }
        }
        // insert
        return abs(a-b) == 1;
        
    }
};
