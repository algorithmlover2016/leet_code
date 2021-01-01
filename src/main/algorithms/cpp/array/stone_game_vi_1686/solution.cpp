#include "../../head.h"


#define DEBUG
class SolutionWrongAnswer {
    // forget to consider the optimal selection
public:
    int stoneGameVI(std::vector<int> const & aliceValues,
            std::vector<int> const & bobValues) {
        if (aliceValues.empty() || bobValues.empty()) {
            return 0;
        }
        int const aliceValuesSize = aliceValues.size();
        int const bobValuesSize = bobValues.size();
        if (aliceValuesSize != bobValuesSize) {
            return 0;
        }

        std::vector<bool>  used(aliceValuesSize, false);

        int ans = 0;
        dpHelp(used, aliceValues, bobValues, 0, 0, 0, ans);
        return ans;
    }
    void dpHelp(std::vector<bool> & used,
            std::vector<int> const & aliceValues,
            std::vector<int> const & bobValues,
            int cnt,
            int alicePoints,
            int bobPoints,
            int & ans) {
        if (cnt == used.size()) {
            #ifdef DEBUG
            std::cout << "aPoint, bPoint: " << alicePoints << ",\t" << bobPoints << "\n";
            #endif
            ans = std::max(ans, alicePoints > bobPoints ? 1 : (alicePoints == bobPoints ? 0 : -1));
            return;
        }
        for (int idx = 0; idx < used.size(); idx++) {
            if (!used[idx]) {
                if (cnt & 0x01) {
                    bobPoints += bobValues[idx];
                } else {
                    alicePoints += aliceValues[idx];
                }
                used[idx] = true;
                dpHelp(used, aliceValues, bobValues, cnt + 1, alicePoints, bobPoints, ans);
                used[idx] = false;
            }

        }
    }
};

// #define DEBUG
class Solution {
public:
    int stoneGameVI(std::vector<int> const & aliceValues,
            std::vector<int> const & bobValues) {
        // plagiarizing from https://leetcode.com/problems/stone-game-vi/discuss/969574/JavaC%2B%2BPython-Sort-by-Value-Sum
        if (aliceValues.empty() || bobValues.empty()) {
            return 0;
        }
        int const aliceValuesSize = aliceValues.size();
        int const bobValuesSize = bobValues.size();
        if (aliceValuesSize != bobValuesSize) {
            return 0;
        }
        std::vector<std::vector<int>> comb;

        for (int idx = 0; idx < aliceValuesSize; idx++) {
            comb.push_back({{-aliceValues[idx] - bobValues[idx], aliceValues[idx], bobValues[idx]}});
        }
        std::sort(comb.begin(), comb.end());
        std::array<int, ANS_LEN> ans = {0, 0} ;
        for (int idx = 0; idx < aliceValuesSize; idx++) {
            ans[idx & 0x01] += comb[idx][START_IDX + (idx & 0x01)];
        }
        #ifdef DEBUG
        std::cout << "a, b: " << ans[ANS_ALICE_IDX] << ",\t" << ans[ANS_BOB_IDX] << "\n" ;
        #endif
        return ans[ANS_ALICE_IDX] > ans[ANS_BOB_IDX] ? 1 : (ans[ANS_ALICE_IDX] == ans[ANS_BOB_IDX] ? 0 : -1);
    }

private:
    static int const COMB_ELE_LEN = 3;
    static int const START_IDX = 1;

    static int const ANS_LEN = 2;
    static int const ANS_ALICE_IDX = 0;
    static int const ANS_BOB_IDX = 1;
};

// have not understand
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

static const auto fast = []()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); return 0;
} ();

void RadixSort(int* nums, const size_t n) {
   const size_t radix_bits = 8;
   const size_t mask = (1U << radix_bits) - 1U;
   size_t count[1 << radix_bits];
   int *aux = (int*)malloc(n * sizeof(nums[0]));

   for (size_t shift = 0; shift < sizeof(nums[0]) * 8; shift += radix_bits) {
      memset(count, 0, sizeof(count));

      for (size_t i = 0; i < n; i++)    // Counting sort
         count[(nums[i] >> shift) & mask]++;

      // Calculate buckets positions (cumulative sum)
      for (size_t i = 0; i < mask;) {
         size_t temp = count[i++];
         count[i] += temp;
      }

      // Put buckets content into temporary array
      for (size_t i = n; i--; ) {
         aux[--count[(nums[i] >> shift) & mask]] = nums[i];
      }

      int *temp = aux;
      aux = nums;
      nums = temp;
   }
   free(aux);
}

inline int Sign(int value) {
  return (value > 0) - (value < 0);
}

class Solution {
public:
    int stoneGameVI(vector<int>& alice_values, vector<int>& bob_values) {
      const int kLength = alice_values.size();
      std::vector<int> true_values(kLength);
      for (int index = 0; index < kLength; ++index) {
          true_values[index] = alice_values[index] + bob_values[index];
      }
      //std::sort(true_values.begin(), true_values.end());
      RadixSort(true_values.data(), kLength);
      /*for (int index = 0; index < kLength; ++index) {
        if (index & 1) {
          true_values[index] = -true_values[index];
        }
      }*/
      for (int i = kLength, t = 0; i--; t ^= 2) {
          true_values[i] *= 1 - t;
      }
      return Sign(std::accumulate(true_values.begin(), true_values.end(), 0)
          + std::accumulate(alice_values.begin(), alice_values.end(), 0)
          - std::accumulate(bob_values.begin(), bob_values.end(), 0));
    }
};
