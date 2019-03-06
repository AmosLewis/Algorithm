Node* cloneGraph(Node* node) {
    if(node == nullptr)
    {
        return node;
    } 
    queue<Node*> Q;
    Q.push(node);
    // 用一个hash_map建立原图与当前图之间的映射关系
    unordered_map<Node*, Node*> my_map;
    Node* new_node = new Node;
    new_node->val = node->val;
    my_map[node] = new_node;

    while(!Q.empty())
    {
        Node* cur = Q.front();
        Q.pop();

        for(const auto& it : cur->neighbors)
        {
            // 这个点还没有访问过， hash表中没有
            if(!my_map.count(it))
            {
                Q.push(it);
                Node* new_node = new Node;
                new_node->val = it->val;
                my_map[it] = new_node; 
            }
            my_map[cur]->neighbors.push_back(my_map[it]);
        }
    }
    return new_node;
}

// DFS1 
Node* cloneGraph(Node* node) {
    unordered_map<Node*, Node*> my_map; // [node,clone of node]
    return helper(node, my_map);
}

Node* helper(Node* node, unordered_map<Node*, Node*>& my_map)
{
    if(!node) 
    {
        return node;
    }
    // 已经克隆过，所以node及其所有邻居都已经都clone好了,放在my_map[node]里面
    if(my_map.count(node))
    {
        return my_map[node];//已经clone过了，直接已经clone好的返回
    }
    // 没有clone过，新建一个node
    Node* new_node = new Node;
    new_node->val = node->val;
    // 记录已经clone过当前节点
    my_map[node] = new_node;
    
    for(const auto& it : node->neighbors)
    {
        new_node->neighbors.push_back(helper(it, my_map));
    }
    return new_node;
}
