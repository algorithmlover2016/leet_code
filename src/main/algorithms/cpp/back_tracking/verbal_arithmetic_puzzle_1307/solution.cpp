#include "../../head.h"


class Solution {
public:
    bool isSolvable(std::vector<std::string> words, std::string result) {
        // plagiarizing from https://leetcode.com/problems/verbal-arithmetic-puzzle/discuss/463916/C%2B%2B-12ms-DFS-and-Backtracking-and-Prunning-Strategy
        limitLen = result.size();
        for (std::string & word : words) {
            if (word.length() > limitLen) {
                return false;
            }
            std::reverse(word.begin(), word.end());
        }
        std::reverse(result.begin(), result.end());
        return backTracking(words, result, 0, 0, 0);
    }
    bool backTracking(std::vector<std::string> const & words,
            std::string const & result,
            int idxWord, int idxVec, int sum) {
        // at the last column of the result
        if (idxWord == limitLen) {
            return sum == 0;
        }

        // at the most right, should compute the sum at idxWord position
        if (idxVec == words.size()) {
            int remainder = sum % 10;
            if (c2i.find(result[idxWord]) == c2i.end() &&
                    i2c.find(remainder) == i2c.end()) {
                // avoid set the first letter of result to zero
                if (0 == remainder && idxWord + 1 == limitLen) {
                    return false;
                }
                // the letter and number pair has not been used.
                c2i[result[idxWord]] = remainder;
                i2c[remainder] = result[idxWord];
                bool tmp = backTracking(words, result, idxWord + 1, 0, sum / 10);
                c2i.erase(result[idxWord]);
                i2c.erase(remainder);
                return tmp;
            } else if (c2i.find(result[idxWord]) != c2i.end() &&
                    // because we always set c2i and i2c at same time. no need to judge
                    // i2c.find(remainder) != i2c.end() &&
                    c2i[result[idxWord]] == remainder) {
                if (idxWord + 1 == limitLen && 0 == remainder) {
                    return false;
                }
                return backTracking(words, result, idxWord + 1, 0, sum / 10);
            } else {
                return false;
            }
        }

        if (idxWord >= words[idxVec].length()) {
            return backTracking(words, result, idxWord, idxVec + 1, sum);
        }

        if (c2i.find(words[idxVec][idxWord]) != c2i.end()) {
            // already set <letter, num> pair, make sure that the first letter in a word is not zero
            if (idxWord + 1 == words[idxVec].length() &&
                    1 < words[idxVec].length() && // if only has one letter in a word, it can be zero
                    0 == c2i[words[idxVec][idxWord]]) {
                return false;
            }
            return backTracking(words, result, idxWord, idxVec + 1, sum + c2i[words[idxVec][idxWord]]);
        }

        // if have not set the pair <letter, num>, try to set it
        for (int num = 0; num < 10; num++) {
            // can't be already used
            if (i2c.find(num) != i2c.end()) {
                continue;
            }
            // first letter in a word whose length is greater than 1, can not be zero
            if (idxWord + 1 == words[idxVec].length() &&
                    1 < words[idxVec].length() && // if only has one letter in a word, it can be zero
                    0 == num) {
                continue;
            }
            // set pair
            c2i[words[idxVec][idxWord]] = num;
            i2c[num] = words[idxVec][idxWord];
            bool tmp = backTracking(words, result, idxWord, idxVec + 1, sum + num);
            c2i.erase(words[idxVec][idxWord]);
            i2c.erase(num);
            if (tmp) {
                return true;
            }
        }
        return false;

    }

private:
    int limitLen;
    std::unordered_map<int, char> i2c;
    std::unordered_map<char, int> c2i;
};


class SolutionUpperUpdate {
    // chracter to digit mapping, and the inverse
	// (if you want better performance: use array instead of unordered_map)
    unordered_map<char, int> c2i;
    unordered_map<int, char> i2c;
	// limit: length of result
    int limit = 0;
	// digit: index of digit in a word, widx: index of a word in word list, sum: summation of all word[digit]  
    bool helper(std::vector<std::string> const & words, std::string const & result, int digit, int widx, int sum) { 
        if (digit == limit) {
            return 0 != c2i[result[digit - 1]] && sum == 0;
        }
		// if summation at digit position complete, validate it with result[digit].
        if (widx == words.size()) {
            if (c2i.count(result[digit]) == 0 && i2c.count(sum%10) == 0) {
                // if (sum%10 == 0 && digit+1 == limit) // Avoid leading zero in result
                //     return false;
                c2i[result[digit]] = sum % 10;
                i2c[sum%10] = result[digit];
                bool tmp = helper(words, result, digit+1, 0, sum/10);
                c2i.erase(result[digit]);
                i2c.erase(sum%10);
                return tmp;
            } else if (c2i.count(result[digit]) && c2i[result[digit]] == sum % 10){
                return helper(words, result, digit+1, 0, sum/10);
            } else {
                return false;
            }
        }
		// if word[widx] length less than digit, ignore and go to next word
        if (digit >= words[widx].length()) {
            return helper(words, result, digit, widx+1, sum);
        }
		// if word[widx][digit] already mapped to a value
        if (c2i.count(words[widx][digit])) {
            if (digit+1 == words[widx].length() && words[widx].length() > 1 && c2i[words[widx][digit]] == 0) 
                return false;
            return helper(words, result, digit, widx+1, sum+c2i[words[widx][digit]]);
        }
		// if word[widx][digit] not mapped to a value yet
        for (int i = 0; i < 10; i++) {
            if (digit+1 == words[widx].length() && i == 0 && words[widx].length() > 1) continue;
            if (i2c.count(i)) continue;
            c2i[words[widx][digit]] = i;
            i2c[i] = words[widx][digit];
            bool tmp = helper(words, result, digit, widx+1, sum+i);
            c2i.erase(words[widx][digit]);
            i2c.erase(i);
            if (tmp) return true;
        }
        return false;
    }
public:
    bool isSolvable(std::vector<std::string> words, std::string result) {
        limit = result.length();
        for (auto &w: words) 
            if (w.length() > limit) 
				return false;
        for (auto&w:words) 
            reverse(w.begin(), w.end());
        reverse(result.begin(), result.end());
        return helper(words, result, 0, 0, 0);
    }
};

class SolutionTLE {
public:
    bool isSolvable(std::vector<std::string> const & words, std::string const & result) {
        // plagiarizing from https://leetcode.com/problems/verbal-arithmetic-puzzle/discuss/463953/Java-Fast-Backtracking-Clean-Code-O(n!)-~-300ms
        std::set<char> nonLeadingZero;
        std::set<char> seenChar;
        std::unordered_map<char, int> charCnt;
        for (std::string const & word : words) {
            int const wordSize = word.size();
            for (int index = 0; index < wordSize; index++) {
                if (0 == index && 1 < wordSize) {
                    nonLeadingZero.emplace(word[index]);
                }
                charCnt[word[index]] += POW_10[wordSize - index - 1];
                seenChar.emplace(word[index]);
            }
        }

        int const resultSize = result.size();
        for (int index = 0; index < resultSize; index++) {
            if (0 == index && 1 < resultSize) {
                nonLeadingZero.emplace(result[index]);
            }
            charCnt[result[index]] -= POW_10[resultSize - index - 1];
            seenChar.emplace(result[index]);
        }

        std::vector<bool> used(10, false);
        std::vector<char> charList;
        for (std::set<char>::iterator it = seenChar.begin(); it != seenChar.end(); it++) {
            charList.emplace_back(*it);
        }
        return backTracking(charCnt, charList, nonLeadingZero, used, 0, 0);
    }
private:
    bool backTracking(std::unordered_map<char, int> & charCnt,
            std::vector<char> const & charList,
            std::set<char> const & nonLeadingZero,
            std::vector<bool> & used,
            int const step,
            int diff) {
        if (step == charList.size()) {
            return 0 == diff;
        }
        for (int num = 0; num < 10; num++) {
            char c = charList[step];
            // first letter in a word or result can't be zero;
            if (used[num] || (0 == num && nonLeadingZero.find(c) != nonLeadingZero.end())) {
                continue;
            }
            used[num] = true;
            if (backTracking(charCnt, charList, nonLeadingZero, used, step + 1, charCnt[c] * num + diff)) {
                return true;
            }
            used[num] = false;
        }
        return false;
    }
private:
    // becuase std::max(result.size() == 7)
    static std::array<int, 7> const POW_10;
};
std::array<int, 7> const Solution::POW_10 = {1, 10, 100, 1000, 10000, 100000, 1000000};
