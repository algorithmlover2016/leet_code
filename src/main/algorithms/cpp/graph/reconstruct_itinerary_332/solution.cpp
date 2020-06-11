#include "../../head.h"

 
class SolutionError {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> const & tickets) {
        if (tickets.empty()) {
            return {};
        } else if (tickets.size() == 1) {
            return tickets.back();
        }
        std::unordered_map<std::string, std::set<string>> graph;

        for (auto const & pair : tickets) {
            if (pair.size() < 2) {
                continue;
            }
            if (graph.find(pair[0]) == graph.end()) {
                graph[pair[0]] = std::set<std::string>();
            }
            graph[pair[0]].emplace(pair[1]);
        }
        std::vector<std::string> ans;
        std::string const START("JFK");

        std::queue<std::string> todo;
        todo.emplace(START);
        while (!todo.empty()) {
            std::string cur = todo.front(); todo.pop();
            ans.emplace_back(cur);
            if (graph.find(cur) == graph.end()) {
                return {};
            }
            auto it = graph[cur].begin();
            std::string next = *it;
            graph[cur].erase(it);
            todo.emplace(next);
        }
        return ans;
    }
};

class SolutionDFS {
public:
    // https://leetcode.com/problems/reconstruct-itinerary/discuss/78768/Short-Ruby-Python-Java-C%2B%2B
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> const & tickets) {
        if (tickets.empty()) {
            return {};
        }

        std::unordered_map<std::string, std::multiset<string>> graph;

        for (auto const & pair : tickets) {
            if (pair.size() < 2) {
                continue;
            }
            if (graph.find(pair[0]) == graph.end()) {
                graph[pair[0]] = std::multiset<std::string>();
            }
            graph[pair[0]].emplace(pair[1]);
        }

        std::vector<std::string> ans;
        std::string const START("JFK");
        visitDFS(START, graph, ans);
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    void visitDFS(std::string const & start, std::unordered_map<std::string, std::multiset<std::string>> & graph,
            std::vector<std::string> & ans) {
        if (graph.find(start) != graph.end()) {
            while(graph[start].size()) {
                auto it = graph[start].begin();
                std::string next = *(it);
                graph[start].erase(it);
                visitDFS(next, graph, ans);
            }
        }
        ans.emplace_back(start);
    }

};

class Solution {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> const & tickets) {
        std::vector<std::string> ret;
        std::unordered_map<std::string, std::multiset<std::string>> um;
        for(auto & v : tickets) {
            um[v[0]].insert(v[1]);
        }
        dfs(um, ret, "JFK");
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
    void dfs(std::unordered_map<std::string, std::multiset<std::string>> & um, std::vector<std::string> &ret, std::string from) {
        auto &st = um[from];
        while(!st.empty()) {
            string to = *st.begin();
            um[from].erase(st.begin());
            dfs(um, ret, to);
        }
        ret.push_back(from);
    }
};
