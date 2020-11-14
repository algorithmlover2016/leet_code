#include "../../head.h"


class SolutionCntResult {
public:
    int smallestSufficientTeam(std::vector<std::string> const & reqSkills,
            std::vector<std::vector<std::string>> const & people) {
        int const reqSkillsSize = reqSkills.size();
        int const reqSkillsState = (1 << reqSkillsSize);
        std::unordered_map<std::string, int> skills2Int;
        for (int idx = 0; idx < reqSkills.size(); idx++) {
            skills2Int[reqSkills[idx]]  = (1 << idx);
            std::cout << reqSkills[idx] << "\t: " << skills2Int[reqSkills[idx]] << "\n";
        }

        std::vector<std::vector<int>> people2Int(people.size());
        for (int idx = 0; idx < people.size(); idx++) {
            std::cout << "people: ";
            for (std::string const & skill : people[idx]) {
                if (skills2Int.find(skill) == skills2Int.end()) {
                    continue;
                }
                people2Int[idx].emplace_back(skills2Int[skill]);
                std::cout << skills2Int[skill] << "\t";
            }
            std::cout << "\n";
        }

        std::vector<int> maskState(reqSkillsState);
        maskState[0] = 1;
        for (int idx = 0; idx < people2Int.size(); idx++) {
            for (int mask = (reqSkillsState - 1); mask >= 0; mask--) {
                for (int const skill : people2Int[idx]) {
                    if (0 == (mask & skill)) {
                        maskState[mask | skill] += maskState[mask];
                    }
                }
            }
        }
        std::cout << "res number: " << maskState[reqSkillsState - 1] << "\n";
        return maskState[reqSkillsState - 1];
    }
};

class SolutionWrongAnswer {
    /*
       ["mwobudvo","goczubcwnfze","yspbsez","pf","ey","hkq"]
[[],["mwobudvo"],["hkq"],["pf"],["pf"],["mwobudvo","pf"],[],["yspbsez"],[],["hkq"],[],[],["goczubcwnfze","pf","hkq"],["goczubcwnfze"],["hkq"],["mwobudvo"],[],["mwobudvo","pf"],["pf","ey"],["mwobudvo"],["hkq"],[],["pf"],["mwobudvo","yspbsez"],["mwobudvo","goczubcwnfze"],["goczubcwnfze","pf"],["goczubcwnfze"],["goczubcwnfze"],["mwobudvo"],["mwobudvo","goczubcwnfze"],[],["goczubcwnfze"],[],["goczubcwnfze"],["mwobudvo"],[],["hkq"],["yspbsez"],["mwobudvo"],["goczubcwnfze","ey"]]
       */
private:
    typedef std::tuple<int, int> mapKey;
    typedef std::map<std::tuple<int, int>, std::vector<int>> tupleMap;
public:
    std::vector<int> smallestSufficientTeam(std::vector<std::string> const & reqSkills,
            std::vector<std::vector<std::string>> const & people) {
        int const reqSkillsSize = reqSkills.size();
        int const reqSkillsState = (1 << reqSkillsSize) - 1;
        std::unordered_map<std::string, int> skills2Int;
        for (int idx = 0; idx < reqSkills.size(); idx++) {
            skills2Int[reqSkills[idx]]  = (1 << idx);
        }

        std::vector<int> people2Int(people.size());
        for (int idx = 0; idx < people.size(); idx++) {
            int skills = 0;
            for (std::string const & skill : people[idx]) {
                if (skills2Int.find(skill) == skills2Int.end()) {
                    continue;
                }
                skills |= skills2Int[skill];
            }
            people2Int[idx] = skills;
        }
        std::vector<int> ans;
        tupleMap dpMemo;
        return dpRecursiveWithMemo(people2Int, 0, 0, dpMemo, reqSkillsState, ans);
    }
    std::vector<int> dpRecursiveWithMemo(std::vector<int> const & people2Int,
                             int idx,
                             int maskState,
                             tupleMap & dpMemo,
                             int const reqSkillsState,
                             std::vector<int> ans) {
        mapKey key = std::make_tuple(idx, maskState);
        if (dpMemo.find(key) != dpMemo.end()) {
            return dpMemo[key];
        }
        std::vector<int> res;
        if (maskState == reqSkillsState) {
            res = ans;
        } else if (idx >= people2Int.size()) {
            res = {};
        } else {
            // not use the cur person
            // dpRecursiveWithMemo(people2Int, idx + 1, maskState, reqSkillsState, res, ans);
            res = dpRecursiveWithMemo(people2Int, idx + 1, maskState, dpMemo, reqSkillsState, ans);

            // using the cur person
            ans.emplace_back(idx);
            // dpRecursiveWithMemo(people2Int, idx + 1, maskState | curMask, dpMemo, reqSkillsState, res, ans);
            std::vector<int> tmpRes = dpRecursiveWithMemo(people2Int, idx + 1, maskState | people2Int[idx], dpMemo, reqSkillsState, ans);
            if (res.empty() || !tmpRes.empty() && tmpRes.size() < res.size()) {
                res = tmpRes;
            }
        }
        return dpMemo[key] = res;
    }
};

class SolutionWrongAnswer {
    /*
       ["mwobudvo","goczubcwnfze","yspbsez","pf","ey","hkq"]
[[],["mwobudvo"],["hkq"],["pf"],["pf"],["mwobudvo","pf"],[],["yspbsez"],[],["hkq"],[],[],["goczubcwnfze","pf","hkq"],["goczubcwnfze"],["hkq"],["mwobudvo"],[],["mwobudvo","pf"],["pf","ey"],["mwobudvo"],["hkq"],[],["pf"],["mwobudvo","yspbsez"],["mwobudvo","goczubcwnfze"],["goczubcwnfze","pf"],["goczubcwnfze"],["goczubcwnfze"],["mwobudvo"],["mwobudvo","goczubcwnfze"],[],["goczubcwnfze"],[],["goczubcwnfze"],["mwobudvo"],[],["hkq"],["yspbsez"],["mwobudvo"],["goczubcwnfze","ey"]]
       */
private:
    typedef std::tuple<int, int> mapKey;
    struct key_hash : public std::unary_function<mapKey, std::size_t> {
        std::size_t operator()(mapKey const & key) const {
            return (std::get<0>(key) << 20) | (std::get<1>(key));
        }
    };

    struct key_equal : public std::binary_function<mapKey, mapKey, bool> {
        bool operator()(mapKey const & key1, mapKey const & key2) const {
            return (std::get<0>(key1) == std::get<0>(key2) &&
                    std::get<1>(key1) == std::get<1>(key2));
        }
    };
    typedef std::unordered_map<std::tuple<int, int>, std::vector<int>, key_hash, key_equal> tupleMap;
public:
    std::vector<int> smallestSufficientTeam(std::vector<std::string> const & reqSkills,
            std::vector<std::vector<std::string>> const & people) {
        int const reqSkillsSize = reqSkills.size();
        int const reqSkillsState = (1 << reqSkillsSize) - 1;
        std::unordered_map<std::string, int> skills2Int;
        for (int idx = 0; idx < reqSkills.size(); idx++) {
            skills2Int[reqSkills[idx]]  = (1 << idx);
        }

        std::vector<int> people2Int(people.size());
        for (int idx = 0; idx < people.size(); idx++) {
            int skills = 0;
            for (std::string const & skill : people[idx]) {
                if (skills2Int.find(skill) == skills2Int.end()) {
                    continue;
                }
                skills |= skills2Int[skill];
            }
            people2Int[idx] = skills;
        }

        std::vector<int> ans;
        tupleMap dpMemo;
        return dpRecursiveWithMemo(people2Int, 0, 0, dpMemo, reqSkillsState, ans);
    }

    std::vector<int> dpRecursiveWithMemo(std::vector<int> const & people2Int,
            int idx,
            int maskState,
            tupleMap & dpMemo,
            int const reqSkillsState,
            std::vector<int> ans) {
        mapKey key = std::make_tuple(idx, maskState);
        if (dpMemo.find(key) != dpMemo.end()) {
            return dpMemo[key];
        }
        std::vector<int> res;
        if (maskState == reqSkillsState) {
            res = ans;
        } else if (idx >= people2Int.size()) {
            res = {};
        } else {
            // not use the cur person
            // dpRecursiveWithMemo(people2Int, idx + 1, maskState, reqSkillsState, res, ans);
            res = dpRecursiveWithMemo(people2Int, idx + 1, maskState, dpMemo, reqSkillsState, ans);

            // using the cur person
            ans.emplace_back(idx);
            // dpRecursiveWithMemo(people2Int, idx + 1, maskState | curMask, dpMemo, reqSkillsState, res, ans);
            std::vector<int> tmpRes = dpRecursiveWithMemo(people2Int, idx + 1, maskState | people2Int[idx], dpMemo, reqSkillsState, ans);
            if (res.empty() || !tmpRes.empty() && tmpRes.size() < res.size()) {
                res = tmpRes;
            }
        }
        return dpMemo[key] = res;
    }
};

class SolutionMapDP ;
public:
    std::vector<int> smallestSufficientTeam(std::vector<std::string> const & reqSkills,
            std::vector<std::vector<std::string>> const & people) {
        // plagiarizing from https://leetcode.com/problems/smallest-sufficient-team/discuss/334572/Python-DP-Solution
        int const reqSkillsSize = reqSkills.size();
        int const reqSkillsComb = (1 << reqSkillsSize);

        std::unordered_map<std::string, int> skills2Int;
        for (int idx = 0; idx < reqSkills.size(); idx++) {
            std::string const & skill = reqSkills[idx];
            if (skills2Int.find(skill) != skills2Int.end()) {
                continue;
            }
            skills2Int[skill] = (1 << idx);
        }

        std::unordered_map<int, std::vector<int>> dpMemo;
        dpMemo[0] = {};

            std::unordered_map<int, std::vector<int>> tmpDpMemo(dpMemo);
        for (int idx = 0; idx < people.size(); idx++) {
            int curSkill = 0;
            for (std::string const & skill : people[idx]) {
                curSkill |= skills2Int[skill];
            }
            // std::cout << std::bitset<16>(curSkill) << "\tdpMemoSize: " << dpMemo.size() << "\n";
            for (std::unordered_map<int, std::vector<int>>::iterator it = dpMemo.begin();
                 it != dpMemo.end();
                 it++) {

                // std::cout << std::bitset<16>(it->first) << "\t";
                int const nextMask = it->first | curSkill;
                if (it->first == nextMask) { // there is no need to add cur person
                    continue;
                }

                // std::cout << "nextMask: " << std::bitset<16>(nextMask) << "\t";
                if (tmpDpMemo.find(nextMask) == tmpDpMemo.end() ||
                    (tmpDpMemo[nextMask].size() > dpMemo[it->first].size() + 1)) {
                    tmpDpMemo[nextMask] = it->second;
                    tmpDpMemo[nextMask].emplace_back(idx);
                    // std::cout << "nextMaskSize: " << tmpDpMemo[nextMask].size() << "\t";
                }
                // std::cout << "\n";
            }
            dpMemo = tmpDpMemo;
            // std::cout << "\n";
        }
        return dpMemo[reqSkillsComb - 1];
    }
};

class SolutionVectorDP {
public:
    std::vector<int> smallestSufficientTeam(std::vector<std::string> const & reqSkills,
            std::vector<std::vector<std::string>> const & people) {
        // plagiarizing from https://leetcode.com/problems/smallest-sufficient-team/discuss/334572/Python-DP-Solution
        int const reqSkillsSize = reqSkills.size();
        int const reqSkillsComb = (1 << reqSkillsSize);

        std::unordered_map<std::string, int> skills2Int;
        for (int idx = 0; idx < reqSkills.size(); idx++) {
            std::string const & skill = reqSkills[idx];
            if (skills2Int.find(skill) != skills2Int.end()) {
                continue;
            }
            skills2Int[skill] = (1 << idx);
        }

        std::vector<std::vector<int>> dpMemo(reqSkillsComb);
        std::vector<std::vector<int>> tmpDpMemo(dpMemo);
        for (int idx = 0; idx < people.size(); idx++) {
            int curSkill = 0;
            for (std::string const & skill : people[idx]) {
                curSkill |= skills2Int[skill];
            }
            // std::cout << std::bitset<16>(curSkill) << "\tdpMemoSize: " << dpMemo.size() << "\n";
            for (int mask = 0; mask < reqSkillsComb; mask++) {
                // std::cout << std::bitset<16>(mask) << "\t";
                int const nextMask = mask | curSkill;
                if (mask == nextMask) { // there is no need to add cur person
                    continue;
                }
                if (0 != mask && dpMemo[mask].empty()) {
                    continue;
                }

                // std::cout << "nextMask: " << std::bitset<16>(nextMask) << "\t";
                if ((tmpDpMemo[nextMask].empty() ||
                    (tmpDpMemo[nextMask].size() > dpMemo[mask].size() + 1))) {
                    // because from mask to nextMask, we need a curSkill who has at least one bit setting 1.
                    // there maybe exist other state, tmpMask that satisfy nextMask = tmpMask | curSkill
                    tmpDpMemo[nextMask] = dpMemo[mask];
                    tmpDpMemo[nextMask].emplace_back(idx);
                }
                // std::cout << "\n";
            }
            dpMemo = tmpDpMemo;
            // std::cout << "\n";
        }
        return dpMemo[reqSkillsComb - 1];
    }
};
