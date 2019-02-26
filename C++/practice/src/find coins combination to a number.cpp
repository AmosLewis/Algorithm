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
		findCoins(money_left - coins[level], coins, level + 1, counts);
		// counts[level] = 0; 没必要在 这步还原成parent状态，，因为下一次循环会直接覆盖这个值，这是同一层操作
		// 另外一只写法是对counts 不初始化，而是先count.push_back(i), DFS后再count.pop_back(i)恢复父亲状态
	}
}
