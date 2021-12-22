#include "../../head.h"



// #define DEBUG
#define ROLLING_HASH_WITH_COLLISION_CHECK
class Solution {
public:
    int longestCommonSubpath(int n, std::vector<std::vector<int>> const & paths) {
        // plagiarizing from https://leetcode.com/problems/longest-common-subpath/discuss/1314826/Rolling-Hash-vs.-Suffix-Automation
        // rolling and hash.
        auto cmp = [&] (std::vector<int> const & left, std::vector<int> const & right) {
            return left.size() < right.size();
        };

        // the max common length will not be larger than the shortest lenght of paths.legth
        int left = 0, right = std::min_element(std::begin(paths), std::end(paths), cmp)->size();
        while (left < right) {
            int mid = (left + right + 1) / 2;
            #ifdef DEBUG
            std::cout << "left, mid, right: " << left << ", " << mid << ", " << right << "\n";
            #endif
            if (
                #ifndef ROLLING_HASH_WITH_COLLISION_CHECK
                rollingHash(paths, mid)
                #else
                rollingHashWithCollisionCheck(paths, mid)
                #endif
            ) {
            
                left = mid;
            } else {
                right= mid - 1;
            }
        }
        return left;
    }
private:
    bool rollingHash(std::vector<std::vector<int>> const & paths, int const len) {
        if (0 == len) {
            return true;
        }
        #ifdef DEBUG
        std::cout << "cur len: " << len << '\n';
        #endif
        std::unordered_set<long long> rollHashs;
        for (int idx = 0; idx < paths.size() && (0 == idx || !rollHashs.empty()); idx++) {
            std::unordered_set<long long> nextRollHashs;
            long long int hash = 0;
            long long int baseLen = 1;
            for (int subIdx = 0; subIdx < paths[idx].size(); subIdx++) {
                hash = (hash * BASE_NUM + paths[idx][subIdx]) % HASH_MOD;
                if (subIdx >= len /*we have get the length of substr which is larger than len, so we need the beginning.*/) {
                    hash = (hash - paths[idx][subIdx - len] * baseLen % HASH_MOD + HASH_MOD) % HASH_MOD;
                } else {
                    baseLen = baseLen * BASE_NUM % HASH_MOD;
                }
                #ifdef DEBUG
                std::cout << "hash: " << hash <<"\n";
                #endif
                if ((subIdx >= len - 1) && (0 == idx || rollHashs.count(hash))) {
                    // we only reserve the valid hash which have the length of substr is len, and just add the hash numbers of the substr extracting from the first substr
                    // or the hash number of the substr extracting from the others which appears in the substr of the first string
                    nextRollHashs.emplace(hash);
                }
            }
            std::swap(rollHashs, nextRollHashs);
            #ifdef DEBUG
            std::cout << "cur rolling hash size: " << rollHashs.size() << "\n";
            #endif
        }
        return !rollHashs.empty();
    }

    bool rollingHashWithCollisionCheck(std::vector<std::vector<int>> const & paths, int const len) {
        if (0 == len) {
            return true;
        }
        std::unordered_map<long long, std::vector<int> /*the starting idx from the paths[0]*/> rollHashs;
        for (int idx = 0; idx < paths.size() && (0 == idx /*it means the first string*/ || !rollHashs.empty() /*if rollHashs.empty is true, and it means there is no common*/); idx++) {
            std::unordered_map<long long, std::vector<int>> nextRollHashs;
            long long int hash = 0;
            long long int baseLen = 1;
            for (int subIdx = 0; subIdx < paths[idx].size(); subIdx++) {
                hash = (hash * BASE_NUM + paths[idx][subIdx]) % HASH_MOD;
                if (subIdx >= len /*we have get the length of substr which is larger than len, so we need the beginning.*/) {
                    hash = (hash - paths[idx][subIdx - len] * baseLen % HASH_MOD + HASH_MOD) % HASH_MOD;
                } else {
                    baseLen = baseLen * BASE_NUM % HASH_MOD;
                }

                if (subIdx >= len - 1 /*we have get len length substr, then we get a valid hash number*/) {
                    if (0 == idx) {
                        // we only reserve the hash number of the substr substract from the first string and whose length is len
                        nextRollHashs[hash].emplace_back(subIdx - len + 1);
                    } else {
                        if (rollHashs.count(hash) /*according to our hash function, there are two substr matching one hash number*/) {
                            for (auto const posIdx : rollHashs[hash]) {
                                if (std::equal(std::begin(paths[0]) + posIdx, std::begin(paths[0]) + posIdx + len, std::begin(paths[idx]) + subIdx - len + 1)) {
                                    nextRollHashs[hash].emplace_back(posIdx);
                                }
                            }
                        }
                    }
                }
            }
            std::swap(rollHashs, nextRollHashs);
        }
        return !rollHashs.empty();
    }

private:
    static int const BASE_NUM = 1e5 + 1;
    static long long const HASH_MOD = 1e11 + 19;
};
