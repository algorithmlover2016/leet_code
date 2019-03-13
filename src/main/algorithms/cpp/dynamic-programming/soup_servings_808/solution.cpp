#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    double soupServings(int N) {
        // if (N <= 0) {
        //     return 1;
        // }
        return N >= 4800 ? 1 : dp((N + 24) / 25, (N + 24) / 25);
    }
#ifndef USE_ARRAY
    double dp(int aLeft, int bLeft) {
        // std::cout << "aLeft: " << aLeft << " bLeft: " << bLeft << std::endl;
        if (0 == (aLeft | bLeft)) {
            return 0.5;
        } else if (0 == aLeft) {
            return 1.0;
        } else if (bLeft == 0) {
            return 0;
        } else {
            stringstream ss;
            ss << aLeft << "@" << bLeft;
            string key(ss.str());
            if (record.find(key) == record.end()) {
                record[key] = 0.25 * (
                    dp(aLeft > 4 ? aLeft - 4:0, bLeft > 0 ? bLeft : 0) +
                    dp(aLeft > 3 ? aLeft - 3:0, bLeft > 1 ? bLeft - 1 : 0) +
                    dp(aLeft > 2 ? aLeft - 2:0, bLeft > 2 ? bLeft - 2 : 0) +
                    dp(aLeft > 1 ? aLeft - 1:0, bLeft > 3 ? bLeft - 3: 0));
            }
            // std::cout << "key: " << key << " value: " << record[key] << std::endl;
            return record[key];
        }

    }
    private:
    unordered_map<string, double> record;
#else
    double dp(int a, int b){
        if (a <= 0 && b <=0 ) {
            return 0.5;
        } else if(a <= 0) {
            return 1;
        } else if(b <= 0) {
            return 0;
        } else if(m[a][b] > 0) {
            return m[a][b];
        } else {
            m[a][b] = 0.25 * (
                    dp(a - 4, b) +
                    dp(a - 3, b - 1) +
                    dp(a - 2, b - 2) +
                    dp(a - 1, b - 3)
                    );
        }
        return m[a][b];
    }
private:
    double m[200][200];
#endif
};
int main() {
    Solution a;

    std::cout << a.soupServings(660295675) << std::endl;
    return 0;
}
// g++ -std=c++11  -o main solution.cpp
