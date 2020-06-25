#include "../../head.h"


class Solution {
public:
    std::string minWindow(std::string const & s, std::string const & t) {
        std::string res(s + t);
        int start = 0;
        std::unordered_map<char, int> target;
        for (char const c : t) {
            target[c]++;
        }
        std::unordered_map<char, int> visited;
        for (int index = 0; index < s.size(); index++) {
            // std::cout << "\nvisit: " << s[index] << "\t";
            visited[s[index]]++;

            bool flag = true;
            for (auto const & tPair : target) {
                if (tPair.second > visited[tPair.first]) {
                    flag = false;
                }
            }
            while (flag) {
                std::string curRes = s.substr(start, index - start + 1);
                if (curRes.size() < res.size()) {
                    res = curRes;
                }
                visited[s[start++]]--;
                for (auto const & tPair : target) {
                    if (tPair.second > visited[tPair.first]) {
                        flag = false;
                    }
                }
            }
        }
        return res == (s + t) ? "" : res;

    }

    std::string minWindowUpgrade(std::string const & s, std::string const & t) {
        std::string res;
        int resLen = INT_MAX;
        int start = 0;
        std::unordered_map<char, int> target;
        for (char const c : t) {
            target[c]++;
        }
        std::unordered_map<char, int> visited;
        for (int index = 0; index < s.size(); index++) {
            // std::cout << "\nvisit: " << s[index] << "\t";
            visited[s[index]]++;

            bool flag = true;
            for (auto const & tPair : target) {
                if (tPair.second > visited[tPair.first]) {
                    flag = false;
                }
            }
            while (flag) {
                if (index - start + 1 < resLen) {
                    res = s.substr(start, index - start + 1);
                    resLen = res.size();

                }
                visited[s[start++]]--;
                for (auto const & tPair : target) {
                    if (tPair.second > visited[tPair.first]) {
                        flag = false;
                    }
                }
            }
        }
        return res;

    }
};

auto ii = [](){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  return 0;
} ();

class SolutionBetterRunTime {
public:
    string minWindow(std::string const & s, std::string const & t) {
      int size = s.size();
      int needed = t.size();
      if (needed > size) {
          return "";
      }

      int freq[128] = {};
      for (const auto & c : t) {
          freq[c]++;
      }

      int prev = 0;
      int start = -1;
      int len = INT_MAX;
      int count = 0;
      for (int i = 0; i < size; i++) {
        char c = s[i];
        freq[c]--;
        if (freq[c] >= 0) {
          count++;
        }
        while (count == needed) {
          char p = s[prev];
          freq[p]++;
          if (freq[p] > 0) {
            int l = i - prev + 1;
            count--;
            if (l < len) {
              start = prev;
              len = l;
            }
          }
          prev++;
        }
      }

      if (start == -1) {
          return "";
      }
      return s.substr(start, len);
    }
};
