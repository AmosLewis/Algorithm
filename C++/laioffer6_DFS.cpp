//laioffer6_DFS.cpp


// String subset
//   empty								{}
// 0 +a					{a}								{}
// 1 +b			{a,b}			{a}				{b}				{}
// 2 +c {a,b,c}	  {a,b}	   {a,c}   {a}	    {b,c}   {b}		{c}		{}
// 3

// init input = "abc" level = 0
void FindSub(const string& input, int level, string& solution)
{
	// 只在最后一层才输出 level = 3
	if(level == input.length())
	{
		if(solution.size() == 0)
		{
			cout<<"empty"<<endl;
		}else
		{
			cout<<solution<<endl;

		}
		return;
	}

	solution.push_back(input.at(level));
	FindSub(input, level + 1, solution);
	solution.pop_back();
	FindSub(input, level + 1, solution);
}
// space complexity: O(n)
// time complexity: O(2^n) 2^0 + 2^1 + 2^2 + 2^3...



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



// combination of coins
// sum 99
// coin: 25 10 5 1

//  							        99
// 0 		0*25(99)	  1*25(74)		    2*25(49)			3*25(24)
// 1	   0 ...  9(9)     0  ...  7     0  ...  3(19)  4			  0  ...  2
// 2 			0   1(4)        			   0 1   2(9)  3
// 3			   0...4						    0...9
vector<int> findCoins(const int sum, const vector<int>& coins)
{
	vector<int> counts(coins.size(), 0);
	findCoinsDFS(sum, coins, level, counts);
	return counts;
}

void findCoinsDFS(int money_left, 				// remain sum: 99 74 49 ...
				vector<int> coins, 		// 4 kinds of coins [25 10 5 1]
				int level, 				// considering one kinds of coins
				vector<int>& counts)	// init [0 0 0 0], record the number of each coins
{
	if(level == 3)
	{
		counts[3] = money_left;
	}

	// k叉树，一般就是一个循环套用一个递归， branch factor 动态变化
	for(int i = 0; i < money_left / coins[level]; i++)
	{
		counts[level] = i;
		findCoins(money_left - coins[level] * counts[level], coins, level + 1, counts);
		// counts[level] = 0; 没必要在 这步还原成parent状态，，因为下一次循环会直接覆盖这个值，这是同一层操作
		// 另外一只写法是对counts 不初始化，而是先count.push_back(i), DFS后再count.pop_back(i)恢复父亲状态
	}
}



//given a string with no duplicate letters, find all permutation of string
// a b c
// a c b
// b a c
// b c a
// c a b
// c b a

// 							    null[abc]
// 0 			a[bc]          b[ac]           c[ab]
// 1	   b[c]    c[b]      a[c]    c[a]     a[b]   b[c] 
// 2       c 		b  		 c 		 a  		b     c
// 分3层，
// 剩余多少个元素没有permutate到，就分多少个叉
// time complexity:O(n!) n + n(n-1) + n(n-1)(n-2) + ... n!
// space complexity: O(1)

// solution 1
vector<string> stringPermutation(string& S)
{
	vector<string> results;
	int size = s.size();
	string temp_result = "";
	string tempS = S;
	stringPermutationDFS(temps, temp_result, results);
	
}
void stringPermutationDFS(string& tempS, 
						int level, 
						string& temp_result, 
						vector<string>& results)
{
	if(tempS.size() == 0)
	{
		results.push_back(temp_result);
	}

	for(int i = 0; i < tempS.size(); i++)
	{
		char c = tempS.at(i);
		temp_result.push_back(c);
		temps.erase(i, 1);
		stringPermutationDFS(tempS, temp_result, results);
		temp_result.pop_back();
		tempS.insert(i, c);
	}

}

// solution2
// swap inpalce

// 							       [null]abc
// 0 			[a]bc               [b]ac            [c]ab
// 1	   A[b]c    A[c]b      B[a]c    B[c]a     C[a]b   C[b]a 
// 2       AB[c] 	AC[b]  	 BA[c] 		BC[a]  	  CA[b]   CB[a]
// 3	   ABC      ACB.     BAC.       BCA.      CAB.    CBA 
vector<string> stringPermutation(string& S)
{
	vector<string> results;
	stringPermutationDFS(S, 0, results);
	return results;
}
// 以level为ID， fix住这个char, 后面所有的char与它交换
void stringPermutationDFS(string& S, 				// input
						int level, 					// 待swap的char的index
						vector<string> results)		// result
{
	if(level == S.size()) // 当想要fix住id = S.size(), 访问越界，返回
	{
		results.push_back(S);
		return;
	}

	for(int i = level; i < S.size(); i++)
	{
		// 交换第level个元素后面的所有元素到level位置
		swap(S[level], S[i]);
		stringPermutationDFS(S, level + 1, results);
		swap(S[level], S[i]);
	}
}
// time: n + n(n-1) + n(n-1)(n-2) + ...n!
















