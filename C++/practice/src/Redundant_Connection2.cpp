class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        // union find
        // 时间复杂度 (Time Complexity) O(nlog*n) ~ O(n), 
        // 空间复杂度 (Space Complexity) O(n)
        
        // 存每个顶点的parents，这样就可以判断有没有重复的parent
        // 用于第一次循环找出重复的parents
        // +1 是因为题中说 N nodes (with distinct values 1, 2, ..., N),
        vector<int> parents(edges.size() + 1, 0);
        
        // union set 中会用到的俩数据结构
        // 用于第二次循环做union find
        vector<int> roots(edges.size() + 1, 0);
        // 每个union_set包含的的nodes 个数
        vector<int> sizes(edges.size() + 1, 1);
        
        // 存俩candicates,俩父节点，必须要删掉一个
        vector<int> ans1; 
        vector<int> ans2; 
        
        // 检查一个子node是否有俩parents
        for(auto& edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            
            if(parents[v] == 0) // 第一次遇到v
            {
                // 更新（记录）当前的node v的parents是u，
                parents[v] = u;
            }else //(parents[v] > 0) // v 已经有过一个parent， 即v 被找到过一次
            {
                // 存储两条candidate边， 后面必须要删除一条
                ans1 = {parents[v], v}; // 1,3
                ans2 = edge;// 2,3
                
                //先标记第二条边为不访问，为后面的操作if(u < 0 || v < 0) continue; 铺垫
                edge[0] = edge[1] = -1;
            }
            
        }
        
        // union set 查找环，做法与第一问一样
        for(const auto& edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            
            // Invalid edge，因为前面有 edge[0] = edge[1] = -1;
            // 所以u v 可能 == -1
            // 跳过重复的第二条边
            if(u == -1 || v == -1) continue; 
            
            // 如果该node还没有父node,父为自己， 
            // union find 标准操作
            if(!roots[u]) roots[u] = u;
            if(!roots[v]) roots[v] = v;
            int pu = find(u, roots);
            int pv = find(v, roots);
            
            // u,v在同一个tree中两个叶子node, 且彼此有连接，说明构成【环】
            if(pu == pv)
            {
                // ans1空，说明没有重复的parents，edge即第一条构成环的边， 与第一问相同 case1
                // ans1非空，因为之前已经删掉了第二条ans2，现在依然有环，只能是ans1, 那么返回第一条ans1 case2.2
                return ans1.empty() ? edge : ans1;
            }
            
            // 合并小的到大的里面
            if(sizes[pv] > sizes[pu])
            {
                swap(pv, pu);
            }
            roots[pv] = pu;
            sizes[pu] += sizes[pv];
        }
        
        // 两重含义，
        // 1. 这环由ans2构成, 只是之前已经删除俩ans2,所以并查时候没找到环 case2.2 去4->2,加4->3
        // 2. Case2.1 没有发现环，有俩父母 2,3
        return ans2;
    }
    
    int find(int node, vector<int>& parents)
    {
        while(parents[node] != node)
        {
            parents[node] = parents[parents[node]];// 压缩路径
            node = parents[node];
        }
        return node;
    }
};
