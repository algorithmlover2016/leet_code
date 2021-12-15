#include "../../head.h"


class Solution {
private:
    struct Node
    {
        std::map<std::string, struct Node*> curNodes;
        std::string curName;
        bool isDelete = false;
        Node(std::string const & name = "") : curName(name) {}

        void insert(std::vector<std::string> const & path, int const idx = 0) {
            if (idx < path.size()) {
                auto it = curNodes.find(path[idx]);
                if (it == curNodes.end()) {
                    it = curNodes.insert({path[idx], new Node(path[idx])}).first;
                }
                it->second->insert(path, idx + 1);
            }
        }


        std::string trim(std::unordered_map<std::string, struct Node*> & globalMap) {
            std::string curPath;
            for (auto & [name, node] : curNodes) {
                curPath += node->trim(globalMap);
            }
            if (!curPath.empty()) {
                auto it = globalMap.find(curPath);
                if (it != std::end(globalMap)) {
                    it->second->isDelete = isDelete = true;
                } else {
                    globalMap[curPath] = this; // can not be set as it->second
                }
            }
            return "(" + curName + curPath + ")";
        }

        void build(std::vector<std::vector<std::string>> & paths, std::vector<std::string> & path) {
            if (!isDelete) {
                if (!path.empty()) {
                    paths.emplace_back(path);
                }
                for (auto & [name, node] : curNodes) {
                    path.emplace_back(name);
                    node->build(paths, path);
                    path.pop_back();
                }
            }

        }

    };
    
public:
    std::vector<std::vector<std::string>> deleteDuplicateFolder(std::vector<std::vector<std::string>> const & paths) {
        // plagiarizing from https://leetcode.com/problems/delete-duplicate-folders-in-system/discuss/1361096/Hash-Map-of-Serialized-Tree-Traversals
        struct Node r;
        for (auto & path : paths) {
            r.insert(path);
        }
        std::vector<std::vector<std::string>> ans;
        r.trim(std::unordered_map<std::string, Node *>() = {});
        r.build(ans, std::vector<std::string>() = {});
        return ans;
    }
};