/*
http://www.cnblogs.com/grandyang/p/5174322.html
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
    int read(char *buf, int n) {
        // 用一个文件指针offset指向buf的结尾， 指针的大小就是文件的大小
        // 初始时候指针长度为0
        int offset = 0;
        while(true)
        {
            // 获取当前读到的字符长度， 字符存入buf的结尾
            int current = read4(buf + offset);
            // 没有新的输入，说明读完了，直接跳出循环
            if(current == 0) break;
            // 文件指针向后移动
            offset += current;
        }
        // 如果offset = 3 , n = 100, 只有3个字符，却要求读100个，则只返回3
        return min(offset, n);
    }
};


// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        // 递归
        int current = read4(buf);
        // 要的不多
        // current = 3, n = 2 有3个字符取只要俩
        // current = 4, n = 4 有四个字符，只要4个
        // current = 4, n = 2 有四个字符，只要2个
        if(current >= n) return n;
        // 要的多,有的少
        // current = 2, n = 4
        // current = 2, n = 10
        if(current < 4) return current;
        // 递归, buf 始终指向最后一位
        return 4 + read(&buf[4], n - 4);
    }
};
