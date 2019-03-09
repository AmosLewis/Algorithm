class Solution {
public:
    string frequencySort(string s) {
        // 用一个hash_map 计数
        // 把hash_map 结果放入vector<pair<char, int>> 排序
        // 法1 quicksort 但会stack overflow
        // 法2 selection sort但会heap overflow
        // 法3 bucket sort 把pair换成<int, string> 用map第二位作为index，放入index 个char
        // 法4 priority_queue 建立一个max_heap，自定义比较函数
        string res;
        unordered_map<char, int> m_map;
        for(const auto& it : s)
        {
            m_map[it]++;
        }
        
        // 注意了这里用的不是m_map的size，因为如果全一样，map.size 只== 2， 但string确很长，索引就很大
        vector<string> freq(s.size() + 1);
        for(const auto& it : m_map)
        {
            freq[it.second].append(it.second, it.first);
        }
        
        for(int i = s.size(); i > 0; i--)
        {
            if(!freq[i].empty())
            {
                res.append(freq[i]);
            }
        }
        return res;
    }

};
// t r e e
// m_map
// t 1
// r 1
// e 2
// freq
// 0
// 1 t r
// 2 e e
// 3


class Solution {
public:
    string frequencySort(string s) {
        // 用一个hash_map 计数
        // 把hash_map 结果放入vector<pair<char, int>> 排序
        // 法1 quicksort 但会stack overflow
        // 法2 selection sort但会heap overflow
        // 法3 bucket sort 把pair换成<int, string> 用map第二位作为index，放入index 个char
        // 法4 priority_queue 建立一个max_heap，自定义比较函数
        string res;
        unordered_map<char, int> m_map;
        for(const auto& it : s)
        {
            m_map[it]++;
        }
        
        vector<pair<char, int>> v(m_map.begin(), m_map.end());
        priority_queue<pair<int, char>, vector<pair<char, int>>, Cmp> Q(v.begin(), v.end());//  最大堆
        while(!Q.empty())
        {
            auto it = Q.top();
            Q.pop();
            res.append(it.second, it.first);
        }
        
        return res;
    }
    class Cmp
    {
    public:
        bool operator()(pair<char, int>& p1, pair<char, int>& p2)
        {
            return p1.second < p2.second;
        }
    };

};
// t r e e
// m_map
// t 1
// r 1
// e 2
// freq
// 0
// 1 t r
// 2 e e
// 3



