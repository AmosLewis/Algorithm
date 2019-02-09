class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // 这个解法极其简单
        // 用两个set, 一个用来查询，一个用来插入去重
        set<int> s(nums1.begin(), nums1.end());
        // result 不可以直接用vector, 会有重复插入相同数的情况
        set<int> result;
        for(auto it: nums2)
        {
            if(s.count(it)) // O(nlogn)
            {
                result.insert(it);
            }
        }
        
        return vector<int>(result.begin(), result.end());
    }
};
