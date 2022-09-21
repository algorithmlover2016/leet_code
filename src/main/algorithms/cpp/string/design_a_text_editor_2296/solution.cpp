#include "../../head.h"

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */

// #define DEBUG
class TextEditorTLE {
public:
    TextEditorTLE() : start(0) {
    }
    
    void addText(std::string const & text) {
        std::string tmp;
        tmp.append(content.substr(0, start)).append(text).append(content.substr(start));
        content = tmp;
        start += text.size();
        #ifdef DEBUG
        std::cout << __FUNCTION__ << " cur: " << content << ", index: " << start << "\n";
        #endif
    }
    
    int deleteText(int k) {
        k = std::min(k, start);
        std::string tmp;
        tmp.append(content.substr(0, start - k)).append(content.substr(start));
        start -= k;
        std::swap(tmp, content);
        #ifdef DEBUG
        std::cout << __FUNCTION__ << " cur: " << content << "\n";
        #endif
        return k;
    }
    
    std::string cursorLeft(int k) {
        k = std::min(k, start);
        #ifdef DEBUG
        std::cout << __FUNCTION__ << " move left " << k << " steps\n";
        #endif
        start -= k;
        int minLen = std::min(MIN_LEN, start);
        #ifdef DEBUG
        std::cout << __FUNCTION__ << " display " << minLen << " chars\n";
        #endif
        return content.substr(start - minLen, minLen);
    }
    
    std::string cursorRight(int k) {
        k = std::min(k, (int)content.size() - start);
        #ifdef DEBUG
        std::cout << "content size: " << content.size()  << ", " << start << "\n";
        std::cout << __FUNCTION__ << " move right " << k << " steps\n";
        #endif
        start += k;
        int minLen = std::min(MIN_LEN, start);
        #ifdef DEBUG
        std::cout << __FUNCTION__ << " display " << minLen << " chars\n";
        #endif
        return content.substr(start - minLen, minLen);
    }
private:
    constexpr int static MIN_LEN = 10;
    int start;
    std::string content;
};

class TextEditor {
public:
    TextEditor() {
        // plagiarizing from https://leetcode.com/problems/design-a-text-editor/discuss/2112623/Two-Strings
        // and https://leetcode.com/problems/design-a-text-editor/discuss/2111861/Using-Two-Stacks-or-C%2B%2B
    }

    void addText(std::string const & text) {
        left.append(text);
        // left.insert(left.end(), std::begin(text), std::end(text));
    }

    int deleteText(int k) {
        k = std::min(k, (int)left.size());
        // int ans = k;
        // while (k--) {
        //     left.pop_back();
        // }
        // return ans;
        left.resize(left.size() - k);
        return k;
    }

    std::string cursorLeft(int k) {
        k = std::min(k, (int)left.size());
        while (k--) {
            char c = left.back(); left.pop_back();
            right.push_back(c);
        }
        return left.substr(left.size() - std::min(MAX_LEN, (int)left.size()));
    }

    std::string cursorRight(int k) {
        k = std::min(k, (int)right.size());
        while (k--) {
            left.push_back(right.back());
            right.pop_back();
        }
        return left.substr(left.size() - std::min(MAX_LEN, (int)left.size()));
    }
private:
    std::string left, right;
    constexpr int static MAX_LEN = 10;        
};