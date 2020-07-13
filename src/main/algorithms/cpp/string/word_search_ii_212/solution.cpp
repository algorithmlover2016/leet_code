#include "../../head.h"


class Solution {
public:
    int nRows;
    int nCols;
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
                                       std::vector<std::string> const & words) {
        nRows = board.size();
        nCols = board[0].size();

        std::vector<std::string> res;
        for (auto const & word : words) {
            bool find = false;
            for (int i = 0; i < nRows; ++i) {
                for (int j = 0; j < nCols; ++j) {
                    if(find = solve(board, i, j, 0, word)) {
                        res.emplace_back(word);
                        break;
                    }
                }
                if (find) {
                    break;
                }
            }

        }
        return res;
    }
    bool solve(std::vector<std::vector<char>> & board, int i, int j, int w, const std::string & word) {
        
        char ch = board[i][j];
        if(ch != word[w]) {
            return false;
        }
            
        board[i][j] = '$';
        ++w;
        if (w == word.length()) {
            board[i][j] = ch;
            return true;
        }

        bool solved = false;
        //Left
        if (j > 0)
            solved = solve(board, i, j - 1, w, word);
        //Right
        if (!solved && j < nCols - 1)
            solved = solve(board, i, j + 1, w, word);
        //Up
        if (!solved && i > 0)
            solved = solve(board, i - 1, j, w, word);
        //Down
        if (!solved && i < nRows - 1)
            solved = solve(board, i + 1, j, w, word);

        board[i][j] = ch;

        return solved;
    }
};

class Solution {
private:

    //Trie INSERT
    void insert(std::string const & s) {
        node *curr = root;
        int index, i=0;
        while(s[i]) {
            index = s[i] - 'a';
            if(curr->child[index]==NULL) {
                curr->child[index] = getNode(s[i]);
            }
            curr = curr->child[index];
            i += 1;
        }
        curr->ends += 1; // means words have repeat word
        curr->word = s;
    }

    void solve(std::vector<std::vector<char>>& board,
            int i, int j, int r, int c,
            std::vector<std::string> & ans, node *curr) {
        //Base case
        //If the trie doesn't have the current char OR cell is Visited
        int index = board[i][j] - 'a';
        if(board[i][j] == '$' || curr->child[index]==NULL) {
            return;
        }

        curr = curr->child[index];
        if(curr->ends > 0) {
            ans.push_back(curr->word);
            curr->ends -=1;
        }

        //Body
        char ch = board[i][j];   //Store current char
        board[i][j] = '$';  //Mark current node visited

        if(i > 0)     //TOP
            solve(board, i - 1, j, r, c, ans, curr);
        if(i < r - 1)   //DOWN
            solve(board, i + 1, j, r, c, ans, curr);
        if(j > 0)     //LEFT
            solve(board, i, j - 1, r, c, ans, curr);
        if(j < c - 1)   //RIGHT
            solve(board, i, j + 1, r, c, ans, curr);

        board[i][j] = ch;    //Mark current node as Unvisited by restoring the value
    }

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>> & board, std::vector<std::string> const & words) {
        int r = board.size();
        int c = board[0].size();

        //Insert all words in TRIE
        for(int i = 0;i < words.size(); ++i) {
            insert(words[i]);
        }

        //Now search words
        std::vector<std::string> ans;
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j) {
                solve(board, i, j, r, c, ans, root);
            }
        }
        return ans;
    }
private:
    struct node {    //TrieNode
        char c;
        int ends;
        string word;
        node *child[26];
    };

    struct node *getNode(char c) {    //get newnode
        node *newnode = new node;
        newnode->c = c;
        newnode->ends = 0;
        newnode->word = "";
        for(int i = 0; i < 26; ++i) {
            newnode->child[i] = NULL;
        }
        return newnode;
    }
    node *root = getNode('/');  //root
};


static int fastio = []() {
    #define endl '\n'
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(0);
    return 0;
}();
