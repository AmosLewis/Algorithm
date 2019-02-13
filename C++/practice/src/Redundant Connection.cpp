class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // 法1 DFS
        // 将图中是否有环，转化成对每一对新的顶点，是否graph中已经存在另一条路径链接起来
        // 即在每插入新边之前，先对新边的一个顶点u做一次DFS看是否能找到另外一个节点v
        // 建一个无向图
        unordered_map<int, vector<int>> graph;
        // 遍历每一条边
        for(const auto& edge : edges)
        {
            // 取出每一对顶点
            int u = edge[0];
            int v = edge[1];
            
            // 定义一个 hash_set记录已经访问过(DFS)的点
            // 访问过则不用访问，说明后面的点没有满足条件的
            // 注意这个是对每一条边都重新申请一次，而不是全局的
            unordered_set<int> visited;
            // 查找是否graph中已经存在一条u->v的路径
            // 如果存在，则加上这条新的uv就构成环了
            if(hasPath(u, v , graph, visited))
            {
                // 那么返回这个uv
                return edge;
            }
            
            // 如果没有找到从u-v 的路径，那么在途中插入u-v
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        // 遍历完所有的边都没有找到环，就返回空
        return {};
    }
    
private:
    bool hasPath(int curr, const int goal, const unordered_map<int, vector<int>>& graph,
                 unordered_set<int>& visited)
    {
        // 当前节点已经到达goal了, 邻居中有goal, 说明找到一条路径了，返回true
        if(curr == goal) return true;
        // 标记当前node已经访问(DFS)了
        visited.insert(curr);
        //剪枝，如果graph中没有curr/goal，不用查找，一定没有路径，直接false
        if(!graph.count(curr) || !graph.count(goal))
        {
            return false;
        }
        
        // 遍历当前节点的所有邻居，DFS
        for(const auto& it : graph.at(curr))
        {
            // 如果当前邻居已经访问过，则跳过
            if(visited.count(it)) continue;
            // 如果邻居中找到goal，it == goal则返回有，
            // 如果邻居没有goal , 就对邻居的邻居深搜
            if(hasPath(it, goal, graph, visited)) return true;
            // 该点的邻居，已经邻居的邻居，以及邻居的邻居的邻居。。。搜完了，
            // 结束，搜下一个点
        }
        
        // 如对所有邻居深搜也没有找到goal, 说明此路不通
        return false;  
    }
};


class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // 法2 并查集
        // 表示某个元素的父节点，
        vector<int> parents(edges.size() + 1, 0);
        
        // 表示某个根节点上一共有多少个元素
        vector<int> sizes(edges.size() + 1, 1);
        
        
        for(const auto& edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            // 没有父节点，就指向自己
            if(!parents[u]) parents[u] = u;
            if(!parents[v]) parents[v] = v;
            // 查找u,v的根节点
            int pu = find(u, parents);
            int pv = find(v, parents);
            
            // 如果 u,v 根相同, 说明在同一个union set里面
            if(pu == pv) return edge;
            
            // 如果连个父节点不同，把小的那个接入大的后面
            // 把小的size定义为pv
            if(sizes[pv] > sizes[pu])
            {
                swap(pu, pv);
            }
            
            // 把小的union_set的父节点指到大的union_set的父节点
            parents[pv] = pu;
            // 指完之后要更改大的union_set的大小， 加上小的
            sizes[pu] += sizes[pv];
        }
        
        return {};
    }
    
    int find(int node, vector<int>& parents)
    {
        // 只有根节点的父亲是自己，如果不满足条件，就循环
        // 使用node 保存root
        while(node != parents[node])
        {
            // 当前node 的父节点变成他的祖父节点
            parents[node] = parents[parents[node]]; 
            // 当前node 移动到祖父节点，相当于跳两格
            node = parents[node];
        }
        return node;
    }

};
