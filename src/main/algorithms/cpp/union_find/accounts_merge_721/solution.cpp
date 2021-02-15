#include "../../head.h"


class SolutionTLE {
public:
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>> const & acts) {
        // plagiarizing from https://leetcode.com/problems/accounts-merge/discuss/109157/JavaC%2B%2B-Union-Find
        std::map<std::string, std::string> owner;
        std::map<std::string, std::string> parents;

        std::function<std::string(std::string const &)> find = [&](std::string const & s) {
            return parents[s] = (parents[s] == s ? s : find(parents[s]));
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
            std::vector<std::string> emails;
            emails.emplace_back(owner[p.first]);
            for (auto emailIt = p.second.begin(); emailIt != p.second.end(); emailIt++) {
                emails.emplace_back(*emailIt);
            }
            merged.push_back(emails);
        }
        return merged;
    }
};

class Solution {
protected:
    // union find with rank
    struct DisjointSet {
        std::vector<int> parent;
        std::vector<int> rank;
        DisjointSet(int n) {
            parent = std::vector<int>(n);
            rank = std::vector<int>(n);
            std::iota(parent.begin(), parent.end(), 0);
            // for(int i = 0 ; i < n ; ++i){
            //     parent[i] = i;
            // }
        }

        void add(int index) {
            parent.push_back(index);
        }

        int find(int a) {
            if(parent[a] == a) {
                return a;
            }
            return parent[a] = find(parent[a]);
        }

        void merge(int a, int b) {
            a = find(a);
            b = find(b);
            if(a == b) {
                return;
            }
            if(rank[a] > rank[b]) {
                std::swap(a, b);
                // merge(b, a);
                // return;
            }
            parent[a] = b;
            if(rank[a] == rank[b]) {
                rank[b] += 1;
            }
        }

    };

public:
    std::vector<std::vector<std::string>> accountsMerge(std::vector<std::vector<std::string>> const & accounts) {
        int offset = accounts.size();
        DisjointSet ds(offset);
        std::unordered_map<std::string, int> email_hash;
        for(int i = 0 ; i < accounts.size(); ++i) {
            for(int j = 1 ; j < accounts[i].size(); ++j) {
                if(email_hash.find(accounts[i][j]) == email_hash.end()) {
                    ds.add(i);
                    email_hash[accounts[i][j]] = offset;
                    offset += 1;
                } else {
                    ds.merge(i, email_hash[accounts[i][j]]);
                }
            }
        }

        std::unordered_map<int, int> name_index;
        std::vector<std::vector<std::string>> ret;
        int index = 0;
        for(int i = 0 ; i < accounts.size(); ++i) {
            if(ds.find(i) == i) {
                name_index[i] = index;
                index += 1;
                ret.push_back({accounts[i][0]});
            }
        }

        for(auto it = email_hash.begin(); it != email_hash.end(); ++it) {
            ret[name_index[ds.find(it->second)]].push_back(it->first);
        }

        for(int i = 0 ; i < ret.size() ; ++i) {
            std::sort(ret[i].begin() + 1, ret[i].end());
        }

        return ret;
    }
};
