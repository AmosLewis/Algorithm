// remove particular char in string
// fast slow
// remove u n
// s t d e u u n t
//         i
//             j
// slow: i, all the letters that not equal to u/n, put on the lefthand side of i,[not include i]
// fast: j, current index, iteration all the letters, if j not euqual to u/n, copy j to i, i++, 而j始终++
// (i, j] we don't care, XXX, 
// (j, size-1] area to explore 
// 慢指针为什么会慢，是因为必须在满足某些条件的情况下才可以++，所以i一定包含在某个if条件语句里面

string removeletters(string& input)
{
	int i = 0;// slow
	int j = 0;// fast

	while(j < input.size())
	{
		if(input[j] == 'u' || input[j] == 'n')
		{
			j++;
		}else
		{
			input[i++] = input[j++];
		}
	}

	// resize the original string to the new size
	input.resize(i); 
	return input;
}
