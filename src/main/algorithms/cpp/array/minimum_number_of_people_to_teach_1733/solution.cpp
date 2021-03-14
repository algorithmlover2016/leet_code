#include "../../head.h"


class SolutionTLE {
public:
    int minimumTeachings(int n,
            std::vector<std::vector<int>> const & languages,
            std::vector<std::vector<int>> const & friendships) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031170/Python-Straight-Forward
        // and https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031079/Python-3-steps
        // I misunderstand the problem.
        // referenct set_union(A.begin(),A.end(),B.begin(),B.end(),ostream_iterator<int>(cout," "));
        // https://www.cnblogs.com/nxopen2018/p/10957679.html

        std::unordered_map<int, std::set<int>> usersLanguages;
        for (int idx = 0; idx < languages.size(); idx++) {
            std::set<int> skill(languages[idx].begin(), languages[idx].end());
            usersLanguages[idx] = skill;
        }

        size_t ans = languages.size();
        for (int language = 1; language <= n; language++) {
            // if we choose this language to make all users can communication
            std::set<int> teach;
            for (auto const & relationShip : friendships) {
                if (shipLen > relationShip.size()) {
                    continue;
                }
                auto & first = usersLanguages[relationShip[FIRST_USER_IDX] - 1];
                auto & second = usersLanguages[relationShip[SECOND_USER_IDX] - 1];
                std::set<int> interSectionAns;
                std::set_intersection(first.begin(), first.end(),
                        second.begin(), second.end(),
                        std::inserter(interSectionAns, interSectionAns.begin()));
                if (!interSectionAns.empty()) {
                    continue;
                }
                if (first.find(language) == first.end()) {
                    teach.insert(relationShip[FIRST_USER_IDX] - 1);
                }
                if (second.find(language) == second.end()) {
                    teach.insert(relationShip[SECOND_USER_IDX] - 1);
                }
            }

            ans = std::min(ans, teach.size());
            std::set<int>().swap(teach);
        }
        return ans;


    }
private:
    static int const shipLen = 2;
    static int const FIRST_USER_IDX = 0;
    static int const SECOND_USER_IDX = 1;
};


class SolutionBitSet {
public:
    int minimumTeachings(int n,
            std::vector<std::vector<int>> const & languages,
            std::vector<std::vector<int>> const & friendships) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031170/Python-Straight-Forward
        // and https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031079/Python-3-steps
        // and https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031170/Python-Straight-Forward/828843
        // I misunderstand the problem.
        // referenct set_union(A.begin(),A.end(),B.begin(),B.end(),ostream_iterator<int>(cout," "));
        // https://www.cnblogs.com/nxopen2018/p/10957679.html

        int const languagesSize = languages.size();
        std::vector<std::bitset<BIT_TOL_CNT>> lans(languagesSize);
        for (int idx = 0; idx < languages.size(); idx++) {
            for (auto const lan : languages[idx]) {
                lans[idx].set(lan);
            }
        }

        size_t ans = languagesSize;
        for (int language = 1; language <= n; language++) {
            // if we choose this language to make all users can communication
            std::set<int> teach;
            for (auto const & relationShip : friendships) {
                if (shipLen > relationShip.size()) {
                    continue;
                }
                auto & first = lans[relationShip[FIRST_USER_IDX] - 1];
                auto & second = lans[relationShip[SECOND_USER_IDX] - 1];
                if ((first & second).any()) {
                    continue;
                }
                if (!first.test(language)) {
                    teach.insert(relationShip[FIRST_USER_IDX] - 1);
                }
                if (!second.test(language)) {
                    teach.insert(relationShip[SECOND_USER_IDX] - 1);
                }
            }

            ans = std::min(ans, teach.size());
            std::set<int>().swap(teach);
        }
        return ans;


    }
private:
    static int const shipLen = 2;
    static int const FIRST_USER_IDX = 0;
    static int const SECOND_USER_IDX = 1;
    static int const BIT_TOL_CNT = 512; // the max languages.size() is not larger than 500
};

// #define DEBUG
class Solution {
public:
    int minimumTeachings(int n,
            std::vector<std::vector<int>> const & languages,
            std::vector<std::vector<int>> const & friendships) {
        // plagiarizing from https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031170/Python-Straight-Forward
        // and https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031079/Python-3-steps
        // and https://leetcode.com/problems/minimum-number-of-people-to-teach/discuss/1031170/Python-Straight-Forward/828843
        // I misunderstand the problem.
        // referenct set_union(A.begin(),A.end(),B.begin(),B.end(),ostream_iterator<int>(cout," "));
        // https://www.cnblogs.com/nxopen2018/p/10957679.html

        int const languagesSize = languages.size();
        std::vector<std::bitset<BIT_TOL_CNT>> lans(languagesSize);
        for (int idx = 0; idx < languages.size(); idx++) {
            for (auto const lan : languages[idx]) {
                lans[idx].set(lan);
            }
        }

        std::unordered_set<int> needTeachUsers;
        for (auto const & relationShip : friendships) {
            if (shipLen > relationShip.size()) {
                continue;
            }
            auto & first = lans[relationShip[FIRST_USER_IDX] - 1];
            auto & second = lans[relationShip[SECOND_USER_IDX] - 1];
            if ((first & second).none()) {
                needTeachUsers.insert(relationShip[FIRST_USER_IDX] - 1);
                needTeachUsers.insert(relationShip[SECOND_USER_IDX] - 1);
            }
        }

        std::unordered_map<int, int> languages2Users;
        int userNumForMaxPolularLanguage = 0;

        for (int user: needTeachUsers) {
            for (auto const lan : languages[user]) {
                userNumForMaxPolularLanguage = std::max(userNumForMaxPolularLanguage, ++languages2Users[lan]);
                #ifdef DEBUG
                std::cout << lan << ", " << languages2Users[lan] << ", " << userNumForMaxPolularLanguage << "\n";
                #endif
            }
        }

        int ans = needTeachUsers.size() - userNumForMaxPolularLanguage;
        return ans;
    }
private:
    static int const shipLen = 2;
    static int const FIRST_USER_IDX = 0;
    static int const SECOND_USER_IDX = 1;
    static int const BIT_TOL_CNT = 512; // the max languages.size() is not larger than 500
};
