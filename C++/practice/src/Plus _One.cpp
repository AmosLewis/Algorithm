class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        // http://www.cnblogs.com/grandyang/p/4079357.html
        // 这题很直接，就分是9和不是9两种情况
        // 是9 +1要进位
        // 还有就是要学会vector头节点插入方法
        int n = digits.size();
        if(0 == n) return {};
        
        // 从最后一个位置开始更新数字
        for(int i = n-1; i >= 0; i--)
        {
            if(digits[i] == 9)
            {
                // 进位
                 digits[i] = 0;
            }else
            {
                // 不用进位，+ 完之后可以直接返回
                digits[i]++;
                return digits;
            }
        }
        
        if(0 == digits.front())
        {
            // vector头节点插入方法
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};
