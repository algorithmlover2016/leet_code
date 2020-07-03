#include "../../head.h"


class SolutionReverseIterator {
public:
    int minJumps(std::vector<int> const & arr) {
        // plagiarizing from https://leetcode.com/problems/jump-game-iv/discuss/502699/JavaC%2B%2B-BFS-Solution-Clean-code-O(N)
        int arrSize = arr.size();
        if (2 > arrSize) {
            return 0;
        }
        std::unordered_map<int, std::vector<int>> graph;
        for (int index = 0; index < arrSize; index++) {
            // equal element gather together
            graph[arr[index]].emplace_back(index);
        }
        std::vector<bool> visited(arrSize, false);
        std::queue<int> todo;
        todo.emplace(0);
        visited[0] = true;
        int res = 0;
        do {
            res++;
            for (int layerSize = todo.size(); layerSize > 0; layerSize--) {
                int curIndex = todo.front(); todo.pop();
                // std::cout << "\n curIndex : " << curIndex << "\t";
                if (curIndex + 1 < arrSize) {
                    graph[arr[curIndex]].emplace_back(curIndex + 1);
                }
                if (curIndex >= 1) {
                    graph[arr[curIndex]].emplace_back(curIndex - 1);
                }
                for (std::vector<int>::const_reverse_iterator it = graph[arr[curIndex]].crbegin();
                     it != graph[arr[curIndex]].crend(); it++) {
                    // std::cout << " jump to " << next << '\t';
                    int next = *it;
                    if (next + 1 == arrSize) {
                        return res;
                    }
                    if (!visited[next]) {
                        visited[next] = true;
                        todo.emplace(next);
                    }
                }

            }
        } while (todo.size());
        return -1;
    }
};

class SolutionMoreSlow {
public:
    int minJumps(std::vector<int> const & arr) {
        // plagiarizing from https://leetcode.com/problems/jump-game-iv/discuss/502699/JavaC%2B%2B-BFS-Solution-Clean-code-O(N)
        int arrSize = arr.size();
        if (2 > arrSize) {
            return 0;
        }
        std::unordered_map<int, std::vector<int>> graph;
        for (int index = 0; index < arrSize; index++) {
            // equal element gather together
            graph[arr[index]].emplace_back(index);
        }
        std::queue<int> todo;
        todo.emplace(0);
        int res = 0;
        do {
            res++;
            for (int layerSize = todo.size(); layerSize > 0; layerSize--) {
                int curIndex = todo.front(); todo.pop();
                // std::cout << "\n curIndex : " << curIndex << "\t";
                if (curIndex + 1 < arrSize && graph.find(arr[curIndex + 1]) != graph.end()) {
                    if (curIndex + 1 == arrSize - 1) {
                        return res;
                    }
                    todo.emplace(curIndex + 1);
                }
                if (curIndex >= 1 && graph.find(arr[curIndex - 1]) != graph.end()) {
                    todo.emplace(curIndex - 1);
                }
                if (graph.find(arr[curIndex]) != graph.end()) {
                    for (std::vector<int>::const_reverse_iterator it = graph[arr[curIndex]].crbegin();
                         it != graph[arr[curIndex]].crend(); it++) {
                        int next = *it;
                        if (next + 1 == arrSize) {
                            return res;
                        }
                        todo.emplace(next);
                    }
                    graph.erase(arr[curIndex]);
                }
            }
        } while (todo.size());
        return -1;
    }
};

static int accel = [](){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
    void enqueue(std::queue<int> & bfs, std::vector<bool> & processed, int idx) {
        bfs.push(idx);
        processed[idx] = true;
    }
public:
    int minJumps(std::vector<int> & arr) {
        if (arr.size() < 2) {
            return 0;
        }

        std::unordered_map<int, std::vector<int>> sameElementMap;
        int len = arr.size(), min_jumps = 0 ;

        for (int i = 0 ; i < len ; i++) {
            sameElementMap[arr[i]].push_back(i);
        }

        std::queue<int> bfs;
        bfs.push(0);
        std::vector<bool> processed(arr.size(), false);
        int dest = len - 1;
        processed[0] = true;

        while(!bfs.empty()) {
            int size = bfs.size();
            min_jumps++;
            while(size--) {
                int front = bfs.front(); bfs.pop();
                if (front == dest) {
                    return min_jumps;
                }

                if(front + 1 < len && !processed[front + 1]) {
                    if(front + 1 == dest) {
                        return min_jumps;
                    }
                    enqueue(bfs, processed, front + 1);
                }

                if(front - 1 >= 0 && !processed[front - 1]) {
                    if(front - 1 == dest ) {
                        return min_jumps;
                    }
                    enqueue(bfs, processed, front - 1);
                }

                if(sameElementMap.find(arr[front]) != sameElementMap.end()) {
                    for(auto next_idx : sameElementMap[arr[front]]) {
                        if(!processed[next_idx]) {
                            if (next_idx == dest) {
                                return min_jumps;
                            }
                            enqueue(bfs, processed, next_idx);
                        }
                    }
                    sameElementMap.erase(arr[front]);
                }
            }
        }
        return -1;
    }
};
