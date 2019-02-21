class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> q;
        
        // 记录每个数出现的次数
        for(auto i : nums) ++m[i];
        // 直接用最大堆排序
        for(auto it:m)
        {
           q.push(make_pair(it.second, it.first)); 
        }
        
        // 返回前K大个
        vector<int> results;
        for(int i = 0; i < k;i++)
        {
            results.push_back(q.top().second);
            q.pop();
        }
        return results;
    }
};
