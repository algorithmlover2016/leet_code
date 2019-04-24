class Solution {
public:
    int magicalString(int n) {
        // copying method from https://leetcode.com/problems/magical-string/discuss/96408/Short-C%2B%2B
        string S("122");
        int index = 2;
        while (S.size() <= n) {
            // index always is smaller S.size()
            // for each loop, the next element is determined by S.back()
            // the length of the next elements is determined by S[index]
            S += string(S[index++] - '0', S.back() ^ 3);
            // std::cout << "S: " << S << std::endl;
        }
        return count(S.begin(), S.begin() + n, '1');
        
    }
};
