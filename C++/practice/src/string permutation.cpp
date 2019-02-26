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
// swap inpalce 最优解

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
void stringPermutationDFS(string& S, 				// input
						int level, 					// 待swap的char的index
						vector<string> results)		// result
{
	if(level == S.size())
	{
		results.push_back(S);
		return;
	}

	for(int i = level; i < S.size(); i++)
	{
		// 交换第level个元素后面的所有元素到level位置
		swap(S[level], S[i]);
		stringPermutationDFS(S, 1, results);
		swap(S[level], S[i]);
	}
}
