/*
Given an array S of n integers, are there elements a, b, c,
and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
    
    3Sum 外面再套一层循环，相向双指针
    
    手动进行去重复处理。
    主要可以进行的有三个地方，首先在两个for循环下可以各放一个，因为一旦当前的数字跟上面处理过的数字相同了，那么找下来肯定还是重复的。
    之后就是当sum等于target的时候了，我们在将四个数字加入结果res之后，left和right都需要去重复处理，分别像各自的方面遍历即可
*/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> results;
        int n = nums.size();
        if(n < 4)
        {
            return {};
        }
        
        sort(nums.begin(), nums.end());
        vector<int> tmp(4);
        //第一个数遍历0到倒数第四个
        for(int i = 0; i < n - 3; i++)
        {
            // 去除重复的第一个数
            if(i > 0 && nums[i] == nums[i-1]) continue;
            // 第二个数遍历从第一个数后面一个数开始
            for(int j = i + 1; j < n - 2; j++)
            {
                // 注意这里必须是 j > i + 1, 不能是 j > 0,否则[0,0,0,0] ->{}
                // 去重第二个数
                if(j > i + 1 && nums[j] == nums[j-1]) continue;
                // 相向双指针
                int left = j + 1, right = n - 1;
                while(left < right)
                {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum == target)
                    {
                        tmp[0] = nums[i];
                        tmp[1] = nums[j];
                        tmp[2] = nums[left];
                        tmp[3] = nums[right];
                        results.push_back(tmp);
                        // 去重第三个数
                        while(left < right && nums[left] == nums[left + 1]) left++;
                        // 去重第四个数
                        while(left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    }else if(sum < target)
                    {
                        left++;
                    }else
                    {
                        right--;
                    } 
                }
            }
        }
        
        return results;
        
    }
};
