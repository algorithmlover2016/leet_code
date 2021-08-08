#include "../../head.h"


// #define DEBUG
class Solution {
public:
        std::vector<std::string> removeInvalidParentheses(std::string const & s) {
                // reference to https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/Easy-Short-Concise-and-Fast-Java-DFS-3-ms-solution
                std::vector<std::string> ans;
                dfsHelper(s, 0, 0, LeftToRightParenthese, ans);
                return ans;
    }
pirvate:
		void dfsHelper(std::string s,
				int curIdx,
				int nextRmIdx,
				std::vector<char> const & parentheses,
				std::vector<std::string> & ans) {
			for (int misMatch = 0, idx = curIdx; idx < s.size(); idx++) {
				if (s[idx] == parentheses[FirstParenthesesIdx]) {
					misMatch++;
				} else if (s[idx] == parentheses[SecondParenthesesIdx]){
					misMatch--;
				}
				if (misMatch >= 0) {
					continue;
				}
				for (int tryRmIdx = nextRmIdx; tryRmIdx <= idx; tryRmIdx++) {
					if (s[tryRmIdx] == parentheses[SecondParenthesesIdx] && (
								tryRmIdx == nextRmIdx || s[tryRmIdx - 1] != parentheses[SecondParenthesesIdx])
					   ) {
#ifdef DEBUG
						std::cout << s.substr(0, tryRmIdx) + s.substr(tryRmIdx + 1) << "\n";
#endif
						dfsHelper(s.substr(0, tryRmIdx) + s.substr(tryRmIdx + 1), idx, tryRmIdx, parentheses, ans);
					}
				}
				return;

			}
			std::reverse(s.begin(), s.end());
			if (parentheses[FirstParenthesesIdx] == LeftToRightParenthese[FirstParenthesesIdx]) {
				dfsHelper(s, 0, 0, RightToLeftParenthese, ans);
			} else {
				ans.emplace_back(s);
			}

		}
private:
		static int const FirstParenthesesIdx = 0;
		static int const SecondParenthesesIdx = 1;
		static std::vector<char> const LeftToRightParenthese;
		static std::vector<char> const RightToLeftParenthese;
};
std::vector<char> const Solution::LeftToRightParenthese{'(', ')'};
std::vector<char> const Solution::RightToLeftParenthese{')', '('};
