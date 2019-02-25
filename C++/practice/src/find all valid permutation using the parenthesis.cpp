// ()()()find all valid permutation using the parenthesis provided
// DFS
// 每层代表这个位置是否可以放（ 或者 ）
// int n=2, l = 0, r = 0, temp="" results=[]
// 0 1 2 3
// ( ( ( (
// ) ) ) )
void DFS(int n,							// total nums of () need to create, so the level is 2n
		int l,							// number of ( added to temp so far
		int r,							// ) added to temp so far
		string& temp,
		vector<string>& results)
{
	if(l == n && r == n)
	{
		results.push_back(temp);
		return;
	}

	if(l < n)
	{
		temp.push_back("(");
		DFS(n, l + 1, r, temp, results);
		temp.pop_back();
	}

	if(r < l)
	{
		temp.push_back(")");
		DFS(n, l, r + 1, temp, results);
		temp.pop_back();
	}
}
// 0 							  ""
// 1			        "("						)
// 2			"("			    ")"			 (	   )
// 3		(		")"	    "("      )
// 4.     (	  )   (   ")"  (  ")"  (   )
// (())
// ()()
