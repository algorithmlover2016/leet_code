#include "../../head.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        if (n < 2) return 0;
        
        // Flatten all lists into one sorted structure to find medians efficiently
        struct Element {
            int val;
            int list_idx;
            bool operator<(const Element& other) const {
                return val < other.val;
            }
        };
        
        // Pre-allocate to avoid reallocations, total elements <= 2000
        vector<Element> all_elements;
        all_elements.reserve(2000); 
        
        vector<int> lens(n);
        for(int i=0; i<n; ++i) {
            lens[i] = lists[i].size();
            for(int val : lists[i]) {
                all_elements.push_back({val, i});
            }
        }
        
        // Sort all elements once: O(TotalLen * log(TotalLen))
        sort(all_elements.begin(), all_elements.end());
        
        int total_masks = 1 << n;
        
        // dp[mask] stores the min cost to merge the subset of lists represented by mask
        vector<long long> dp(total_masks, LLONG_MAX);
        
        // Precompute length and median for every mask
        vector<int> mask_len(total_masks);
        vector<int> mask_median(total_masks);
        
        // O(2^n * TotalLen) - with N=12, TotalLen=2000, approx 8*10^6 ops
        for (int m = 1; m < total_masks; ++m) {
            int len = 0;
            // Calculate total length for this mask
            for(int i=0; i<n; ++i) {
                if((m >> i) & 1) {
                    len += lens[i];
                }
            }
            mask_len[m] = len;
            
            // Find median for this mask
            // The median of the merged list is the element at index (len - 1) / 2 in the sorted combined list
            int median_target_idx = (len - 1) / 2;
            int current_count = 0;
            
            for(const auto& el : all_elements) {
                // If this element belongs to one of the lists in the current mask
                if((m >> el.list_idx) & 1) {
                    if(current_count == median_target_idx) {
                        mask_median[m] = el.val;
                        break;
                    }
                    current_count++;
                }
            }
        }
        
        // Base cases: A single list is already "merged" with cost 0
        for(int i=0; i<n; ++i) {
            dp[1 << i] = 0;
        }
        
        // DP Transitions: O(3^n)
        for (int m = 1; m < total_masks; ++m) {
            // Skip base cases (single bits)
            if ((m & (m - 1)) == 0) continue;
            
            // The cost to merge two sub-components 's' and 'other' (where s | other = m) is:
            // cost_to_form_s + cost_to_form_other + len(s) + len(other) + abs(median(s) - median(other))
            // Note: len(s) + len(other) == mask_len[m]
            
            int current_len_add = mask_len[m];
            
            // Iterate over all proper submasks s of m
            // Loop goes from largest submask down to 1
            for (int s = (m - 1) & m; s > 0; s = (s - 1) & m) {
                int other = m ^ s;
                
                // Since we iterate m from 1 to total_masks, smaller masks s and other are already computed
                if (dp[s] != LLONG_MAX && dp[other] != LLONG_MAX) {
                    long long cost = dp[s] + dp[other] + current_len_add + abs(mask_median[s] - mask_median[other]);
                    if (cost < dp[m]) {
                        dp[m] = cost;
                    }
                }
            }
        }
        
        return dp[total_masks - 1];
    }
};