#include "../../head.h"\n\n\n

class Solution {
public:
	std::string longestSubsequenceRepeatedK(std::string const & s, int k) {
		// plagiarizing from https://leetcode.com/problems/longest-subsequence-repeated-k-times/discuss/1474122/Insights-and-Optimizations and
		// https://leetcode.com/problems/longest-subsequence-repeated-k-times/discuss/1471930/Python-Answer-is-not-so-long-explained and
		// https://leetcode.com/problems/longest-subsequence-repeated-k-times/discuss/1472073/Easy-to-Read-Short-25-Lines-C%2B%2B-(With-Comments)

		std::array<int, LOWERCASE_CNTS> cnts;
		for (char c : s) {
			// accumulate the cnt of each letter
			++cnts[c - LOWERCASE_LETTER_START];
		}
		std::string validChars;
		for (int idx = LOWERCASE_CNTS - 1; idx > MOST_LEFT_BOUNDARY_EXCLUDE; idx--) {
			validChars += std::string(cnts[idx] / k, static_cast<char>(LOWERCASE_LETTER_START + idx));
		}
		std::string ans;
		dfsGenerate(s, validChars, std::string() = {}, ans, 0, k);
    }

private:
	void dfsGenerate(std::string const & s,
			std::string const & validChars,
			std::string const & cur,
			std::string & ans,
			int usedMask,
			int k) {
		for (int idx = 0; idx < validChars.size(); idx++) {
			if (0 == (usedMask & (1 << idx))) {
				// the letter has not been used
				std::string newCur = cur + validChars[idx];
				if (check(s, newCur, k)) {
					if (newCur.size() > ans.size()) {
						ans = newCur;
					}
					dfsGenerate(s, validChars, newCur, ans, usedMask | (1 << idx), k);
				}
			}
		}
	}

	bool check(std::string const & s,
			std::string const & cur,
			int k) {
		int const curSize = cur.size();
		for (int idx = 0, curIdx = 0; idx < s.size() && 0 < k; idx++) {
			curIdx += (cur[curIdx] == s[idx]);
			if (curIdx == curSize) {
				curIdx = 0;
				k--;
			}
		}
		return 0 == k;
	}


private:
	static int const LOWERCASE_CNTS = 26;
	static char const LOWERCASE_LETTER_START = 'a';
	static char const MOST_LEFT_BOUNDARY_EXCLUDE = -1;
};
