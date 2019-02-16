class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        // 法1 递归 从n -> 0
        // n = 0:   none
        // n = 1:   0, 1, 8
        // n = 2:   11, 69, 88, 96
        // n = 3:   101, 609, 808, 906, 111, 619, 818, 916, 181, 689, 888, 986
        return find(n, n);
    }
    vector<string> find(int m, int n)
    {
        if(m == 0)  return {""};
        if(m == 1) return {"0", "1", "8"};
        // n=0和n=2，可以发现后者是在前者的基础上，每个数字的左右增加了[1 1], [6 9], [8 8], [9 6]
        vector<string> res;
        vector<string> t = find(m-2, n);
        for(auto a : t)
        {
            if(m != n) res.push_back("0" + a + "0");
            res.push_back("1" + a + "1");
            res.push_back("6" + a + "9");
            res.push_back("9" + a + "6");
            res.push_back("8" + a + "8");
        }
        return res;    
    }
};

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        // 法二 自0 -> n 迭代，分奇偶两类， +2 速度没有递归快
        vector<string> one{"0", "1", "8"}, two{""}, res;
        if(n%2 == 1)
        {
            // odd init
            res = one;
        }else
        {
            // even init
            res = two;
        }
        //odd 从2开始， even从3开始
        for(int i = (n % 2) + 2; i <= n; i += 2)
        {
            vector<string> t;
            for(auto a : res)
            {
                if(i != n) t.push_back("0" + a + "0");
                t.push_back("1" + a + "1");
                t.push_back("6" + a + "9");
                t.push_back("9" + a + "6");
                t.push_back("8" + a + "8");
            }
            res = t;
        }
        return res;
    }
};
