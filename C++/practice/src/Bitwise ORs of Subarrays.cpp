class Solution {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        // dp
        // A[i] 每个数最多32bit,flop最多32次。
        // i 最大为n,next最多n 个元素，所以时间复杂度 < O(32n)
        // 看花花笔记
        // https://docs.google.com/document/d/1jUms25z26h6Ss0oRfBpUaSWB0bW-NYvQOZr8BvSIyug/edit#

        // 用set过滤多余数字
        unordered_set<int> ans;
        unordered_set<int> cur;  // dp数组，记录上一个状态，
        unordered_set<int> next; // dp数组，temp, 和上一个cur一起 | 更新得到当前状态
        // cur =    {A[i-1],
        //           … …
        //           … A[i-2]A[i-1]}
        // next[i] = {A[i], 
        //            A[i-1] | A[i], 
        //            … …,
        //            …, A[i-2] | A[i-1] | A[i]}
        for(int a : A)
        {
            next.clear();
            next.insert(a);
            for(int b : cur)
            {
                next.insert(a | b);
            }
            cur = next;
            ans.insert(cur.begin(), cur.end());
        }
        return ans.size();
    }
};
