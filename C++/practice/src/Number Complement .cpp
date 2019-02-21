class Solution {
public:
    int findComplement(int num) {
        // mask 1111 1111
        // 0 去反就得到全1
        size_t mask = ~0; 
        // num 高位0对应 mask 1，用于后面异或去掉—num高位的1
        // num 开始非0后，mask对应为0， 用于后面异或保留低位的 0 1
        //  nums 0000 0101
        //  mask 1111 1000
        while (num & mask) mask <<= 1;
        // ~nums 1111 1010
        // res   0000 0010
        return ~num ^ mask;
    }
};
