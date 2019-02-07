/*
http://www.cnblogs.com/grandyang/p/4424587.html
*/

class Solution {
public:
    bool isValid(string s) {
        // 没什么好说的，建一个字符栈
        // 不断压右边的括号进去，检查栈顶和左边的括号是否配对
        // 配对了就弹栈
        
        // 建一个字符栈
        stack<char> parentheses;
        
        for(int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if(c == '{' || c == '(' || c == '[')
            {
                // 不断压右边的括号进去
                parentheses.push(c);
                continue;
            }
            else 
            {
                // 没配对成功的情况
                if(parentheses.empty()) return false;
                if(c == '}' && parentheses.top() != '{') return false;
                if(c == ']' && parentheses.top() != '[') return false;
                if(c == ')' && parentheses.top() != '(') return false;  
            }
            // 配对了就弹栈
            parentheses.pop();
        }
        
        return parentheses.empty();
    }
};
