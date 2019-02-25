// 								isBipatite
class GraphNode
{
	int val;
	char flag;
	vector<GraphNode*> sucessor;
}

bool isBipatite(vector<GraphNode*>& graph)
{
	// BFS graph, init the first node as 'v'
	// set successor as 'u'
	// set sucessor's sucessor as 'v'
	// if find conflict,return false
	for(auto & it:graph)
	{
		it->flag = 'a'; // this node has not set to u/v
	}

	queue<GraphNode*> q;
	graph[0]->flag = 'u';
	q.push(graph[0]);
	char help = 'u' + 'v';

	while(!q.empty())
	{
		GraphNode* curnode = q.top();
		q.pop();

		for(auto& it : curnode->sucessor)
		{
			if(it->flag == 'a')// 子节点没有设置过，设置
			{
				it->flag = help - curnode->flag;
			}else if(help - curnode->flag != it->flag) // 已经设置过两次设置的冲突
			{
				return false;
			}
			q.push(it);
		}
	}
	return true;
}
