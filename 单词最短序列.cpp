// 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：

// 每一对相邻的单词只差一个字母。
//  对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
// sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0 。

 
// 示例 1：

// 输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// 输出：5
// 解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
// 示例 2：

// 输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
// 输出：0
// 解释：endWord "cog" 不在字典中，所以无法进行转换。
 

// 提示：

// 1 <= beginWord.length <= 10
// endWord.length == beginWord.length
// 1 <= wordList.length <= 5000
// wordList[i].length == beginWord.length
// beginWord、endWord 和 wordList[i] 由小写英文字母组成
// beginWord != endWord
// wordList 中的所有字符串 互不相同

#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
using namespace std;

class Solution {
public:
    bool can_convert(string str1, string str2)
    {
        if(str1 == str2)
            return false;
        int diff = 0;
        for(int i = 0; i < str1.size(); ++i)
        {
            if(str1[i] != str2[i])
                diff++;
            if(diff > 1)
                return false;
        }
        return true;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<int>> graph(wordList.size(), vector<int>(wordList.size(), INT_MAX));
        vector<int> begin_nodes;
        bool end_in_list = false;
        int end_index = -1;
        //construct graph
        for(int i = 0; i < wordList.size(); ++i)
        {
            graph[i][i] = 0;
            if(can_convert(beginWord, wordList[i]))
                begin_nodes.push_back(i);
            if(endWord == wordList[i])
                end_index = i;
            for(int j = i+1; j < wordList.size(); ++j)
            {
                if(can_convert(wordList[i], wordList[j]))
                {
                    graph[i][j] = 1;
                    graph[j][i] = 1;
                }
            }
        }
        if(end_index < 0)
            return 0;
        //floyd
        vector<vector<int>> dist(graph);
        for(int k = 0; k < wordList.size(); ++k)
        {
            for(int j = 0; j < wordList.size();++j)
            {
                for(int i = j+1; i < wordList.size(); ++i)
                {
                    if(dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        dist[j][i] = dist[i][j];
                    }
                }
            }
        }
        //choose min
        int res = INT_MAX;
        for(auto begin_index:begin_nodes)
        {
            res = min(dist[begin_index][end_index], res);
        }
        
        return res < INT_MAX? (res+2) : 0;
    }
};



//深度优先遍历
class Solution {
public:
    bool can_convert(string str1, string str2)
    {
        if(str1 == str2)
            return false;
        int diff = 0;
        for(int i = 0; i < str1.size(); ++i)
        {
            if(str1[i] != str2[i])
                diff++;
            if(diff > 1)
                return false;
        }
        return true;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        set<string> word_set(wordList.begin(), wordList.end());
        if(word_set.find(endWord) == word_set.end())
            return 0;
        queue<string> internals;
        internals.push(beginWord);
        int layer_num = 0;
        bool find_end = false;
        while(!internals.empty())
        {
            int cur_layer_num = internals.size();
            for(int i = 0; i < cur_layer_num; ++i)
            {
                string front_str = internals.front();
                internals.pop();
                auto ite = word_set.begin();
                while(ite != word_set.end())
                {  
                    string str = *ite;
                    if(can_convert(front_str, str))
                    {
                        if(str == endWord)
                            return layer_num + 2;
                        internals.push(str);
                        ite = word_set.erase(ite);
                        continue;
                    }
                    ite++;
                }
            }
            layer_num++;
        }
        return 0;
    }
};