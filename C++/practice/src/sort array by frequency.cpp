#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


//td::vector<int> v = {1, 5, 2, 2, 6, 5, ....};

void quickSort(vector<pair<int, int>>& freq, int left, int right)
{
  int start = left;
  int end = right;
  int mid = left + (right-left) / 2;
  int pivot = freq[mid].second;

  while(left <= right)
  {
    while(left <= right && freq[left].second < pivot)
    {
      left++;
    }
    while(left <= right && freq[right].second > pivot)
    {
      right--;
    }
    if(left <= right)
    {
      swap(freq[left], freq[right]);
      right--;
      left++;
    }
  }
  if(start <= right)
  {
    quickSort(freq, start, right);
  }
  if(left<= end)
  {
    quickSort(freq, left, end);
  }
}

vector<int> mysort(vector<int>& A)
{
  unordered_map<int, int> m_map;
  for(const auto& it : A)
  {
    m_map[it]++;
  }

  int smalleset = -1;

  vector<pair<int, int>> freq(m_map.begin(), m_map.end());
  

  quickSort(freq, 0, freq.size()-1);

  vector<int> res;
  for(const auto& it: freq)
  {
    res.push_back(it.first);
  }
  return res;
}

vector<int> mysort2(vector<int>& A)
{
  unordered_map<int, int> m_map;
  for(const auto& it : A)
  {
    m_map[it]++;
  }
  // space O(n)
  vector<vector<int>> bucket(A.size() + 1, vector<int>());

  for(const auto& it : m_map)
  {
    bucket[it.second].push_back(it.first);
  }

  vector<int> res;
  for(int i = 0; i < bucket.size(); i++)
  {
    if(!bucket[i].empty())
    {
      for(const auto& it : bucket[i])
      res.push_back(it);
    }
  }
  return res;
}


int main(int argc, char* argv[])
{
  vector<int> v = {1, 5, 2, 2, 6, 5, 4};
  vector<int> m_v = mysort(v);
  for(const auto& it: m_v) cout<<it<<endl;
  cout<<endl;
  vector<int> v2 = {1, 5, 2, 2, 6, 5, 4};
  vector<int> m_v2 = mysort2(v2);
  for(const auto& it: m_v2) cout<<it<<endl;
}

// 1
// 6
// 4
// 5
// 2

// 4
// 6
// 1
// 2
// 5
