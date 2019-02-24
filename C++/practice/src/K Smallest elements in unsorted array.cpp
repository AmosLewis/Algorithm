vector<int> kSmallest(vector<int>& nums, int k)
{
	// 维持一个nums大的最小堆,很耗空间
	// 遍历一次数组，往最小堆里面插入所有数据
	vector<int> results;
	if(nums.size() == 0 || nums.size() < k || k == 0)
	{
		return results;
	}
	priority_queue<int, vector<int>, greater<int>> minQueue;
	for(const auto& it : nums)// Time: O(nlogn) Space: O(n)
	{
		minQueue.push(it);
	}
	for(int i = 0; i < k; i++) // Time: O(klogn) Space: O(k)
	{
		results.push_back(minQueue.top());
		minQueue.pop()；// O(logn)
	}
	return results;
}
// Time O(nlogn)
// Space O(n)

// 法2：Max heap, online 算法
vector<int> kSmallest(vector<int>& nums, int k)
{
	// 维持一个K大的最大堆
	// 遍历一次数组，往最大堆里面插入K个数据
	vector<int> results;
	if(nums.size() == 0 || nums.size() < k || k == 0)
	{
		return results;
	}
	priority_queue<int> maxQueue;
	for(const auto& it : nums)// Time: O(nlogk) Space: O(k)
	{
		if(maxQueue.size() < k)
		{
			maxQueue.push_back(it);
		}else if(it < maxQueue.top())
		{
			maxQueue.pop();
			maxQueue.push(it);
		}
	}
	for(int i = 0; i < k; i++) // Time: O(klogk) Space: O(k)
	{
		results.push_back(maxQueue.top());
		minQueue.pop()
	}
	return results;
}
//Time: O(nlogk)
//Space: O(k)


// 法3 quick sort partition
// 最坏的情况：O(n^2)
// 即每次都取最大的数，n + n-1 + n-2 +...+1 = n(1+n)/2
// average: O(n)
// 每次减少一半：n + n/2 + n/4 + .... = 2n 
vector<int> kSmallest(vector<int>& nums, int k)
{
	vector<int> result;
	KSmallestQuickSort(0, nums.size() - 1, k, nums, result);

	return result;
}
void KSmallestQuickSort(int start, int end, int k, vector<int>& nums, vector<int>& result)
{
	if((end - start + 1) == k)
	{
		for(int i = start; i <= end; i++)
		{
			result.push_back(nums[i]);
		}
	}

	int pivot = start + (end - start) / 2;
	int target = nums[pivot];
	int left = start, right = end;

	while(left <= right)
	{
		while(left <= right && nums[left] < target) left++;
		while(left <= right && nums[right] > target]) right--;
		if(left <= right)
		{
			swap(nums[left], nums[right]);
			left++;
			right--;
		}
	}
	// start       right left      end
	if(k <= right)
	{
		KSmallestQuickSort(start, right, k, nums, result);
	}
	if(k >= left)
	{
		// 把前一半的数放入结果中保存
		for(int i = start; i < right; i++)
		{
			result.push_back(nums[i]);
		}
		// 去右边去找剩下的 k - left 个数
		KSmallestQuickSort(left, right, k - left, nums, result);
	}
}
