//http://www.cnblogs.com/grandyang/p/6006000.html
class Solution {
public: 
    class TrieNode
    {
    public:
        vector<int> wordsID;
        vector<TrieNode*> children;
        TrieNode(): children(26, nullptr){}
        ~TrieNode()
        {
            for(auto it : children)
            {
                if(it) delete it;
            }
        }
    };
    class Trie{
    public:
        Trie(): root_(new TrieNode()){}
        // 根据words构建完整Trie树
        void insert(vector<string>& words)
        {
            for(int i = 0; i < words.size(); i++)
            {
                // 每次插入新string,要重新将指针知道Trie的root
                TrieNode* t = root_.get();
                for(const char c : words[i])
                {
                    // 该char没有遇到过，new一个新的node
                    if(!t->children[c - 'a']) 
                    {
                        t->children[c - 'a'] = new TrieNode();
                    }
                    // 指针向下移动，指到刚刚新建的node上
                    t = t->children[c - 'a'];
                    // 记录该前缀是由那些单词经过，用于后面的查找递归
                    t->wordsID.push_back(i);
                }
            }
        }
        
    public: 
        unique_ptr<TrieNode> root_; 
    };
    
    vector<vector<string>> wordSquares(vector<string>& words) {
        // 新建一个Trie对象
        Trie m_trie;
        m_trie.insert(words);
        
        // 保存一个满足条件的结果， 中间量
        vector<string> result(words[0].size());
        // 保存所有满足条件的结果
        vector<vector<string>> results;
        for(int i = 0; i < words.size(); i++)
        {
            // 尝试把每一个单词都当成第一行，然后开始深搜
            result[0] = words[i];
            // 递归深搜，逐步填满result
            help(m_trie, words, result, 1, results);
        }
        
        return results;
    }
    
    void help(Trie& m_trie,                         // 自己构建的Trie树
              vector<string>& words,                // 原始输入string数组
              vector<string>& result,               // 一个符合条件的结果
              int ID,                               // 处理result 的第ID行，去第ID列的字符组单词
              vector<vector<string>>& results       // 所有符合条件的结果
             )
    {
        // 当越过result的高度
        if(ID == words[0].size())
        {
            results.push_back(result);  // 只在这里用到results
            return;
        }
        
        string prefix = "";
        // 取出第ID列作为该行前缀
        for(int i = 0; i < ID; i++)
        {
            prefix += result[i][ID];
        }
        
        // t 找到prefix末尾的c的指针
        TrieNode* t = m_trie.root_.get();
        for(const auto& c : prefix)
        {
            // 以该prefix开头的其他word 不存在，
            // 直接跳出递归，尝试result[ID]处放其他word用于找新prefix
            if(!t->children[c - 'a']) return;
            t = t->children[c - 'a'];
        }
        
        // 遍历所有满足prefix条件的word
        for(int index : t->wordsID)
        {
            // 逐一尝试每个满足前缀的string，迭代放入result的第ID行，会不断覆盖前一次结果
            result[ID] = words[index]; 
            help(m_trie, words, result, ID + 1, results);
        }
        
    }
    
};
