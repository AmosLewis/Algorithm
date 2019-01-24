/*
Sentence screen fitting
Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

Note:

A word cannot be split into two lines.
The order of words in the sentence must remain unchanged.
Two consecutive words in a line must be separated by a single space.
Total words in the sentence won't exceed 100.
Length of each word is greater than 0 and won't exceed 10.
1 ≤ rows, cols ≤ 20,000.
Example 1:

Input:
rows = 2, cols = 8, sentence = ["hello", "world"]

Output: 
1

Explanation:
hello---
world---

The character '-' signifies an empty space on the screen.
Example 2:

Input:
rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

Output: 
2

Explanation:
a-bcd- 
e-a---
bcd-e-

The character '-' signifies an empty space on the screen.
Example 3:

Input:
rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

Output: 
1

Explanation:
I-had
apple
pie-I
had--

The character '-' signifies an empty space on the screen.


time O(rows * word length)
space O(number of characters in the reformatted sentence) = O(number of words * word length)
Reformatted sentence
["ab", "cde", "f"] --> "ab cde f " 构造新字符，单词中间加 ‘ ’
count: how many characters of the reformatted sentence is on the screen
count % length of reformatted sentence: the starting position of the next row
Answer: count / length of reformatted sentence
length: 9
count = (3 + 4 + 5 + 4 + 5) / 9 = 2
row 5
col 4
ab cde f ab cde f ab cde f....
XXX     //开始放满整行，放四个XXXX，检查下一个字符 next_row_start_index = count % n,这是下一行的起始位置，
        //发现起始位置是一个字符，可能是单词中间，循环后退一格, --count,变XXX，直到找到前一个数为‘ ’，起始位置还是停留‘ ’后面一个字母
   XXXX// 发现下一行起始位置是‘ ’， 因为‘ ’可以不作为起始位置，所以向后再移动一个位置 ++count
       XXXXX
            XXXX
                XXXXX
                
                  
*/


class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        // 构造新字符，每个单词后面加 ‘ ’， 注意，这里最后一个单词后面也有‘ ’
        string s;
        for (const auto& sen: sentence) {
            s += sen;
            s += " ";
        }
        
        int count{0}; // 同时表示可以放置的总的字符个数，也可以用count %n 表示下一行的起始位置
        int n = s.size(); // 获得新的字符串的长度
        for (int i = 0; i < rows; ++i) { // 循环遍历没一行，对没一行尝试插满，行就++，不行就循环--
            count += cols;// 开始放满整行
            if (s[count % n] == ' ') { // 检查下一行的起始位置,是‘ ’
                ++count;//发现下一行起始位置是‘ ’， 因为‘ ’可以不作为起始位置，所以向后再移动一个位置
            } else { // 不是‘ ’，即是字母‘a-z’
                while (count > 0 && s[(count - 1) % n] != ' ') // 检查前一个位置，也不是‘ ’，说明起始位置再单词中间，循环退回到单词起始位置
                    --count;// 循环退回单词起始字符，再重新计算下一行开始位置
            }
        }
        
        return count / n; // count 表示放的总的字符个数，n是字符串的总长，整除就可以得到位子大小
    }
};
