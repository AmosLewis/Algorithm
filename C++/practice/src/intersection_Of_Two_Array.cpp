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

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // 这个2 point 的方法是最好的解决方法，比用set的快
        vector<int> result;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int p1 = 0, p2 = 0;
        while(p1 < nums1.size() && p2 < nums2.size())
        {
            if(nums1[p1] < nums2[p2])
            {
                p1++;
            }else if(nums1[p1] > nums2[p2])
            {
                p2++;
            }else // nums1[p1] > nums2[p2]
            {
                if(result.empty() || result.back() != nums1[p1])
                {
                    result.push_back(nums1[p1]);
                }
                p1++;
                p2++;
            }
        }
        
        return result;
        
    }
};
