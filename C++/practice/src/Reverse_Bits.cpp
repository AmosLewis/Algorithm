class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0; i < 32; i++)
        {
            // 获得res最低位，并设置位0， 其他位置循环左移不变
            res <<= 1;
            // n 0000 0000 0000 0011
            // 1 0000 0000 0000 0001
            // 比较此时n的最低位与1 的关系， 如果是1， 就设置res
            if(n & 1 == 1)
            {
                // 设置res， 
                // res本来最低位是0, XOR 1, 不同，变1
                // res高位是已经设置好的数字，XOR 0 不变，因为
                //  1 的高位全是0
                //  高位是0，XOR 0， 相同，还是0
                //  高位是1，XOR 0， 不同，还是1
                // XOR 相同是0，不同是1
                res ^=1;
            }
            
            // n右移，把最低位扔掉，处理下一位
            n >>= 1;
        }
        
        return res;
    }
};
