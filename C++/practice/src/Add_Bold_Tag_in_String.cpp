/*
https://www.youtube.com/watch?v=rUNE3VVcXAs
*/

class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {
        // 遍历vector找到字典中最大的word的长度max_length， 
        // 用hash表重新构建dict数组便于query
        // 定义一个bold数组，作为template,用于简化+<\b>的判断
        
        // 设置bold 数组，有substing的位置为1
        // 循环产生所有的substring, 设置bold数组
        // 第一重初始位置i O(n)
        // 第二重循环(O(l*l))substring最大长度 1 ～ max_length，
        //                      或者 1 ～ n-i ,在结尾处可能 < max_length
        // 取较小的那个
        // [         i   n]
        // [    max_Length]
        // 如果在substring in dict, 对应的bold数组填为1
        // 从最长的开始查，一旦找到跳出循环
        
        // 循环加<\b>, 判断初始位置，结束位置分别处理
        
        // 找到字典中最大的word的长度max_Length， 
        int max_length = 0;
        for(const auto& it: dict)
        {
            int tmp_length = it.size();
            max_length = max(max_length, tmp_length);
        }
        // 用hash表重新构建数组
        unordered_set<string> hash_dict(dict.begin(), dict.end());
        
        // 定义一个bold数组,作为template,用于简化+<\b>的判断
        int l_string = s.length();
        vector<int> bolded(l_string, 0);
        
        // 设置bold 数组，有substing的位置为1
        // 循环产生所有的substring
        for(int i = 0; i < l_string; i++)//O(n)
        {
            // 第二重循环(O(l*l))substring最大长度 1 ～ max_length，
            //                      或者 1 ～ n-i ,在结尾处可能 < max_length
            // 取较小的那个
            // [         i   n]
            // [    max_Length]
            for(int l = min(max_length, l_string - i); l >=1; l--)//O(l*l)注意这里用l 循环，不是i
            {
                // 如果在substring in dict, 对应的bold数组填为1
                if(hash_dict.count(s.substr(i,l))) // substr(start_index, length)
                {
                    fill(bolded.begin() + i, bolded.begin() + i + l, 1);
                    // 从最长的开始查，一旦找到跳出循环
                    break;
                }
            }
        }
   
        // 循环加<\b>, 判断初始位置，结束位置分别处理
        string result;
        for(int i = 0; i < l_string; i++)
        { 
            // \b[110                ] 初始位置
            //   [    0\b111111      ]
            if((1 == bolded[i]) && ( (0 == i) || (0 == bolded[i-1]) )) result +="<b>";
            result += s[i];
            // [                01]\b 结束位置
            // [    11111\b0      ] 
            if((1 == bolded[i]) && (l_string-1 == i || 0 == bolded[i+1])) result += "</b>";
        }

        return result;   
    }
};
