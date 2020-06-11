#include "../../head.h"
 

class SolutionDFS {
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>> const & equations,
            std::vector<double>& values,
            std::vector<std::vector<std::string>> const & queries) {
        std::unordered_map<std::string, double> weight;
        std::unordered_map<std::string, std::set<std::string>> graph;

        if (equations.size() != values.size()) {
            return {};
        }

        // construct graph
        for (int index = 0; index < equations.size(); index++) {
            if (2 > equations[index].size()) {
                continue;
            }
            graph[equations[index][0]].emplace(equations[index][1]);
            graph[equations[index][1]].emplace(equations[index][0]);
            weight[equations[index][0] + "@" + equations[index][1]] = values[index];
            weight[equations[index][1] + "@" + equations[index][0]] = 1.0 / values[index];
        }
        std::vector<double> ans;
        for (int index = 0; index < queries.size(); index++) {
            if (queries[index].size() < 2) {
                continue;
            }

            std::string start = queries[index][0];
            std::string end = queries[index][1];

            if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
                ans.emplace_back(-1.0);
                continue;
            }
            if (start == end) {
                ans.emplace_back(1.0);
                continue;
            }
            double res = dfs(start, end, "", weight, graph);
            ans.emplace_back(res > 0 ? res : -1.0);

        }

        return ans;
    }

    // if not find a path from start to end, return 0, otherwise return the path weight
    double dfs(std::string const & start,
            std::string const & end,
            std::string before,
            std::unordered_map<std::string, double> const & weight,
            std::unordered_map<std::string, std::set<std::string>> const & graph) {
        if (start == end) {
            return 1.0;
        }
        double res = 0;
        for (auto & neighbor : graph.at(start)) {
            if (neighbor == before) {
                continue;
            }
            before = start;
            res = std::max(res,  weight.at(start + "@" + neighbor) * dfs(neighbor, end, before, weight, graph));

        }
        return res;
    }

};


class SolutionBFS {
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>> const & equations,
            std::vector<double> const & values,
            std::vector<std::vector<std::string>> const & queries) {
        std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> g;
        for (int i=0; i<equations.size(); ++i) {
            g[equations[i][0]].push_back({equations[i][1], values[i]});
            g[equations[i][1]].push_back({equations[i][0], 1.0 / values[i]});
        }
        
        std::vector<double> res;
        for(auto & p : queries){
            res.push_back(find(g, p));
        }
        return res;
    }
    
    double find(std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& g,
            std::vector<std::string> & q){
        if (!g.count(q[0]) || !g.count(q[1])) {
            return -1;
        }
        std::string head = q[0];
        std::unordered_set<std::string> visited;
        std::queue<std::pair<std::string, double>> Q;
        Q.push({head, 1});
        while(Q.size()){
            int len = Q.size();
            while(len){
                --len;
                string node = Q.front().first;
                double num = Q.front().second;
                if(node == q[1]) {
                    return num;
                }
                visited.insert(node);
                Q.pop();
                for(auto & child : g[node]){
                    if(!visited.count(child.first)) {
                        Q.push({child.first, child.second * num});
                    }
                }
            }
        }
        return -1;
    }
};
