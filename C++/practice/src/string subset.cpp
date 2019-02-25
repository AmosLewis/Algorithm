// String subset
// 0 empty								{}
// 1 +a					{a}								{}
// 2 +b			{a,b}			{a}				{b}				{}
// 3 +c {a,b,c}	  {a,b}	   {a,c}   {a}	    {b,c}   {b}		{c}		{}

// init input = "abc" level = 0
void FindSub(const string& input, int level, string& solution)
{
	// 只在最后一层才输出 level = 3
	if(level == input.length)
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
