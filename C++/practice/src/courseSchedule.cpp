/*
There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:

Input: 2, [[1,0]] 
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
*/

// DFS
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        // O(n)
        // 用index 表示课程ID，创建邻接表，第二项表示child课程
        graph_ = vector<vector<int>>(numCourses);
        // 用index 表示课程ID， 创建记录访问状态的矩阵 0 not visit, 1 visiting, 2 visited 
        vector<int> status(numCourses, 0); 
        
        for(const auto& it : prerequisites) // 用&可以不用对原数组拷贝一份tmp， const 表示不修改原数组
        {
            int parent_ID = it.second;
            int child_ID = it.first;
            graph_[parent_ID].push_back(child_ID);
        }
        // 深搜邻接表表
        for(int i = 0; i < graph_.size(); i++)
        {
            if(dfsAdajecentGraph(status, i)) // 如果找到环，返回false
            {
                return false;
            };
        }
         return true;// 图DFS完了还没有找到环返回，就返回true
    }
private:
    // 用index 表示课程ID，创建邻接表，第二项表示child课程
    vector<vector<int>> graph_;    
    // 如果找到图返回ture
    bool dfsAdajecentGraph(vector<int>& status, int& id)
    {
        if(status[id] == 1) return true; // 访问到正在访问的点，有环，返回true
        if(status[id] == 2) return false; // 该点已经访问过了，没环，跳过；
        
        // 该节点正在访问
        status[id] = 1; 
        for(auto it: graph_[id])
        {
            if(dfsAdajecentGraph(status, it)) return true;
        }
        
        
        status[id] = 2; // 该节点访问完了
        return false;
    }
};

// 
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        // BFS 
        // 目标是，从所有入度为0的所有点出发，遍历完BFS所有节点以后，
        // 再次遍历入度数组，只有入度全部为0才表示没有环，入度大于0就有环
        
        // 创建一个邻接表，数组ID表示课程号， 每一行表示子课程
        graph_ = vector<vector<int>>(numCourses);
        // 创建一个入度表，数组ID表示课程号，每一行表示对应节点入度
        vector<int> degrees(numCourses, 0);
        
        queue<int> Q;
        // 遍历输入对，构造邻接表，入度数组
        for(const auto& it: prerequisites)
        {
            // 获得课程依赖关系索引ID
            int parentID = it.second;
            int childID = it.first;
            // 构造邻接表
            graph_[parentID].push_back(childID);
            // 构造入度数组,【注意】 是对孩子++
            degrees[childID]++;
        }
        
        // 遍历一次入度数组，向Q中插入入度为0的点
        for(int ID = 0; ID < numCourses; ID++)
        {
            if(degrees[ID] == 0)
            {
                Q.push(ID);
            }
        }
        
        while(!Q.empty())
        {
            int parentID = Q.front();
            Q.pop();
            
            for(const auto& childID: graph_[parentID])
            {
                // 【注意】是对孩子--
                degrees[childID]--;
                if(degrees[childID] == 0)
                {
                    Q.push(childID);
                }
            }
            
        }
        
        // 遍历每个节点的入度，如果有非0值，则有环
        for(const auto& degree: degrees)
        {
            if(degree != 0)
            {
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<int>> graph_;
};
