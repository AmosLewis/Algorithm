class Solution {
public:
    /*
     * @param nums: An integer array sorted in ascending order
     * @param target: An integer
     * @return: An integer
     */
    int lastPosition(vector<int> nums, int target) {
        // write your code here
        if (nums.size() == 0) {
            return -1;
        }
        
        int start = 0, end = nums.size()-1;
        
        while (start + 1 < end ){
            int mid = start + (end - start) /2;
            if (nums[mid] < target) {
                start = mid;
            } else if (target < nums[mid]) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        // 注意 这里一定要考察开始和结尾
        if (nums[end] == target) {
            return end;
        } else if (nums[start] == target) {
            return start;
        }
        return -1;
    }
};
