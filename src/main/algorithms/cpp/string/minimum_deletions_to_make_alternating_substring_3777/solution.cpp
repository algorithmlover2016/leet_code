#include "../../head.h"

// Time Complexity: O(Q * log N)
// Space Complexity: O(N)
class Solution {
private:
    vector<int> bit;
    int n;

    // Update BIT at index 'idx' by 'val'
    // internal BIT is 1-based, input idx is 0-based
    void add(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    // Query prefix sum up to index 'idx'
    int query(int idx) {
        int sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            sum += bit[idx];
        }
        return sum;
    }

public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        n = s.length();
        // Since we track adj pairs from 0 to n-2, size n is sufficient. 
        // We use size n+1 for 1-based indexing convenience/safety.
        bit.assign(n + 1, 0);

        // Initialize BIT with existing adjacent identical characters
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                add(i, 1);
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int type = q[0];
            if (type == 1) {
                int idx = q[1];

                // Before flip: remove contribution of adjacent pairs involving s[idx]
                if (idx > 0 && s[idx] == s[idx - 1]) {
                    add(idx - 1, -1);
                }
                if (idx < n - 1 && s[idx] == s[idx + 1]) {
                    add(idx, -1);
                }

                // Flip the character: 'A'^3 = 'B', 'B'^3 = 'A' (Assuming ASCII)
                // Or simply use ternary operator for safety
                s[idx] = (s[idx] == 'A' ? 'B' : 'A');

                // After flip: add contribution of adjacent pairs
                if (idx > 0 && s[idx] == s[idx - 1]) {
                    add(idx - 1, 1);
                }
                if (idx < n - 1 && s[idx] == s[idx + 1]) {
                    add(idx, 1);
                }

            } else {
                int l = q[1];
                int r = q[2];
                // Concept: Min deletions to make string alternating is equal to
                // the number of adjacent equal pairs.
                // We need sum of pairs in range [l, r-1]
                if (l >= r) {
                    ans.push_back(0);
                } else {
                    ans.push_back(query(r - 1) - query(l - 1));
                }
            }
        }
        return ans;
    }
};