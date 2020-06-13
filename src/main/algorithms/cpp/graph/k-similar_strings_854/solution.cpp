#include "../../head.h"
 

class SolutionJustOneRoute {
public:
    int kSimilarity(std::string & A, std::string & B) {
        if (A.size() != B.size()) {
            return -1;
        }
        int k = 0;
        for (int iB = 0; iB < B.size(); iB++) {
            if (A[iB] == B[iB]) {
                continue;
            }
            int iA = iB + 1;
            while (iA < A.size()) {
                if (A[iA] == B[iB] && B[iA] != A[iA]) {
                    std::swap(A[iA], A[iB]);
                    k++;
                    break;
                } else {
                    iA++;
                }
            }
        }
        return k;

    }
};

class SolutionBetterRuntime {
    void swap(char& a,char & b) {
        char temp=a;
        a=b;
        b=temp;
    }
    int sol(string& a, string& b, int in) {
        int n=a.length();
        int a1=-1,a2=-1;
        int y=INT_MAX;
        for(int i=in;i<n;i++)
        {
            if(a[i]!=b[i])
            {
                if(a1==-1)
                    a1=i;
                
                for(int j=i+1;j<n;j++)
                {
                    if(b[j]==a[i] && a[j]==b[i])
                    {
                        a1=i;
                        a2=j;
                        swap(a[i],a[j]);
                        y = sol(a,b,in)+1;
                        swap(a[i],a[j]);
                        return y;
                    }
                }
            }
            
        }
        if(a1==-1)
            return 0;
        for(int i=a1+1;i<n;i++)
        {
            if(a[i]==b[a1] && a[i]!=b[i])
            {
                a2=i;
                swap(a[a1],a[a2]);
                y=min(y,sol(a,b,in+1));
                swap(a[a1],a[a2]);
            }
        }
        
        return y+1;
    }
public:
    int kSimilarity(string A, string B) {
        return sol(A,B,0);
    }
};

class SolutionBFS {
public:
    int kSimilarity(std::string const & A, std::string const & B) {
        // plagiarizing from https://leetcode.com/problems/k-similar-strings/discuss/140099/JAVA-BFS-32-ms-cleanconciseexplanationwhatever
        if (0 == A.compare(B)) {
            return 0;
        }
        std::set<std::string> visited;
        std::queue<std::string> todo;
        todo.emplace(A);

        int size = 0;
        int ans = 0;
        while (size = todo.size()) {
            ans++;
            while (size-- > 0) {
                std::string cur = todo.front(); todo.pop();
                int index = 0;
                // because cur.size() == B.size(), and cur != B, so index < B.size() is true;
                while (cur[index] == B[index]) {
                    index++;
                }
                for (int j = index + 1; j < B.size(); j++) {
                    if ((B[index] == cur[j]) && (B[j] != cur[j])) {
                        std::string tmp(cur);
                        std::swap(tmp[index], tmp[j]);
                        if (tmp == B) {
                            return ans;
                        }
                        // if visited.emplace fail, there must be emplaced before, so it's not the shortest
                        if (visited.emplace(tmp).second) {
                            todo.emplace(tmp);
                        }
                    }
                }
            }

        }
        return ans;
    }
};

class Solution {
public:
    int kSimilarity(std::string const & A, std::string const & B) {
        // plagiarizing from https://leetcode.com/problems/k-similar-strings/discuss/139872/Java-Backtracking-with-Memorization add a map to store visited node to slow down runtime;
        std::unordered_map<std::string, int> visitedWeight;
        return dfs(A, B, visitedWeight, 0);
    }

    int dfs(std::string const & start,
            std::string const & end,
            std::unordered_map<string, int> & visitedWeight,
            int index) {
        if (start == end) {
            // compute the height from buttom to top, and the layerHeight use min function to find the shortest path
            // if compute the tree height, when computing from buttom to height, then should use max function
            return 0;
        }
        if (visitedWeight.find(start) != visitedWeight.end()) {
            return visitedWeight[start];
        }
        while (start[index] == end[index]) {
            index++;
        }
        int layerHeight = INT_MAX;
        for (int j = index + 1; j < start.size(); j++) {
            if (start[j] == end[index] && start[j] != end[j]) {
                std::string tmp(start);
                std::swap(tmp[index], tmp[j]);
                layerHeight = std::min(layerHeight, dfs(tmp, end, visitedWeight, index + 1) + 1);
            }
        }
        visitedWeight[start] = layerHeight;
        return layerHeight;
    }
};

class SolutionDFS {
public:
    int kSimilarity(std::string A, std::string B) {
        // plagiarizing from https://leetcode.com/problems/k-similar-strings/discuss/140299/C%2B%2B-6ms-Solution
        for (int i = 0; i < A.size(); i++) {
            if (A[i] == B[i]) {
                continue;
            }
            std::vector<int> matches;
            for (int j = i + 1; j < A.size(); j++) {
                if (A[j] == B[i] && A[j] != B[j]) {
                    matches.push_back(j);
                    if (A[i] == B[j]) {
                        swap(A[i],A[j]);
                        return 1 + kSimilarity(A.substr(i + 1), B.substr(i + 1));
                    }
                }
            }

            int best=A.size()-1;
            std::array<bool, b> visited; // default set to false;
            // visited.fill(false);

            for (int j: matches) {
                if (visited[B[j] - 'a']) {
                    continue;
                }
                visited[B[j] - 'a'] = true;
                swap(A[i],A[j]);
                best = std::min(best, 1 + kSimilarity(A.substr(i+1), B.substr(i+1)));
                swap(A[i],A[j]);
            }
            return best;
        }
        return 0;
    }
};
