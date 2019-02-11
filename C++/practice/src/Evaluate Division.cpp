class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        // 这题naive的方法就是用DFS，有向图，
        // 每个string是node, value是 edge, A->B = 2 B->A = 1/2
        // 对有向图DFS，开始深搜任何一个节点时，新建一个set记录已经被搜过的点
        // DFS中，如果被搜过就跳过
        
        // 建立有向图
        unordered_map<string, unordered_map<string, double>> g;
        for(int i = 0; i < equations.size(); i++)
        {
            const string& A = equations[i].first;
            const string& B = equations[i].second;
            const double k = values[i];
            g[A][B] = k;
            g[B][A] = 1.0/k;
        }
        
        // 范围值
        vector<double> results;
        // 遍历查询数组，对每一堆query计算返回值
        for(const auto& q : queries)
        {
            const string& A = q.first;
            const string& C = q.second;
            // 找不到这俩string
            if(!g.count(A) || !g.count(C))
            {
                results.push_back(-1.0);
                continue;
            }
            
            // 正常情况，push深搜的结果
            unordered_set<string> visited;
            results.push_back(divide(A, C, g, visited));// A/C
        }
        return results;
    }
    
    // get result of A/C
    double divide(const string& A, const string& C, 
                  unordered_map<string, unordered_map<string, double>>& g,
                  unordered_set<string>& visited)
    {
        // 终止条件,找到俩都在map中
        if(g[A].count(C)) return g[A][C];
        // 标记A已经访问过
        visited.insert(A);
        // 下面对A的邻居深搜
        for(const auto& pair : g[A])
        {
            const string& B = pair.first;
            //如果该点深搜过了，说明这个点后面没有符合条件的点，就不搜了，换下一个点
            if(visited.count(B)) continue;
            // 如果没有访问过，找 B->C的路径
            double d = divide(B, C, g, visited); // d = g[B][C]
            // d > 0说明有这个路径
            if(d > 0) return g[A][B] * d;// g[A][B] * g[B][C]
        }
        return -1.0;
    }
    
};








