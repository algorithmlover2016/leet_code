#include "../../head.h"


class SolutionStackOverFlow {
public:
    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string> const & words) {
        std::vector<std::string> res;
        if (2 > words.size()) {
            return res;
        }
        int minStrSize = INT_MAX;
        std::set<std::string> allELes;
        for (auto const & ele : words) {
            int eleSize = ele.size();
            if (eleSize < minStrSize) {
                minStrSize = eleSize;
            }
            allELes.emplace(ele);
        }

        for (std::string const & ele : words) {
            if (dfsHelper(ele, allELes, minStrSize, true)) {
                res.emplace_back(ele);
            }
        }
        return res;
    }

    bool dfsHelper(std::string const & ele, std::set<std::string> const & allELes, int const minStrSize, bool const isSelf) {
        if (ele.empty()) {
            return true;
        } else if (ele.size() < minStrSize) {
            return false;
        }

        // std::cout << "\n ele: " << ele << "\t";
        for (int index = minStrSize; index <= ele.size(); index++) {
            // std::cout << "judge: " << ele.substr(0, index) << "\t";
            if (index == ele.size() && isSelf) {
                return false;
            }
            if (allELes.find(ele.substr(0, index)) != allELes.end()) {
                // std::cout << "next " << ele.substr(index) << "\t";
                if (dfsHelper(ele.substr(index), allELes, minStrSize, false)) {
                    return true;
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string> const & words) {
        // plagiarizing from  https://leetcode.com/problems/concatenated-words/discuss/95652/Java-DP-Solution
        // and https://leetcode.com/problems/concatenated-words/discuss/95652/Java-DP-Solution/220383
        std::vector<std::string> res;
        if (2 > words.size()) {
            return res;
        }
        std::set<std::string> dicts;
        int minEleSize = INT_MAX;
        for (auto const & ele : words) {
            int eleSize = ele.size();
            if (eleSize < INT_MAX) {
                minEleSize = eleSize;
            }
            dicts.emplace(ele);
        }
        for (auto const & ele : words) {
            dicts.erase(ele);
            if (dfsHelper(ele, dicts, minEleSize)) {
                res.emplace_back(ele);
            }
            dicts.emplace(ele);
        }
        return res;
    }

    bool dfsHelper(std::string const & ele, std::set<std::string> const & dicts, int const minEleSize = 1) {
        std::vector<bool> dp(ele.size() + 1, false);
        dp[0] = true;
        for (int len = minEleSize; len <= ele.size(); len++) {
            for (int index = len - 1; index >= 0; index--) {
                std::string extractStr = ele.substr(index, len);
                if (extractStr == ele) {
                    continue;
                }
                if (!dp[index]) {
                    continue;
                }
                if (dicts.find(extractStr) != dicts.end()) {
                    dp[index] = true;
                    break;
                }
            }
        }
        return dp[ele.size()];
    }
};

class SolutionAlmostTLE {
public:
    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string> const & words) {
        // plagiarizing from  https://leetcode.com/problems/concatenated-words/discuss/95652/Java-DP-Solution
        // and https://leetcode.com/problems/concatenated-words/discuss/95652/Java-DP-Solution/220383
        std::vector<std::string> res;
        if (2 > words.size()) {
            return res;
        }
        std::set<std::string> dicts;
        int minEleSize = INT_MAX;
        for (auto const & ele : words) {
            int eleSize = ele.size();
            if (eleSize < minEleSize) {
                minEleSize = eleSize;
            }
            dicts.emplace(ele);
        }
        for (auto const & ele : words) {
            if (ele.empty()) {
                continue;
            }
            dicts.erase(ele);
            if (dfsHelper(ele, dicts, minEleSize)) {
                res.emplace_back(ele);
            }
            dicts.emplace(ele);
        }
        return res;
    }

    bool dfsHelper(std::string const & ele, std::set<std::string> const & dicts, int const minEleSize = 1) {
        std::vector<bool> dp(ele.size() + 1, false);
        dp[0] = true;
        // std::cout << "\njude: " << ele << '\t' << minEleSize << "\t";
        for (int len = minEleSize; len <= ele.size(); len++) {
            for (int index = len - minEleSize; index >= 0 ; index--) {
                if (!dp[index]) {
                    continue;
                }
                std::string extractStr = ele.substr(index, len - index);
                // std::cout << "index: " << index << "\tsub: " << extractStr << "\t";
                if (dicts.find(extractStr) != dicts.end()) {
                    dp[len] = true;
                    break;
                }
            }
        }
        // std::cout << dp[ele.size()] << "\t";
        return dp[ele.size()];
    }
};

class Solution {
    Node *head;

    class Node{
    public:
        char c;
        bool word;
        Node * next, *child; // next-> next elem, child->iska baccha.
        Node(char c_) : word(false), c(c_), next(nullptr), child(nullptr) {
        }

        bool isWord() {
            return word;
        }

        void setWord(){
            word = 1;
        }
    };
    void insert(Node ** head, const string & w) {
        Node **q=head;
        Node *p=nullptr;
        for (const auto &c : w) {
            // We'll go by every letter.
            for (p = *q; p ;p = p->next) {
                if(p->c == c)
                    break;
                q = &p->next; // This is making q=next elem of p's location.
            }
            if (p==nullptr) {
                // If we don't find it.
                p = new Node(c);
                *q = p; // this made q=p
            }
            q = & p->child; // q is pointing to p ka child.
        }
        if (p != nullptr) {
            p->setWord(); // ?
        }
    }
    bool helper(Node *head,const string &w,int idx,int words){
        if(idx>=w.length() && words>1)
            return 1;
        // Agar word end hogya aur word is made by more than 2 words, toh it is concat.
        int sz=w.length();
        Node *p=head;
        for(int i=idx;i<sz;i+=1){
            while(p!=nullptr){
                if(p->c==w[i])
                    break;
                p=p->next;
            }
            if(p==nullptr) // Not Found
                return 0;
            if(p->isWord()){
                if(helper(head,w,i+1,words+1))
                    return 1;
            }
            p=p->child;
        }
        return 0;
    }
    public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
        head=nullptr;
        for(const auto &x:words){
            if(x.empty()) continue;
            insert(&head,x);
        }
        vector<string> ans;
        for(const auto &x:words){
            if(x.empty()) continue;
            if(helper(head,x,0,0))
                ans.push_back(x);
        }
        return ans;
    }
};

class SolutionMaybeEasyUnderstand {
public:
    Solution() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
    }
    struct Node {
        std::array<Node*, 26 > _c {nullptr};
        bool stop {false};
    };
    Node _root;
    void fill(std::string const & w ) {
        Node* node = &_root;
        int c = w.size();
        for ( int i = 0 ; i < c ; ++i ) {
            int idx = w[i] - 'a';
            if (not node->_c[idx] ) {
                node->_c[idx] = new Node();
            }
            node = node->_c[idx];
            if (i == c - 1) {
                node->stop = true;
            }
        }
    }
    bool find( string const & w, Node* node, int j, int cnt ) {
        int c = w.size();
        for (int i = j ; i < c ; ++i) {
            int idx = w[i] - 'a';
            if (not node->_c[idx]) {
                return false;
            }
            node = node->_c[idx];
            // every time we find the end of word
            if (node->stop) {
                if (i == c - 1) {
                    return cnt + 1 > 1;
                }
                // restart the search from the root
                if (find( w, &_root, i + 1, cnt + 1)) {
                    return true;
                }
            }
        }
        return false;
    }
    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string>& words) {
        if (words.size() < 2)
            return std::vector<std::string>();

        // build trie
        for (auto const & w : words)
            fill(w);

        std::vector<std::string> result;
        // check each word against trie
        for (auto const & w : words)
            if (find(w, &_root, 0, 0))
                result.push_back(w);
        return result;
    }
};
