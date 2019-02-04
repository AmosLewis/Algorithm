/*
http://www.cnblogs.com/grandyang/p/7631434.html

Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.
*/

class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        // 三种情况
        // A 重复cnt次，比>=B.size，刚好能包含B
        // A 重复cnt次不够包含B，再+1才够
        // A重复cnt+1 次还是不够，直接返回 -1
        
        int b = B.size();
        string tmp_string = A;
        
        int cnt = 1;
        
        // A 重复cnt次，比>=B.size，
        while(tmp_string.size() < b)
        {
            cnt++;
            tmp_string += A;
        }
        
        if(tmp_string.find(B) != string::npos)
        {
            // 刚好能包含B
            return cnt;
        }else
        {
            // A 重复cnt次不够包含B，再+1才够
            cnt++;
            tmp_string +=A;
        }
        
        // A重复cnt+1 次还是不够，直接返回 -1
        return (tmp_string.find(B) != string::npos) ? cnt : -1;
    }
};
