#include "../../head.h"

class SolutionBFS {
public:
    bool canFinish(int const numCourses, std::vector<std::vector<int>> const & prerequisites) {
        if (prerequisites.empty()) {
            return true;
        }
        // because the key is 0 -> numCourses -1, so we can get key by index.
        // which means use array(vector) instead of map
        // std::unordered_map<int, std::set<int>> graph;
        std::vector<std::vector<int>> graph(numCourses);
        std::vector<int> degree(numCourses, 0); // record the course have how many prerequisites, just number not detail

        for (int index = 0; index < prerequisites.size(); index++) {
            if (prerequisites[index].size() < 2) {
                continue;
            }
            for (int subIndex = 1; subIndex < prerequisites[index].size(); subIndex++) {
                graph[prerequisites[index][subIndex]].emplace_back(prerequisites[index][0]); // [1, 0, 2] means 0 and 2 are 1's prerequisit
                degree[prerequisites[index][0]]++;
            }
        }

        for (int num = 0; num < numCourses; num++) {
            int findNoPrereq = 0;
            for (; findNoPrereq < numCourses; findNoPrereq++) { // nuum always reach numCourses faster than findNoPrereq if there is no cycle
                if (0 == degree[findNoPrereq]) {
                    break;
                }
            }
            if (numCourses == findNoPrereq) {
                return false;
            }
            degree[findNoPrereq]--; // remove from the courses, it become negative, and can avoid iterator again
            for (auto depend : graph[findNoPrereq]) {
                degree[depend]--;
            }
        }

        // the foreach can be replaced by queue
        std::queue<int> todo;
        for (int num = 0; num < numCourses; num++) {
            if (0 == degree[num]) {
                todo.emplace(num);
            }
        }
        int dependCourses = numCourses;
        while(!todo.empty()) {
            int curCanDone = todo.front(); todo.pop();
            dependCourses--;
            for (auto depend : graph[curCanDone]) {
                degree[depend]--;
                if (0 == degree[depend]) {
                    todo.emplace(depend);
                }
            }
        }
        return 0 == dependCourses;
    }
};

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::vector<std::set<int>> adj(numCourses);
        std::vector<int> inDegree(numCourses);
        for(int i = 0; i < prerequisites.size(); i++){
            int v1 = prerequisites[i][0];
            int v2 = prerequisites[i][1];
            adj[v2].insert(v1);
            inDegree[v1]++;
        }

        std::queue<int> q;
        int count = 0;
        for(int i = 0; i < numCourses; i++){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int top = q.front();
            q.pop();
            count++;
            for(auto it = adj[top].begin(); it != adj[top].end(); it++){
                inDegree[*it]--;
                if(inDegree[*it] == 0){
                    q.push(*it);
                }
            }
        }
        return count == numCourses;
    }
};

class SolutionDFS {
public:
    // plagiarizing from https://leetcode.com/problems/course-schedule/discuss/58509/C%2B%2B-BFSDFS
    bool canFinish(int const numCourses, std::vector<std::vector<int>> const & prerequisites) {
        if (prerequisites.empty()) {
            return true;
        }
        // because the key is 0 -> numCourses -1, so we can get key by index.
        // which means use array(vector) instead of map
        // std::unordered_map<int, std::set<int>> graph;
        std::vector<std::vector<int>> graph(numCourses);

        for (int index = 0; index < prerequisites.size(); index++) {
            if (prerequisites[index].size() < 2) {
                continue;
            }
            for (int subIndex = 1; subIndex < prerequisites[index].size(); subIndex++) {
                graph[prerequisites[index][subIndex]].emplace_back(prerequisites[index][0]); // [1, 0, 2] means 0 and 2 are 1's prerequisit
            }
        }

        std::vector<bool> toVisit(numCourses, false), visited(numCourses, false);
        for (int num = 0; num < numCourses; num++) {
            if (!visited[num] && (!acyclic(graph, toVisit, visited, num))) {
                    return false;
            }
        }
        return true;
    }

private:
    bool acyclic(std::vector<std::vector<int>> const & graph,
            std::vector<bool> & toVisit, std::vector<bool> & visited, int node) {
        if (toVisit[node]) {
            return false;
        }

        if (visited[node]) {
            return true;
        }
        toVisit[node] = visited[node] = true;
        for (auto depend : graph[node]) {
            if (!acyclic(graph, toVisit, visited, depend)) {
                return false;
            }
        }
        toVisit[node] = false;
        return true;
    }
};
