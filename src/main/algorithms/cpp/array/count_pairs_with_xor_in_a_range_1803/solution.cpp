#include "../../head.h"


class Solution {
private:
    static int const CHILDREN_LEN = 2;
    static int const MAX_NUM_BITS_LEN = 17;
    enum OPS {
        REMOVE = -1,
        ADD = 1,
    };
    struct BitTrie {
        std::array<BitTrie*, CHILDREN_LEN> bitChildren = {};
        int cnts = 0;
        void addOrRemoveNode(int node, OPS op, int bitPos = MAX_NUM_BITS_LEN) {
            cnts += op;
            if (0 <= bitPos) {
                bool leftOrRight = node & (1 << bitPos);
                if (nullptr == bitChildren[leftOrRight]) {
                    bitChildren[leftOrRight] = new BitTrie();
                }
                bitChildren[leftOrRight]->addOrRemoveNode(node, op, bitPos - 1);
            }
        }

        int match(int val, int bitPos = MAX_NUM_BITS_LEN) {
            if (0 > bitPos) {
                return 0;
            }
            bool leftOrRight = val & (1 << bitPos);
            if (nullptr != bitChildren[!leftOrRight] && 0 < bitChildren[!leftOrRight]->cnts) {
                // we can go through the other side of the tree to find the max XOR value from the cur node
                return (1 << bitPos) + bitChildren[!leftOrRight]->match(val, bitPos - 1);
            }
            return (nullptr == bitChildren[leftOrRight] ? 0 : bitChildren[leftOrRight]->match(val, bitPos - 1));
        }

        int countLessThan(int val, int limit, int bitPos = MAX_NUM_BITS_LEN) {
            if (0 > bitPos) {
                return 0;
            }
            int curBitVal = (1 << bitPos);
            bool valBit = val & curBitVal, limitBit = limit & curBitVal, nextLayer = (val xor limit) & curBitVal;
            return (limitBit && nullptr != bitChildren[valBit]) ? bitChildren[valBit]->cnts : 0 +
                    (nullptr != bitChildren[nextLayer] ? bitChildren[nextLayer]->countLessThan(val, limit, bitPos - 1) : 0);

        }
    };
public:
    int countPairs(std::vector<int> const & nums, int low, int high) {
        int const numsSize = nums.size();
        if (0 == numsSize) {
            return -1;
        }
        int ans = 0;
        for (int num : nums) {
            ans += bitTrieObj.countLessThan(num, high + 1) - bitTrieObj.countLessThan(num, low);
            bitTrieObj.addOrRemoveNode(num, OPS::ADD);
        }
        return ans;
    }
private:
    struct BitTrie bitTrieObj;
};