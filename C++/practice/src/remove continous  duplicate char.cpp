// remove all continous duplicate char
// i start from 0
// i 的左侧不包含i,都是要被返回的值
// case1 stack empty, 
// push str[i] i++
// a b b b b a a d e 
// i
// 
// case2 stack not empty , str[i] != stack.top, 
// push str[i], i++
// a b b b b a a d e 
//   i
// a
// case 3, stack not empty, str[i] == stack.top 
// loop i++ until str[i] != stack.top, 
// loop 结束，stack pop_back 
// a b b b b a a d e 
//     i
// a b
// case 3, stack not empty, str[i] == stack.top 
// loop i++ until str[i] != stack.top, 
// loop 结束，stack pop_back
// a b b b b a a d e 
//           i
// a 
// case 1, stack empty, 
// push str[i] i++
// a b b b b a a d e 
//             i
//  
// case 2, stack not empty, push str[i] != stack.top() 
// push str[i], i++
// a b b b b a a d e 
//               i
// a
// 显然case1 case 2可以合并
// 先处理case3 ,剩下的就是case12

// 方法一 显示用一个stack
void removeDuplicatesContinous(string& str)
{
	if(str.size() < 2)
	{
		return str;
	}
	// 建立一个栈
	// 为什么用vector实现stack,因为下面有个把stack 放回string中
	// 如果一只用insert(0), 时间复杂度是O(n^2)
	vector<char> st;
	int i = 0;
	// 遍历所有元素
	while(i < str.size)
	{
		// 取出当前的char， 用于循环比较重复的char
		char c = s[i];
		// 栈不空，栈顶的元素等于当前的元素
		if(st.size() > 0 && st.back() == str[i])
		{
			while(i < str.size() && c == str[i])
			{
				i++;
			}
			// 把栈顶的重复元素给弹出
			st.pop_back();
		}else // case1 st.size == 0, case2 st.size>0 st.back != str[i]
		{
			// 压新的元素
			st.push_back(str[i]);
			i++;
		}
	}
	// 清空s, 等待复制
	s.clear();
	// 复制stack中结果到s
	for(int j = 0; j < st.size(); j++)
	{
		s += st[j];
	}
}

// 方法2 快慢指针，Implicitly use a stack
// s 的左侧包含s 是要返回的元素，
// s 可以想象成stack顶，满足条件(A[s]!=A[f]）一直向右移动s++, j++
// A[s]==A[f] 一直++f到 A[s]!=A[f],再向左移动i，i--
//  s < 0 栈空
//  a b b b a c  s = -1 (s++, A[s] = A[f]) 这就是一个push_back, f++
//s
//  f

//  s >= 0 栈不空
//  a b b b a c  A[f]!=A[s] (s++, A[s] = A[f]) 这就是一个push_back, f++
//  s
//    f
//  a b b b a c  A[f]==A[s] loop f++ until A[f]!=A[s]
//    s
//      f
//  a b b b a c  s-- 进入下一次大循环中栈不空操作
//    s
//          f

//  s >= 0 栈不空
//  a b b b a c  A[f]==A[s] loop f++ until A[f]!=A[s]
//  s
//          f
//  a b b b a c  s-- 进入下一次大循环中栈空操作
// s
//            f




string removeDuplicatesContinous(string& str)
{
	if(str.size() < 2)
	{
		return str;
	}
	int s = -1; 
	int f = 1;
	while(f < str.size())
	{
		char c = s[f];
		if(s == -1)// 栈空
		{
			s++;
			str[s] = s[f++];
		}else // s!=0 栈非空
		{
			if(str[s] == str[f])// s!=0 栈非空， 且发现重复元素
			{
				while(f < str.size() && str[s] == str[f]) // 去掉所有重复元素(跳出重复的元素)
				{
					f++;// f++ 可能会越界，所以while上面一定要加上 f < str.size()
				}
				s--;// 弹栈，因为栈顶是已经被发现的重复的元素，所以要删掉
			}else //s!=0 栈非空，且新元素与栈顶不同，压栈。 
			{
				// (s,f)是已经跳过去的重复元素，可以当作空，随便插入
				// 如果 s,f相邻，虽然有0个跳过的元素，但是则str[f] = str[f]，f放在自己的位子上，也没有问题 
				s++;
				str[s] = str[f++];
			}
		}
	}
	str.resize(s + 1);
}
// 上面这个程序显然可以被优化，if语句之中包含相同的part,可以合并
string removeDuplicatesContinous(string& str)
{
	if(str.size() < 2)
	{
		return str;
	}
	int s = -1; 
	int f = 1;
	while(f < str.size())
	{
		char c = s[f];
		if(s == -1 || str[s] != str[f])// 栈空 压栈/ 栈不空，且新元素与栈顶不同，压栈
		{
			// (s,f)是已经跳过去的重复元素，可以当作空，随便插入
			// 如果 s,f相邻，虽然有0个跳过的元素，但是则str[f] = str[f]，f放在自己的位子上，也没有问题 
			s++;
			str[s] = s[f++];
		}else //if(i >= 0 && str[s] == str[f])// s!=0 栈非空， 且发现重复元素
		{
			while(f < str.size() && str[s] == str[f]) // 去掉所有重复元素(跳出重复的元素)
			{
				f++;// f++ 可能会越界，所以while上面一定要加上 f < str.size()
			}
			s--;// 弹栈，因为栈顶是已经被发现的重复的元素，所以要删掉
		}
	}
	str.resize(s + 1);
}
