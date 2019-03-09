// K smallest elements in unsorted array
// 法1: offline算法
vector<int> kSmallest(vector<int>& nums, int k)
{
	// 维持一个K大的最小堆
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
		minQueue.pop()
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
