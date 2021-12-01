#include "../../head.h"


// #define DEBUG
class SolutionRabinKarp {
public:
    std::string longestDupSubstring(std::string const & s) {
        // plagiarizing from https://leetcode.com/problems/longest-duplicate-substring/discuss/291048/C%2B%2B-solution-using-Rabin-Karp-and-binary-search-with-detailed-explaination

        std::string ans;
        int const sSize = s.size();

        // record the exponential factor
        powerIdx = std::vector<long long>(sSize, 1);
        for (int idx = 1; idx < sSize; idx++) {
            powerIdx[idx] = (powerIdx[idx - 1] * LOWCASE_LETTER_NUMS) % MOD;
        }

        int left = 0, right = sSize;
        while (left < right) {
            int mid = (left + right + 1) / 2;
            if (validate(mid, s, ans)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        #ifdef DEBUG
        std::cout << "MOD: " << MOD << "\n";
        std::cout << ans.size() << ", " << s.size() << "\n";
        #endif
        return ans;
    }
private:
    bool validate(int fixLen, std::string const & s, std::string & ans) {
        int const sSize = s.size();
        if (0 == fixLen) {
            ans = "";
            return true;
        }
        std::unordered_map<long long, std::vector<int>> hash = std::unordered_map<long long, std::vector<int>>();
        long long curHash = 0;
        int idx = 0;
        for (; idx < fixLen; idx++) {
            curHash = (curHash * LOWCASE_LETTER_NUMS + s[idx] - LOWCASE_LETTER) % MOD;
        }

        hash[curHash] = std::vector<int>(1, 0);

        for (idx = fixLen; idx < sSize; idx++) {
            // remove the left most letter
            curHash = ((curHash - powerIdx[fixLen - 1] * (s[idx - fixLen] - LOWCASE_LETTER)) % MOD + MOD) % MOD;
            // add one letter from the right most
            curHash = (curHash * LOWCASE_LETTER_NUMS + s[idx] - LOWCASE_LETTER) % MOD;

            if (hash.find(curHash) == hash.end()) {
                hash[curHash] = std::vector<int>(1, idx - fixLen + 1);
            } else {
                for (auto sameHashIdx : hash[curHash]) {
                    if (0 == strcmp(s.substr(sameHashIdx, fixLen).data(), s.substr(idx + 1 - fixLen, fixLen).data())) {
                        ans = s.substr(sameHashIdx, fixLen);
                        return true;
                    }
                }
                hash[curHash].emplace_back(idx + 1 - fixLen);
            }
        }
        return false;
    }

private:
    std::vector<long long> powerIdx;
    static long const MOD = (1L << 31) - 1; // can't set to (long)(1 << 31) - 1, this will be negative number -2147483649
    // static long const MOD = 2147483647;
    static int const LOWCASE_LETTER_NUMS = 26;
    static char const LOWCASE_LETTER = 'a';
};

// #define DEBUG
class Solution {
    // reference to https://leetcode.com/problems/longest-duplicate-substring/discuss/290852/Suffix-array-clear-solution
private:
    // reference to https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/
    class SuffixArray {
    private:
        static int const RANK_NUM = 2;
        static int const RANK_FIRST = 0;
        static int const RANK_SECOND = 1;

        struct Suffix {
            int idx;
            std::array<int, RANK_NUM> rank = {};
        };
    public:
        SuffixArray(std::string const & str_) : str(str_){
            buildSuffixArray(suffixIdxes);
            #ifdef DEBUG
            for (int idx = 0; idx < suffixIdxes.size(); idx++) {
                std::cout << suffixIdxes[idx] << ((idx == suffixIdxes.size() - 1) ? "\n" : "\t");
            }
            #endif
        }
        void kasai(std::vector<int> & mostLenLCP) {
            int const suffixIdxesSize = suffixIdxes.size();
            int const strSize = str.size();
            assert(suffixIdxesSize == strSize);

            mostLenLCP.resize(suffixIdxesSize);

            // similar to the array in buildSuffixArray
            std::vector<int> oriIdx2Order(suffixIdxesSize);

            for (int idx = 0; idx < suffixIdxesSize; idx++) {
                oriIdx2Order[suffixIdxes[idx]] = idx;
            }

            int mostLargestLen = 0;
            for (int idx = 0; idx < strSize; idx++) {
                if (oriIdx2Order[idx] == strSize - 1) {
                    // after sort by rank, the current idx suffix substring is the largest substr
                    mostLargestLen = 0;
                    continue;
                }
                int nextIdx = suffixIdxes[oriIdx2Order[idx] + 1];
                while ((idx + mostLargestLen < strSize) && (nextIdx + mostLargestLen < strSize) && (str[idx + mostLargestLen] == str[nextIdx + mostLargestLen])) {
                    mostLargestLen++;
                }
                mostLenLCP[idx] = mostLargestLen;
                if (0 < mostLargestLen) {
                    // this operation will lead to the most largest common prefix will be right.
                    // if we want to get the right lcp at each idx, we should set mostLargestLen to be zero, which will lead to ON2 time in worset time.
                    mostLargestLen--;
                }
            }
        }

    private:
        static bool cmp(struct Suffix const & left, struct Suffix const & right) {
            return (left.rank[RANK_FIRST] == right.rank[RANK_FIRST] ?
                    (left.rank[RANK_SECOND] < right.rank[RANK_SECOND]) :
                    (left.rank[RANK_FIRST] < right.rank[RANK_FIRST]));
        }
        
        void buildSuffixArray(std::vector<int> & suffixIdxes) {
            int const strSize = str.size();
            std::vector<struct Suffix> suffixes(strSize);
            for (int idx = 0; idx < strSize; idx++) {
                suffixes[idx].idx = idx;
                suffixes[idx].rank[0] = str[idx] - LOWCASE_LETTER;
                suffixes[idx].rank[1] = (idx + 1 < strSize ? str[idx + 1] - LOWCASE_LETTER : -1);
            }
            std::sort(std::begin(suffixes), std::end(suffixes), cmp);

            std::vector<int> oriIdx2Order(strSize);
            for (int k = 2 * 2; k < 2 * strSize; k *= 2) {
                // first set rank start from zero
                int rank = 0;
                int preRank = suffixes[0].rank[RANK_FIRST];
                suffixes[0].rank[RANK_FIRST] = rank;
                oriIdx2Order[suffixes[0].idx] = 0;
                for (int idx = 1; idx < strSize; idx++) {
                    if (preRank == suffixes[idx].rank[RANK_FIRST] && suffixes[idx].rank[RANK_SECOND] == suffixes[idx - 1].rank[RANK_SECOND]) {
                        // at this loop, we can not seperate the suffix string, we have to keep the same
                        preRank = suffixes[idx].rank[RANK_FIRST];
                        suffixes[idx].rank[RANK_FIRST] = rank;
                    } else {
                        preRank = suffixes[idx].rank[RANK_FIRST];
                        suffixes[idx].rank[RANK_FIRST] = ++rank;
                    }
                    // we record the new position of the orginal idx-th index suffix string
                    oriIdx2Order[suffixes[idx].idx] = idx;
                }

                for (int idx = 0; idx < strSize; idx++) {
                    int nextHalfKIdx = suffixes[idx].idx + k / 2;
                    suffixes[idx].rank[RANK_SECOND] = (nextHalfKIdx < strSize ? suffixes[oriIdx2Order[nextHalfKIdx]].rank[RANK_FIRST] : -1);
                }

                std::sort(std::begin(suffixes), std::end(suffixes), cmp);
            }

            std::vector<int>().swap(suffixIdxes);
            for (int idx = 0; idx < strSize; idx++) {
                suffixIdxes.emplace_back(suffixes[idx].idx);
            }
        }
    private:
        std::string const str;
        std::vector<int> suffixIdxes;
    };
public:
    std::string longestDupSubstring(std::string const & s) {
        SuffixArray obj(s);
        std::vector<int> mostLargestLCP;
        obj.kasai(mostLargestLCP);
        
        #ifdef DEBUG
        for (int idx = 0; idx < mostLargestLCP.size(); idx++) {
            std::cout << mostLargestLCP[idx] << ((idx != mostLargestLCP.size() - 1) ? "\t" : "\n");
        }
        #endif
        
        int targetLen = 0;
        int start = 0;
        for (int idx = 0; idx < s.size(); idx++) {
            if (mostLargestLCP[idx] > targetLen) {
                targetLen = mostLargestLCP[idx];
                start = idx;
            }
        }
        if (0 == targetLen) {
            return "";
        }
        return s.substr(start, targetLen);
    }

private:
    static char const LOWCASE_LETTER = 'a';
};