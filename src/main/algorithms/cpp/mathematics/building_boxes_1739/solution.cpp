#include "../../head.h"


class Solution {
public:
    int minimumBoxes(int n) {
        // plagiairizing from https://youtu.be/h3k-xR9qHRs
        /*
        layer = 1;
        cur + (layer + 1) * (layer + 1 + 1) / 2 <= n;
        cur  += ;
        layer++;

        layer2 = 0
        while cur < n;
        layer2++;
        cur +
        */
        int curTotal = 0;
        int layerFull = 0;
        while (curTotal + (layerFull + 1) * (layerFull + 1 + 1) / 2 <= n) {
            curTotal += (layerFull + 1) * (layerFull + 1 + 1) / 2;
            layerFull++;
        }

        int redundant = 0;
        while (curTotal < n) {
            curTotal += ++redundant;
        }
        return (layerFull) * (layerFull + 1) / 2 + redundant;
    }
};

class Solution {
public:
    // 1 + (1 + 2)
    // 1 + (1 + 2) + (1 + 2 + 3)
    // 1 + (1 + 2) + (1 + 2 + 3) + (1 + 2 + 3 + 4)
    int minimumBoxes(int n) {
        int curr_total = 0;
        int curr_layer_max = 0;
        int curr_layer_sum = 0;

        while (curr_total < n) {
            curr_layer_max++;
            curr_layer_sum += curr_layer_max;
            curr_total += curr_layer_sum;
        }

        if (curr_total == n) {
            return curr_layer_sum;
        }

        // revert
        curr_total -= curr_layer_sum;
        curr_layer_sum -= curr_layer_max;

        int curr_step = 0;
        while (curr_total < n) {
            curr_total += ++curr_step;
        }

        // the boxes touching ground added in this layering is the same as the
        // curr_step
        return curr_layer_sum + curr_step;
    }
};
