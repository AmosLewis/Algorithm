class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 这题最主要的是一个切片的思想
        // 对小的那个数组二分查找，因为小的那个要balance更少,
        // [1] [2 3 4 5 6 7 8]
        // ... L1/R1 ...
        // ... L2/R2 ...
        const int n1 = nums1.size();
        const int n2 = nums2.size();
        // 保证 nums1 < nums2
        if(n1 > n2) return findMedianSortedArrays(nums2, nums1);

        int l = 0;
        // 注意这里右边界超过数组
        int r = n1;
        
        // ... L1/R1 ...
        // ... L2/R2 ...
        // 对nums1 二分查找 满足 L2 < R1对情况
        // 注意这里没有==
        while(l < r)
        {
            // 1 2
            // 3 4
            const int mid1 = l + (r - l)/2;// mid1 的左边有mid1个数
            const int mid2 = (n1 + n2 + 1)/2 - mid1;// mid2的左边有mid2个数
            int R1 = nums1[mid1];
            int L2 = nums2[mid2 - 1]; // nums2 大，所以 mid2至少是1
            // 注意移动左指针没有==
            if(R1 < L2) // R1太小，到右边查找
            {
                l = mid1 + 1;
            }else
            {
                r = mid1;
            } 
        }
        
        const int mid1 = l;
        const int mid2 = (n1 + n2 + 1)/2 - mid1;
        
        int L1 = (mid1 == 0) ? INT_MIN : nums1[mid1-1];
        int L2 = (mid2 == 0) ? INT_MIN : nums2[mid2 -1];
        
        // 总数是odd, 返回左边最大
        const int c1 = max(L1, L2); // max of left
        if((n1 + n2) % 2 == 1)
        {
            return c1;
        }
        
        // 总数是even,返回 左大+右小 的一半
        int R1 = (mid1 == n1) ? INT_MAX : nums1[mid1];
        int R2 = (mid2 == n2) ? INT_MAX : nums2[mid2];
        const int c2 = min(R1, R2); // min of right
        
        return (c1 + c2) * 0.5;     
    }
};
