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
        // 用index 表示课程ID，创建邻接表，第二项(vector每一行)表示child课程ID
        graph_ = vector<vector<int>>(numCourses);
        // 用index 表示课程ID， 创建每个课程ID的访问状态的矩阵 0 not visit, 1 visiting, 2 visited 
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
        if(status[id] == 1) return true; // 访问到正在访问过的点，有环，返回true
        if(status[id] == 2) return false; // 该点已经访问过了，没环，跳过；
        
        // 设置该节点状态为正在访问
        status[id] = 1; 
        for(auto it: graph_[id]) // 遍历该父节点的所有子节点
        {
            if(dfsAdajecentGraph(status, it)) return true;
        }
        
        
        status[id] = 2; // 该节点访问完了
        return false;
    }
};















