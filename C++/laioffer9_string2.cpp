//laioffer9_string2.cpp


// 4 string reverse

// Q4 string reversal
// 4.1 两根指针相向而行
void reverseString(string& s)
{
	int i = 0, j = s.size() - 1;
	while(i < j)
	{
		char c = s[j];
		s[j] = s[i];
		s[i] = c;
		i++;
		j--;
	}
} 

// 4.2 递归写法
void reverseString(string& s, int left, int right)
{
	if(left >= right)
	{
		return;
	}
	swap(s[left], s[right]);
	reverseString(s, left + 1, right - 1);
}

//4.3 I love yahoo -> yahoo love I
// 法1 用一个stack, 原来的string 就可以看成一个stack
// | I love yahoo
// yahoo
string& reverseSentence(string& s)
{
	int n = s.size();
	// 存放一个完整的单词， 用了O(n)的空间复杂度
	string temp;
	string result;
	for(int i = n - 1; i >= 0; i--)
	{
		if(s[i] == ' ')
		{
			result + = temp;
		}
		temp = s[i] + temp;// h + OO
	}
}

// 法二 
// reverse each word
// reverse sentence

// I love yahoo
//   i  j
// I ovel oohay
// O(n)
void reverseSentence(string& s)
{
	int i = 0, j = 0;
	string result;
	for(i = 0; i < s.size(); i++)
	{
		if(s[i] != ' ')
		{
			// reverse each word
			while(j < s.size())
			{
				if(j == s.size() - 1)
				{
					// I love yahoo
					//        i   j
					break;
				}else if(s[j+1] != ' ')
				{
					j++;
				}
			}
			// love -> evol
			// i  j
			reverseString(s.substr(s[i], j - i + 1), i, j);
			// love -> evol yahoo
			// 			   ij
			i = j+1;
			j += 2;
		}
	}
	// reverse sentence
	reverseString(s, 0, s.size() - 1);
}

// 4.4
// shift the whole string to the right hand by k position
// abcd | ef
// dcba | fe
// ef | abce
void reverseString(string& s, int left, int right)
{
	if(left >= right)
	{
		return;
	}
	swap(s[left], s[right]);
	reverseString(s, left + 1, right - 1);
}
void shiftKStringtoRight(string& s, int k)
{
	int n = s.size();
	if(k > n) return;

	// step1 先在各自区间reverse
	reverseString(s, 0, n - k - 1);
	reverseString(s, n - k, n - 1);
	// step2 reverse 整个sentence
	reverseString(s, 0, n-1);
}


// 5
// Char Replacement

// Expample 1 s1.length > s2.length
// replace "den" with "pp"
// s t u d e n t d e n t
//		 s 
//		 f
// slow: all the letters on the left side of i is the result to return
// fast: iterrate all the letters

// f: the pointer point to the first element of str1
bool isPattern(string& str, int f, string& str1)
{ 
	// 检查f后面时候是否一个str1 pattern
	for(int i = 0; i < str1.size() ; i++)
	{
		if(str[i + f] != str1[i])
		{
			return false;
		}
	}
	// 全检查完了没有发现不同，说明就是f 后面就是str1 pattern
	return true;
}
// str: source string
// str1: the pattern need to be replaced
// str2: the pattern used to replace
void charReplace1(string& str, string& str1, string str2)
{
	int s = 0;
	int f = 0;
	while(f <= str.size() - str1.size())
	{
		// 发现pattern的第一个字符
		if(str[f] = str1.front())
		{
			if(isPattern(str, f, str1))
			{
				// copy str2 to slow pointer
				for(i = 0; i < str2.size();i++)
				{
					str[s++] = str2[i];
				}
				// 移动f到pattern 后的第一个位子
				f += str1.size();
			}
		}else
		{
			// 对于非pattern，一直向后移动
			s[s++] = s[f++];
		}
	}
}


// Example2
// str1.size() < str2.size()
// _
// &1*
// afdajfowi_lasjfoei_dsfaf
// afdajfowi_lasjfoei_dsfaf _ _ _ _

// step1: reserve place for str
// 		1.1 iterate to find how many str1 pattern in str: times
//      1.2 calulate the new space: length of src + times * difference
// 		1.3 reserve
// step2: two pointer start from the end 
// afdajfowi_lasjfoei_dsfaf _ _ _ _
//								  s
//						  f
// s: all the letters on the right side of s is the result to be return
// f: iteratve all str leters from the right
void charReplace2(string& str, const string& str1, const string& str2)
{
	// step1 reserve place for str
	// 1.1 iterate to find how many str1 pattern in str: times
	int times = 0;
	for(int i = 0; i <= str.size() - str1.size(); i++)
	{
		if(isPattern(str, i, str1))
		{
			times++;
		}
	}
	// 1.2 calulate the new space: length of src + times * difference
	int n = str.size() + times * (str2.size() - str1.size());
	// 1.3 reserve
	str.reserve(n);

	// two pointer start from the end
	int s = n - 1;
	int f = str.size() - 1; 
	while(f >= str2.size() - 1)
	{
		if(str[f] == str2.back())
		{
			if(isPattern1(str, f - str1.size(), str1)) // f - str1.size() 计算如果是str1,应该从哪里开始检查
			{
				for(int i = 0; i < str2.size(); i++)
				{
					str[s++] = str2[i];
				}
				// f 移动到str1 左边第一个位子，准备查下一轮循环检查新字符
				f -= str1.size();
			}
		}else
		{
			str[s++] = str[f++]; 
		}
	}
}


//								 		Advanced Topic
// 1 string shuffle
// 1.1 first direction
// 				A1B2C3D4E5    			->    ABCDE12345
// 		A1B2C3 				D4E5
//	A1B2 		C3 		D4 		E5
// A1 	B2 	   C   3 	   
// A 1	B 2
//====================
// A1 	B2
// 	  A1B2    C3
//		ABC123  		DE45
//				ABCDE12345

// init left = 0 right = str.size
// merge sort
string stringShuffle1(const string& str)
{
	return mergeSortStringShuffle(str, 0, str.size() - 1)
}
string mergeSortStringShuffle(const string& str, int left, int right)
{
	if(left == right)
	{
		return str[left];
	}

	int mid = left + (right - left) / 2;
	string substr1 = mergeSortStringShuffle(str, left, mid);
	string substr2 = mergeSortStringShuffle(str, mid + 1, right);
	return merge(substr1, substr2);
}
// A 1 2 			B C 3
//   ni			        nj
// A  		B  C 			
//   ci		cj	 nj
// A B C				
// 1 2		3
// ni		nj
string merge(const string& str1, const string& str2)
{
	string result;
	// find the start index of number
	int ni = 0;// str1 on the right of ni, inlucde ni, is '0...9'
	int nj = 0;// str2 on the right of nj, inlucde nj, is '0...9'
	while(ni < str1.size() && str1[ni] > '9')
	{
		ni++;
	}
	while(nj < str2.size() && str1[nj] > '9')
	{
		nj++;
	}

	// merge char
	int ci = 0;
	int cj = 0;
	while(ci < ni && cj < nj
		&& str1[ci] > '9' && str2[c2] > '9')
	{
		if(str1[ci] < str2[cj])
		{
			result += str1[ci++];
		}else
		{
			result += str2[cj++];
		}	
	}
	if(ci < ni && str1[ci] > '9')
	{
		result += str1.substr(ci, ni - ci);
	}
	if(cj < nj && str2[c2] > '9')
	{
		result += str2.substr(cj, nj - cj);
	}

	// merge number
	while(ni < str1.size() && nj < str2.size())
	{
		if(str1[ni] < str2[nj])
		{
			result += str1[ni++];
		}else
		{
			result += str2[nj++];
		}	
	}
	if(ni < str1.size())
	{
		result += str1.substr(ni, str1.size() - ni);
	}
	if(nj < str2.size())
	{
		result += str2.substr(nj, str2.size() - nj);
	}
	return result;
}




// 1 string shuffle
// 1.2 second direction
// ABCD1234 -> A1B2C3D4 (in place)
// AB | CD | 12 | 34
// AB | DC | 21 | 34 
// AB | 12 | CD | 34
// AB12 | CD34
// A | B | 1 | 2	| 	C | D | 3 | 4
// A1 | B2
// A B C | C D E F | 1 2 3 | 4 5 6 7
// l.      lm.       m.      rm.   r

void convert(string& s, int left, int right)
{
	if(right - left <= 1) 
	{
		return;
	}
	int left = 0;
	int leftmid = left + s.size()* 1 / 4;
	int mid = left + s.size() / 2;
	int rightmid = left + s.size() * 3 / 4;
	int right = s.size(); 

	// I love yahoo trick
	Reverse(s, leftmid, mid-1);
	Reverse(s, mid, rightmid-1);
	Reverse(s, leftmid, rightmid-1);

	// 二分
	convert(s, left, left + 2*(leftmid - left) - 1);
	convert(s, left + 2*(leftmid - left), right);
}
void Reverse(string& s, int l, int r)
{
	if(l >= r)
	{
		return;
	}
	swap(s, l, r);
	l++;
	r--;
	Reverse(s, l, r);
}


// 												2 String Permutation

// Q2.1 no duplicate letters in input string, permutation
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
		// 交换第level个元素后面的所有元素到level位置, 包括level自己也要和自己交换一次
		swap(S[level], S[i]);
		stringPermutationDFS(S, level + 1, results);
		swap(S[level], S[i]);
	}
}
// time: n + n(n-1) + n(n-1)(n-2) + ...n!



// Q2.2 duplicate char, string permutation
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

	// 去重复
	unordered_set<char> set_to_dedup;
	for(int i = level; i < S.size(); i++)
	{
		if(!set_to_dedup.count(S[i]))
		{
			set_to_dedup.insert(S[i]);
			// 交换第level个元素后面的所有元素到level位置, 包括level自己也要和自己交换一次
			swap(S[level], S[i]);
			stringPermutationDFS(S, level + 1, results);
			swap(S[level], S[i]);
		}
	}
}


// 										3 String Encoding
// aaaaazbbbwcc
// a5z1b3w1c2
void stringEncoding(string& str)
{
	int s = 0; // slow pointer
	int j = 0; // fast point
	int n = str.size();
	int count_unique = 0; // how many unique char
	int count_repeat = 1; // 重复的char的重复次数

	// step 1: 1.1 计算unique的char 的个数 1.2 移动非unique的char
	while(j < n)
	{
		// 处理unique char开头，      中间, 结尾
		// w bb			bb w cc 		bb w
		// j 			   j 			   j
		if( (j == 0 && s[j] != s[j+1]) ||
			(str[j] != str[j-1] && str[j] != str[j+1]) ||
			(j == n - 1 && s[j] != s[j-1]) )
		{
			f++;
			count_unique++;
			continue;
		}

		// 非unique char
		// aaa b 		a5aaazbbb
		// j 			  s   j
		// s
		str[s++] = str[j++];
		// aaa b 		a5baazbbb
		//  j 			   s   j
		//  s
		while(j < n && str[j] == str[j - 1])
		{
			j++;
			count_repeat++;
		}
		// aaa b
		//     j
		//  s
		str[s++] = count_repeat;
		// a5a b
		//     j
		//   s
	}

	// step2 2.1reserve more counter_unique space 
	//		 2.2 从后向前 快慢指针

	// a5 z b3 w c2|bwcc
	//			    s 	j
	str.reserve(s + counter_unique);
	j = s-1;
	s += counter_unique - 1;
	while(j >=0 )
	{
		// a5 z b3 w c2|bw
		//			  j  s
		while(j >= 0 || isNumber(str[j]))
		{
			str[s--] = str[j--];
			str[s--] = str[j--];
		}
		str[s--] = 1;
		str[s--] = str[j--];
	}
}
bool isNumber(char c)
{
	return c <='9' && c >='1';
}




// 						Q4 sliding window in a string
// 4.1 longest substring that contains only unique char
// flow up 换成没有重复k次，把下面的1换成k 就好了
string FindLongest(const string& str)
{
	unordered_map<char, int> hash_map;
	int s = 0;
	int global_max = 0; 
	int global_start = 0;
	int global_end = 0;

	for(int f = 0; f < str.size(); f++)
	{
		// add the curretn element to hash table
		hash_map[str[f]]++;
		if(hash_map[str[f]] > 1) // if current is find duplicate char
		{
			while(hash_map[str[f]] > 1)// move slow pointer
			{
				hash_map[str[s]]--;
				s++;
			}
		}else // 没有重复
		{
			if(global_max < global_end - global_start + 1) // 当前长度是否比gloabl_max 长
			{
				global_max = global_end - global_start + 1;
				global_start = s;
				global_end = f;
			}
		}
	}

	return str.substr(s, global_end - global_start + 1);
}



// 4.2 anagrams 内容相同， 顺序不同
// s2 = aabc
// s1 = zzzzcde bcaa bcyywww
// 用一个hash_table 记录s2信息，滑动窗口不断--，信息全为0，match == 0 即匹配到了
vector<string> findAnagrams(const string& s1, const string& s2)
{
	unordered_map<char, int> hash_map;
	int match = s1.size();
	for(auto it : s1)
	{
		hash_map[it]++;
	}

	int s = 0;
	int f = 0;
	// init zzzz
	for(f = 0; f < s1.size(); f++)
	{
		if(hash_map.count(s2[f]))
		{
			int pre = hash_map[s2[f]];
			hash_map[s2[f]]--;
			int cur = hash_map[s2[f]];
			if(pre == 1 && cur == 0)
			{
				match--;
			}
		}
		if(match == 0)
		{
			result.push_back(s1.substr(s, f - s + 1));
		}
	}

	// zzzzcde bcaa bcyywww
	// s  f
	while(f < s1.size())
	{
		// 看slow指针，当前char 在s2中，
		if(hash_map.count(s2[s]))
		{
			int pre = hash_map[s2[s]];
			hash_map[s2[s]]++;
			int cur = hash_map[s2[s]];
			if(pre == 0 && cur == 1)
			{
				match++;
			}
		}
		s++;
		f++;
		// 看fast指针，当前char在s2中，
		if(f < s1.size() && hash_map.count(s2[f]))
		{
			int pre = hash_map[s2[f]];
			hash_map[s2[f]]--;
			int cur = hash_map[s2[f]];
			if(pre == 1 && cur == 0)
			{
				match--;
			}
		}
		// 全部match到
		if(match == 0)
		{
			result.push_back(s1.substr(s, str2.size()))
		}
	}
	return result;
}


// Q4.3 0-1 array , flip at most k times, 0->1
// find the longest subarray consisof 1 after fip
// 找包含最多k个1的字串
void flipKZero(vector<int>& A, int k)
{
	// 01000101010
	//  s
	//        f
	int s = 0; 
	int f = 0;
	int global_start = 0; 
	int global_end = 0;
	int count0 = 0;// 多少个0
	int global_len = 0; // sliding windows长度
	while(f < A.size())
	{
		//新来一个数是0，count加上
		if(A[f] == 0)
		{
			count0++;
		}
		// 
		if(count0 <= k)
		{
			f++;
		}else if(count0 > k)
		{
			if(A[s] == 0)
			{
				count0--;
			}
			s++;	
		}
		if(global_len < f - s )
		{
			global_len = f - s;
			global_start = s;
			global_end = f - 1;
		}
	}
	vector<int> result(A.begin() + s + 1, A.beign() + f);
	return result;
}




































































