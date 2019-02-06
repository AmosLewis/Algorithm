/*

*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    // 这里每次调用的时候，　buf都指向新的文件的开头
    int read(char *buf, int n) {
        // 开辟一个全局的空间用于存储read4的4个字符
        // 对这个空间用两个指针，一读一写
        // 循环n次，用读指针读出tmp 覆盖buf
        
        for(int i = 0; i < n; i++)
        {
            // 如果刚开始 / read完tmp中所有字符
            if(readPos == writePos)
            {
                // writePos = 0-4 要写几个字符
                writePos = read4(tmp);
                // readPos此时由下面的readPos++ 已经变成了 0-4，
                // 需要重新初始化指到tmp的，读取新的tmp
                readPos = 0;
                // 这种是要读的太多，有的字符太少， 
                // 导致没循环到n,就读完了文件 直接返回当前读到的位置就是文件个数
                // 当前位置i是文件的end()
                if(writePos == 0) return i;
            }
            
            // 循环n次，用读指针读出tmp 覆盖buf
            buf[i] = tmp[readPos++];
            
        }
        return n;
    }
    
    // 对这个空间用两个指针，一读一写
    // 要记得【显式】初始化为0
    int readPos = 0, writePos = 0;
    // 开辟一个全局的空间用于存储read4的4个字符
    char tmp[4];
};
