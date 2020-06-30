#include "../../head.h"


class SolutionTLE {
public:
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>> const & acts) {
        // plagiarizing from https://leetcode.com/problems/accounts-merge/discuss/109157/JavaC%2B%2B-Union-Find
        std::map<std::string, std::string> owner;
        std::map<std::string, std::string> parents;

        std::function<std::string(std::string const &)> find = [&](string const & s) {
            return parents[s] == s ? s : find(parents[s]);
        };

        // initialization the parent Map
        for (int i = 0; i < acts.size(); i++) {
            for (int j = 1; j < acts[i].size(); j++) {
                parents[acts[i][j]] = acts[i][j];
                owner[acts[i][j]] = acts[i][0];
            }
        }

        for (int i = 0; i < acts.size(); i++) {
            std::string p = find(acts[i][1]);
            // each subArray union to a parent and different subArray union to the last occurence
            for (int j = 2; j < acts[i].size(); j++) {
                parents[find(acts[i][j])] = p;
            }
        }

        std::map<std::string, std::set<std::string>> unions;
        for (int i = 0; i < acts.size(); i++) {
            for (int j = 1; j < acts[i].size(); j++) {
                // get lists
                unions[find(acts[i][j])].insert(acts[i][j]);
            }
        }
        std::vector<std::vector<std::string>> merged;
        for (std::pair<std::string, std::set<std::string>> const & p : unions) {
            std::vector<std::string> emails(p.second.begin(), p.second.end());
            emails.insert(emails.begin(), owner[p.first]);
            merged.push_back(emails);
        }
        return merged;
    }
};
