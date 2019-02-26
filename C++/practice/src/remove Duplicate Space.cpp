
// remove all leading/trailing and duplicate empty space
// (only leave one empty space if duplicated space happen) from the input string
// input: _ _ _ a b c _ _ e d _ _ e f _ _ _
// output: a b c _ e d _ e f
// input: _ _ _ a b c _ _ e d _ _ e f _ _ _
//		  i 
//		  j 
// (W)(_W)(_W)... (_W)
// j非_,把后面连续的一个word拷贝到i往后面的位置

void removeDuplicateSpace(string& s)
{
	int slow = 0;
	int fast = 0;
	int word_count = 0; // record if it is the first word
	while(fast < s.size())
	{
		while(fast < s.size() && fast == " " ) // 当写while循环的时候，一定要先考虑快指针越界
		{
			fast++;// skip all leading " " in front of each word 
		}

		if(word_count > 0)
		{
			s[slow] += " "; // add " " in front of (2nd+) word
		}

		while(fast < s.size() && s[fast] != ' ')
		{
			s[slow++] = s[fast++]; // copy word to slow
		}
		word_count++;
	}
	s.resize(slow);
}
