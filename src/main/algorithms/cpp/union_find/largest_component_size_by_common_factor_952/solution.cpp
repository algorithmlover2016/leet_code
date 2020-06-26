#include "../../head.h"


class SolutionTLE {
public:
    int largestComponentSize(std::vector<int> const & A) {
        std::unordered_map<int, std::vector<int>> graph;
        for (int index = 0; index < A.size(); index++) {
            for (int inner = index + 1; inner < A.size(); inner++) {
                if (gcd(A[index], A[inner]) > 1) {
                    graph[A[index]].emplace_back(A[inner]);
                    graph[A[inner]].emplace_back(A[index]);
                }
            }
        }
        std::cout << "\nsize: " << graph.size() << "\t";
        int res = 0;
        std::set<int> visited;
        for (auto const & ele : graph) {
            if (visited.find(ele.first) != visited.end()) {
                continue;
            }
            std::cout << "ele: " << ele.first << "\t";
            int curRes = 0;
            std::queue<int> todo;
            todo.emplace(ele.first);
            while (todo.size()) {
                int cur = todo.front(); todo.pop();
                if (visited.find(cur) != visited.end()) {
                    continue;
                }
                curRes++;
                visited.emplace(cur);
                for (int const linked : graph[cur]) {
                    if (visited.find(linked) == visited.end()) {
                        todo.emplace(linked);
                    }
                }
            }
            res = std::max(res, curRes);
        }
        return res;
    }
private:
    int gcd(int a, int b) {
        if (0 == b) {
            return a;
        }
        return gcd(b, a % b);
    }
};

class Solution {
public:
    int largestComponentSize(std::vector<int> const & A) {
        if (A.size() < 2) {
            return static_cast<int>(int(A.size()));
        }
        std::set<int> primes;
        std::vector<int> orderPrimes;
        const int maxNum = 100000;
        std::vector<bool> primesFlag(maxNum + 1, true);
        for (int index = 2; index <= maxNum; index++) {
            if (!primesFlag[index]) {
                continue;
            }
            primes.insert(index);
            orderPrimes.push_back(index);
            for (int subIndex = 2; subIndex * index <= maxNum; subIndex++) {
                primesFlag[subIndex * index] = false;
            }
        }
        primesFlag.clear();
        std::vector<int> primes2Index(maxNum + 1, -1);
        std::vector<int> parentIndex(A.size(), 0);
        std::vector<int> countDistance(A.size(), 1);
        for (int index = 0; index < A.size(); index++) {
            parentIndex[index] = index;
        }

        int maxCntRet = 0;
        for (int index = 0; index < A.size(); index++) {
            int ele = A[index];
            int sqrtedNum = int(std::sqrt(ele));
            for (int prime : orderPrimes) {
                if (primes.count(ele)) {
                    prime = ele;
                } else if (prime > sqrtedNum) {
                    break;
                }
                if (0 == ele % prime) {
                    if (primes2Index[prime] > -1) {
                        maxCntRet = std::max(maxCntRet, unionAndCount(parentIndex, countDistance, primes2Index[prime], index));
                    }
                    primes2Index[prime] = index;
                    do {
                        ele /= prime;
                    } while (0 == ele % prime);
                }
                if (1 == ele) {
                    break;
                }
            }
        }
        return maxCntRet;

    }
    int unionAndCount(std::vector<int> & parentIndex, std::vector<int> & countDistance,
                       int left, int right) {
        int leftRoot = findParent(parentIndex, left), rightRoot = findParent(parentIndex, right);
        if (leftRoot == rightRoot) {
            return countDistance[leftRoot];
        }
        int count = countDistance[leftRoot] + countDistance[rightRoot];
        parentIndex[leftRoot] = rightRoot;
        countDistance[rightRoot] = count;
        return count;

    }
    int findParent(const std::vector<int> & parentIndex, int index) {
        while (parentIndex[index] != index) {
            index = parentIndex[index];
        }
        return index;
    }
};

class SolutionBetterRuntime {
public:

    int par[200005], sz[200005];
    int adj[200005];

    void init(int n) {
        for (int i = 0; i <= n; i++) {
            par[i] = i;
            sz[i] = 1;
            adj[i] = -1;
        }
    }

    void init(vector <int> &prime){
        prime.resize(100005,0);
        for (int i = 2;i * i < 100005; i++) {
            if (prime[i] == 0) {
                for(int j = i * i; j < 100005; j += i) {
                    prime[j] = i;
                }
            }
        }
        for (int i = 2; i < 100005; i++) {
            if(prime[i] == 0) {
                prime[i] = i;
            }
        }
    }

    int root(int x) {
        while (par[x] != x) {
            x=par[x];
        }
        return x;
    }

    void add(int x,int y) {
        int rx,ry;
        rx = root(x);
        ry = root(y);
        if(rx == ry) {
            return;
        }
        if(sz[rx] < sz[ry]) {
            sz[ry] += sz[rx];
            par[rx] = ry;
        } else{
            sz[rx] += sz[ry];
            par[ry] = rx;
        }
    }

    int largestComponentSize(std::vector<int> const & A) {
        int n = *std::max_element(std::begin(A), std::end(A));
        init(n);
        static std::vector<int> prime;
        if (prime.empty()) {
            init(prime);
        }
        for (int x : A) {
            int y = x;
            while (x > 1) {
                if(adj[prime[x]] == -1)
                    adj[prime[x]] = y;
                add(adj[prime[x]], y);
                int p = prime[x];
                while (prime[x] == p) {
                    x/=p;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < A.size(); i++) {
            ans = std::max(ans, sz[root(A[i])]);
        }
        return ans;
    }
};
