#include "../../head.h"


class SolutionWrongAnswer {
public:
    std::vector<int> findSubstring(std::string const & s, std::vector<std::string> const & words) {
        std::vector<int> res;
        int cnt = words.size();
        int wordLen = 0;
        std::unordered_map<string, int> visited;
        for (std::string const & word : words) {
            visited[word]++;
            wordLen = word.size();

        }
        int start = 0;
        for (int index = 0; index < s.size() - wordLen; index++) {
            std::string cur = s.substr(index, wordLen);
            visited[cur]--;
            if (visited[cur] >=  0) {
                cnt++;
            } else {
                cnt = 0;
                visited[cur]++;
                for (; start < index - wordLen; start += wordLen) {
                    std::string preCur = s.substr(start, wordLen);
                    visited[preCur]++;
                }
            }
            if (cnt == words.size()) {
                res.emplace(start);
                cnt = 0;
                visited[cur]++;
                for (; start < index - wordLen; start += wordLen) {
                    std::string preCur = s.substr(start, wordLen);
                    visited[preCur]++;
                }
            }
        }
        return res;

    }
};

class Solution {
public:
    std::vector<int> findSubstring(std::string const & s, std::vector<std::string> const & words) {
        // plagiarizing from https://leetcode.com/problems/substring-with-concatenation-of-all-words/discuss/13658/Easy-Two-Map-Solution-(C%2B%2BJava)
        std::vector<int> indexes;
        if (words.empty() || s.empty()) {
            return indexes;
        }
        std::unordered_map<std::string, int> counts;
        for (string word : words) {
            counts[word]++;
        }
        int n = s.length(), num = words.size(), len = words[0].length();
        for (int i = 0; i < n - num * len + 1; i++) {
            std::unordered_map<string, int> seen;
            int j = 0;
            for (; j < num; j++) {
                std::string word = s.substr(i + j * len, len);
                if (counts.find(word) != counts.end()) {
                    seen[word]++;
                    if (seen[word] > counts[word])
                        break;
                } else {
                    break;
                }
            }
            if (j == num) {
                indexes.push_back(i);
            }
        }
        return indexes;
    }
};

// using sliding window to reduce repeat computation
class SolutionBetterRunTime {
public:
    std::vector<int> findSubstring(std::string const & s, std::vector<std::string> const & words) {
        if (s.size() == 0 || words.size() == 0) {
            return vector<int>();
        }
        int n = s.size(), m = words.size(), wz = words[0].size();
        int len = m * wz;
        size_t ghash = 0;
        for (int i = 0; i < words.size(); i++) {
            ghash += std::hash<std::string>{}(words[i]); // construct a hash object and call the operator();
        }

        std::vector<int> ans;
        for (int i = 0; i < wz; i++) {
            size_t thash = 0, cnt = 0;
            for (int j = i; j + wz <= n; j += wz) {
                if (++cnt < m) {
                    thash += std::hash<std::string_view>{}(std::string_view(&s[j], wz));
                    continue;
                }
                if (cnt > m) {
                    thash -= std::hash<std::string_view>{}(std::string_view(&s[j - len], wz));
                }

                thash += std::hash<std::string_view>{}(std::string_view(&s[j], wz));
                if (thash == ghash) {
                    ans.push_back(j - len + wz);
                }
            }
        }
        return ans;
    }
    std::vector<int> findSubstringEasyUnderstand(std::string const & s, std::vector<std::string> const & words) {
        if (s.size() == 0 || words.size() == 0) {
            return vector<int>();
        }
        int n = s.size(), m = words.size(), wz = words[0].size();
        int len = m * wz;
        size_t ghash = 0;
        for (int i = 0; i < words.size(); i++) {
            ghash += std::hash<std::string>{}(words[i]); // construct a hash object and call the operator();
        }

        std::vector<int> ans;
        for (int i = 0; i < wz; i++) {
            size_t thash = 0, cnt = 0;
            for (int j = i; j + wz <= n; j += wz) {
                // cnt++, we didn't add the new word into thash
                cnt++;
                thash += std::hash<std::string_view>{}(std::string_view(&s[j], wz));
                if (cnt < m) {
                    continue;
                }
                if (cnt > m) {
                    // remove the left word
                    thash -= std::hash<std::string_view>{}(std::string_view(&s[j - len], wz));
                }

                if (thash == ghash) {
                    ans.push_back(j - len + wz);
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
     // travel all the words combinations to maintain a window
    // there are wl(word len) times travel
    // each time, n/wl words, mostly 2 times travel for each word
    // one left side of the window, the other right side of the window
    // so, time complexity O(wl * 2 * N/wl) = O(2N)
    std::vector<int> findSubstring(std::string const & S, std::vector<std::string> const & L) {
        std::vector<int> ans;
        int n = S.size(), cnt = L.size();
        if (n <= 0 || cnt <= 0) return ans;

        // init word occurence
        std::unordered_map<std::string, int> dict;
        for (int i = 0; i < cnt; ++i) {
            dict[L[i]]++;
        }

        // travel all sub string combinations
        int wl = L[0].size();
        for (int i = 0; i < wl; ++i) {
            int left = i, count = 0;
            std::unordered_map<std::string, int> tdict;
            for (int j = i; j <= n - wl; j += wl) {
                std::string str = S.substr(j, wl);
                // a valid word, accumulate results
                if (dict.count(str)) {
                    tdict[str]++;
                    if (tdict[str] <= dict[str]) {
                        count++;
                    } else { // a more word, advance the window left side possiablly
                        while (tdict[str] > dict[str]) {
                            string str1 = S.substr(left, wl);
                            tdict[str1]--;
                            if (tdict[str1] < dict[str1]) {
                                count--;
                            }
                            left += wl;
                        }
                    }
                    // come to a result
                    if (count == cnt) {
                        ans.push_back(left);
                        // advance one word
                        tdict[S.substr(left, wl)]--;
                        count--;
                        left += wl;
                    }
                } else { // not a valid word, reset all vars
                    tdict.clear();
                    count = 0;
                    left = j + wl;
                }
            }
        }
        return ans;
    }
};
