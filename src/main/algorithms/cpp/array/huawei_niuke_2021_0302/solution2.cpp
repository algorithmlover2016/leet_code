#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


// #define DEBUG
int main() {
    std::map<std::string, std::map<int, int>> timeMap;
    std::string ss;
    while (true) {
        std::getline(cin, ss);
        if (ss.empty()) {
            break;
        }
        // process input str
        std::string newStr;
        std::string msStr;
        for (int idx = 0; idx < ss.size(); idx++) {
            if (ss[idx] >= '0' && ss[idx] <= '9') {
                newStr += ss[idx];
            } else if (ss[idx] == '.') {
                msStr = ss.substr(idx + 1);
                break;
            }
        }
        int msNum = std::stoi(msStr);

#ifdef DEBUG
        std::cout << newStr << "\t" << msNum << "\n";
#endif

        /*
        if (timeMap.find(newStr) == timeMap.end()) {
            timeMap[newStr].emplace(std::make_pair(msNum, 0));
        }
        */

        timeMap[newStr][msNum]++;
    }

    int ans = 0;
    for (auto const & [key, val] : timeMap) {
        if (!val.empty()) {
            ans += val.begin()->second;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
