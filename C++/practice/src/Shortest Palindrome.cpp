class Solution {
public:
    string shortestPalindrome(string s) {
        // 这题遇到就随缘吧， Hard KMP
        string r = s;
        reverse(r.begin(), r.end());
        // 加个"#" 保证#一定不会被匹配到surfix==prefix 的情况，隔离r 与 s
        string t = s + "#" + r;
        // next记录该位置符合条件的surfix/prefix 长度
        // 记录DP时候，prefix 搜索的起始位子，用于下一个next的值更新
        // next[i+1] = next[i] + 1 if prefix[j] == prefix[i]
        // 初始化为0 ，保证j从0开始查找
        vector<int> next(t.size(), 0);
        // KMP DP方法
        // [j i ... ] j 是prefix指针， i是subfix指针
        // https://www.youtube.com/watch?v=GTJr8OvyEVQ
        // https://www.youtube.com/watch?v=c4akpqTwE5g
        for (int i = 1; i < t.size(); ++i) {
            // 前两步对 j 状态更新
            // 后两步对 next 的更新
            
            // next (i-1) 存放了上一次匹配时，符合条件的prefix surfix长度
            // 同时也是这次匹配的j的起始index
            //     j       i
            // a b c d a b c a
            // 0 1 2 3 4 5 6 7
            // 0 0 0 0 1 2 
            // 因为是DP，所以要先获得上一个状态值暂存
            int j = next[i - 1];
            
            // 这部分循环刚开始执行的好一段时间是跳过的，
            // 这部分实现也比较tricky
            // 为什么要将当前j前一个位置的值作为新j？
            // 这又是一个DP状态转换，对j的DP
            // 前一个位置的值表示前一个位置已经匹配到的符合条件的sub/prefix长度，也表示下一次搜索的ID
            while (j > 0 && t[i] != t[j]) 
            {
                // j 取自己前一个位子搜索的起始i
                //       j       i
                // a b c d a b c a
                // 0 1 2 3 4 5 6 7
                // 0 0 0 0 1 2 3 
                //   j2j1    j     i // 循环跳2次找到相等的情况
                // a a b a a b a a a
                // 0 1 2 3 4 5 6 7 8
                // 0 1 0 1 2 3 4 5 
                j = next[j - 1];
            }
            
            // 遇到t[i] == t[j]，对 i j 都++， 但是j 是局部变量，所以要有东西记录下上一个j, 
            // 恰好next中的数也表示上一个j的位置，也表示上一个位置符合条件的prefix surfix长度
            if(t[i] == t[j])
            {
                j++; // j = next[i-1] + 1 或者 j = next[j - 1] + 1
            } // != j不变 >>> j=j+0 >>> j+=(t[i]==t[j])
            // 这个DP状态转换是对next的
            next[i] = j; // next[i] = next[i-1] + 1 或者 next[j-1] + 1
        }
        return r.substr(0, s.size() - next.back()) + s;
        
        
        // 这题的解法很神奇
        // s取反为rev_s，找到s的前缀 == s的后缀的情况，
        // 删掉取反后相同的部分，剩下的作为放到原字符s的前缀
        //    abb -> [b]ba
        // [b]abb
        // 关键在与如何找到相同的部分
        // 网上有些算法用来KMP，不过不好理解
        // 有些简单，相向双指针就可以，
//         int left = 0; 
//         int right = s.size() - 1;
//         while(right >= 0)
//         {
//             if(s[left] == s[right])
//             {
//                 left++;
//             }
//             right--;
//         }
//         if(left==s.size()) return s;
        
//         string t = s;
//         reverse(t.begin(), t.end());

//         return t.substr(0, t.size() - left) + s;
    }
};
