#include "../../head.h"
 

class Solution {
public:
    int minSwapsCouples(std::vector<int> const & row) {
        // plagiarizing from https://leetcode.com/problems/couples-holding-hands/discuss/113362/JavaC%2B%2B-O(N)-solution-using-cyclic-swapping
        int size = row.size();
        std::vector<int> partner(size);
        std::vector<int> position(size);
        for (int index = 0; index < size; index++) {
            partner[row[index]] = (row[index] & 0x01) ? row[index] - 1 : row[index] + 1;
            position[row[index]] = index;
        }
        int ans = 0;
        for (int index = 0; index < size; index++) {
            for (int partnerNeighborIndex = partner[position[partner[row[index]]]];
                    index != partnerNeighborIndex;
                    partnerNeighborIndex = partner[position[partner[row[index]]]]) {
                std::swap(row[index], row[partnerNeighborIndex]);
                std::swap(position[row[index]], position[row[partnerNeighborIndex]]);
                ans++;
            }
        }
        return ans;

    }
};

class Solution {
public:
    int minSwapsCouples(std::vector<int> const & row) {
        int res = 0, n = row.size();
        for (int i = 0; i < n; i += 2) {
            if (row[i + 1] == (row[i] ^ 1)) {
                continue;
            }
            ++res;
            for (int j = i + 1; j < n; ++j) {
                if (row[j] == (row[i] ^ 1)) {
                    row[j] = row[i + 1];
                    row[i + 1] = row[i] ^ 1;
                    break;
                }
            }
        }
        return res;
    }
};

class Solution {
public:
    std::vector<int> parent;

    int findset(int v) {
        if (parent[v]==v) {
            return v;
        }
        return parent[v] = findset(parent[v]);
    }

    int minSwapsCouples(std::vector<int> const & row) {
        ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
        parent=std::vector<int>(row.size());
        for (int i = 0; i < row.size(); i += 2) {
            parent[row[i]] = row[i];
            parent[row[i + 1]] = row[i];
        }
        int ctr=0,x,y;
        for (int i = 0;i < row.size(); i += 2) {
            x = findset(i);
            y = findset(i + 1);
            if (x != y) {
                ctr += 1;
                parent[x] = y;
            }
        }
        return ctr;
    }
};
