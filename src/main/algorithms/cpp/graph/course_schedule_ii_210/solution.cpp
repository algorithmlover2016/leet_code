#inclue "../../head.h"

class SolutionBFS {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> const & prerequisites) {
        if (numCourses == 0) {
            return {};
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

        // the foreach can be replaced by queue
        std::vector<int> ans(numCourses);;
        std::queue<int> todo;
        for (int num = 0; num < numCourses; num++) {
            if (0 == degree[num]) {
                todo.emplace(num);
            }
        }
        int dependCourses = numCourses;
        while(!todo.empty()) {
            int curCanDone = todo.front(); todo.pop();
            ans[numCourses - dependCourses] = curCanDone;
            dependCourses--;
            for (auto depend : graph[curCanDone]) {
                degree[depend]--;
                if (0 == degree[depend]) {
                    todo.emplace(depend);
                }
            }
        }
        return 0 == dependCourses ? ans : std::vector<int>();
    }
};


class SolutionDFS {
public:
    // plagiarizing from https://leetcode.com/problems/course-schedule/discuss/58509/C%2B%2B-BFSDFS
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> const & prerequisites) {
        if (0 == numCourses) {
            return {};
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
        std::vector<int> ans;
        for (int num = 0; num < numCourses; num++) {
            if (!visited[num] && (!acyclic(graph, toVisit, visited, num, ans))) {
                    return {};
            }
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }

private:
    bool acyclic(std::vector<std::vector<int>> const & graph,
            std::vector<bool> & toVisit, std::vector<bool> & visited,
            int node, std::vector<int> & ans) {
        if (toVisit[node]) {
            return false;
        }

        if (visited[node]) {
            return true;
        }
        toVisit[node] = visited[node] = true;
        for (auto depend : graph[node]) {
            if (!acyclic(graph, toVisit, visited, depend, ans)) {
                return false;
            }
        }
        toVisit[node] = false;
        ans.emplace_back(node);
        return true;
    }
};

class SolutionBetterRuntime {
    public:
        std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& pre) {
            std::vector<std::vector<int> > graph;
            graph.resize(numCourses);

            std::vector<int> ans;
            std::vector<int> toret;

            for(int i = 0; i < pre.size(); i++)
            {
                int s = pre[i][0];
                int d = pre[i][1];
                graph[d].push_back(s);
            }

            std::queue<int> q;
            std::vector<int> ins(numCourses);
            for(int i = 0; i < numCourses; i++)
                ins[i] = 0;

            for(int i = 0; i < numCourses; i++)
            {
                for(int j = 0; j < graph[i].size(); j++)
                {
                    ins[graph[i][j]]++;
                }
            }

            std::vector<int> visited(numCourses);
            for(int i = 0; i < numCourses; i++)
                visited[i] = 0;

            for(int i = 0; i < numCourses; i++)
            {
                if(ins[i] == 0)
                {
                    q.push(i);
                    visited[i] = 1;
                }
            }
            if(q.size() == 0)
                return toret;

            while(!q.empty())
            {
                int s = q.front();
                cout << s << endl;
                ans.push_back(s);
                q.pop();
                visited[s] = 1;
                for(int i = 0; i < graph[s].size(); i++)
                {
                    int d = graph[s][i];
                    ins[d]--;
                    if(ins[d] == 0)
                    {
                        q.push(d);
                        visited[d] = 1;
                    }
                }
            }


            for(int i = 0; i < numCourses; i++)
                if(visited[i] == 0)
                    return toret;
            return ans;
        }
};

