/*
https://www.youtube.com/watch?v=K8Nk0AiIX4s
*/
class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        // nlog(n)
        // 用一个set，依次insert每个花的current_slot
        // 因为set是BST实现的，所以它是有序的
        // 每一个set中的元素，是可以拿到指针iterator的 
        // pair<iterator, bool> = set.insert
        // 每insert之后，取到iterator, ++/--得到刚好>/<花的slot的指针
        // 判断是否 == current_slot + k +1 / == current_slot - k -1;
        
        int num_flowers = flowers.size();
        if(num_flowers == 0 || num_flowers <= k) return -1;
        
        // 用一个set，依次insert每个花的current_slot，存放有序
        set<int> slots;
        
        for(int day = 0; day < num_flowers; day++)
        {
            // 当前花的slot地址
            int current_slot = flowers[day];
            // 每一个set中的元素，是可以拿到指针iterator的,先当作连续k个slot的左边界
            // 则下面即将要检查它右边的元素是否满足条件
            auto left = slots.insert(current_slot).first; // log(n)
            auto right = left;
            
            // end()表示最后一个元素的下一位，left+1 不在set末尾的下一个元素，即left不在set末尾，
            // 即left 不是set 中最大的数，则检查 left+1 是否满足条件
            // [                          left, left++] end()
            // log(n)
            if(++left != slots.end() && *left == current_slot + k + 1) return day + 1;
            // [begin()/right--, right                ] end()
            if(right != slots.begin() && *(--right) == current_slot - k - 1) return day + 1;
        }
        
        return -1;
        
    }
};

class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        // v3: O(n)
        // bucket 思想
        // 把花分成每k+1个位置为一个bucket
        // 只记录每个bucket 的MAX 和 MIN 值
        // 每进来一个数，比较与MAX 和 MIN的关系
        // == MIN 则检查后一个bucket的MIN (边界检查 bucketID > 0)
        // bucket 0 [ MIN          ...      MAX(cur-k-1) ] // k+1个slot
        // bucket 1 [ MIN(cur)     ...              MAX  ] // k+1个slot
        // bucket 2 [ MIN          ...              MAX  ] // k+1个slot
        // == MAX 则检查前一个bucket的MAX (边界检查 bucketID < num_buckets - 1)
        // bucket 0 [ MIN          ...               MAX ] // k+1个slot
        // bucket 1 [ MIN          ...          MAX(cur) ] // k+1个slot
        // bucket 2 [ MIN(cur+k+1) ...               MAX ] // k+1个slot
        //           [min_array]              [max_array]
        // 实际没有显式定义bucket，而是只对其用MAX MIN分别建立数组，大大压缩空间复杂度
        
        int num_flowers = flowers.size();
        if( 0 == num_flowers && k > num_flowers) return -1;
        

        // 因为后面只用到了k+1 所以索性这里直接加上了
        ++k;
        // 把花分成每k+1个位置为一个bucket
        // 只记录每个bucket 的MAX 和 MIN 值
        int num_buckets = (num_flowers + k - 1) / k; 
        vector<int> max_array(num_buckets, INT_MIN);
        vector<int> min_array(num_buckets, INT_MAX);
        
        for(int i = 0; i < num_flowers; i++)
        {
            // 获取当前花的地址
            int current_slot = flowers[i];
            // 获取当前或应该在哪一个bucket 　里面
            int bucket_index = current_slot / k;
            
            // == MIN 则检查后一个bucket的MIN (边界检查 bucketID > 0)
            if(current_slot < min_array[bucket_index])
            {
                min_array[bucket_index] = current_slot;
                if(bucket_index > 0 && max_array[bucket_index - 1] == current_slot - k)
                {
                    return i + 1;
                }
            }
            
            // == MAX 则检查前一个bucket的MAX (边界检查 bucketID < num_buckets - 1)
            if(current_slot > max_array[bucket_index])
            {
                max_array[bucket_index] = current_slot;
                if(bucket_index < num_buckets -1 && min_array[bucket_index + 1] == current_slot + k)
                {
                    return i + 1;
                }
            }
            
        }

        return -1;
    }
};
