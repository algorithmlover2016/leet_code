#include "../../head.h"
#include "./graph_node.h"

class Solution {
public:

    // plagiarizing from https://leetcode.com/problems/clone-graph/discuss/42313/C%2B%2B-BFSDFS
    Node* cloneGraphBFS(Node* node) {
        if (nullptr == node) {
            return nullptr;
        }

        std::unordered_map<Node*, Node*> originalCopyMap;
        // make the first map
        originalCopyMap[node] = new Node(node->val, {});

        std::queue<Node*> bfsStore;
        bfsStore.emplace(node);
        while (!bfsStore.empty()) {
            Node * cur = bfsStore.front(); bfsStore.pop();
            for (Node * neighbor : cur->neighbors) {
                if (originalCopyMap.find(neighbor) == originalCopyMap.end()) {
                    originalCopyMap[neighbor] = new Node(neighbor->val, {});
                    bfsStore.emplace(neghbor);
                }
                originalCopyMap[cur]->neighbors.emplace_back(originalCopyMap[neighbor]);
            }
        }
        return originalCopyMap[node];
    }

    Node* cloneGraphDFS(Node* node) {
        if (nullptr == node) {
            return nullptr;
        }

        if (originalCopyMap.find(node) == originalCopyMap.end()) {
            originalCopyMap[node] = new Node(node->val, {});
            for (Node * neighbor : node->neighbors) {
                originalCopyMap[node]->neighbors.emplace_back(cloneGraph(neighbor));
            }
        }
        return originalCopyMap[node];
    }

private:
        std::unordered_map<Node*, Node*> originalCopyMap;
};

class SolutionBetterRuntime {
public:
    Node* cloneGraph(Node* node) {
        if (nullptr == node)
            return nullptr;

        // first construct copy node, and when all ready, connect each other
        std::queue<Node*> q;
        std::unordered_map<Node*, Node*> visited;

        q.push(node);

        while (!q.empty()) {
            Node* curr_node = q.front(); q.pop();

            if (visited.find(curr_node) == visited.end()) {
                Node* new_node = new Node(curr_node->val);


                visited[curr_node] = new_node;

                for (auto next_node: curr_node->neighbors) {
                    if(visited.find(next_node) == visited.end())
                        q.push(next_node);

                    else {
                        Node* new_neighbor = visited[next_node];
                        new_node->neighbors.push_back(new_neighbor);
                        new_neighbor->neighbors.push_back(new_node);
                    }
                }
            }
        }

        return visited[node];
    }
};
