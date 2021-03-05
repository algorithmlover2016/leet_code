#include "../../head.h"

class SolutionPlagiarizeOther {
public:
    std::string nearestPalindromic(std::string const & n) {
        int l = n.size() / 2;
        std::string left = n.substr(0, l);
        std::string mid = n.substr(l, n.size() - 2 * l);
        int ln = left.empty() ? 0 : std::stoi(left);
        long num = std::stol(n);
        long n3 = std::stol(left + mid + std::string(left.rbegin(), left.rend()));
        long lo, hi;
        if (n3 < num) {
            lo = n3;
        } else {
            std::string left1 = left, mid1 = mid;
            if (n.size() % 2 == 0) {
                // mid = ""
                int ln1 = ln - 1;
                left1 = ln1 == 0 ? "" : std::to_string(ln1);
                if (left1.size() < l) {
                    mid1 = "9";
                }
            } else if (mid1 == "0") {
                int ln1 = ln - 1;
                left1 = ln1 == 0 ? "" : to_string(ln1);
                if (left1.size() == l) mid1 = "9";
                else {
                    left1 += '9';
                    mid1 = "";
                }
            } else {
                mid1 = std::to_string(mid1[0] - '0' - 1);
            }
            lo = std::stol(left1 + mid1 + std::string(left1.rbegin(), left1.rend()));
        }
        if (n3 > num) {
            hi = n3;
        } else {
            std::string left2 = left, mid2 = mid;
            if (n.size() % 2 == 0) {
                // mid = "";
                int ln2 = ln + 1;
                left2 = std::to_string(ln2);
                if (left2.size() > l) {
                    left2 = left2.substr(0, l);
                    mid2 = "0";
                }
            } else if (mid2 == "9") {
                int ln2 = ln + 1;
                left2 = std::to_string(ln2);
                if (left2.size() == l) {
                    mid2 = "0";
                } else {
                    mid2 = "";
                }
            } else {
                mid2 = std::to_string(mid2[0] - '0' + 1);
            }
            hi = std::stol(left2 + mid2 + std::string(left2.rbegin(), left2.rend()));
        }
        return num - lo > hi - num ? std::to_string(hi) : std::to_string(lo);
    }
};

class Solution {
public:
    std::string nearestPalindromic(std::string const & n) {
        if (n.size() == 0) {
            return "";
        }
        if(n.size() == 1) {
            return std::to_string(abs(std::stol(n) - 1));
        }

        std::string normal = normalize(n);
        long long int nNum = std::stoll(n);
        long long int changeNum = static_cast<long long int>(pow(10, n.size()/2));
        long long int modNum = nNum % changeNum;
        long long int upperNum = nNum + changeNum - modNum;
        std::string upper = normalize(std::to_string(upperNum));
        long long int lowerNum = nNum - 1 - modNum;
        std::string lower = normalize(std::to_string(lowerNum));
        long long int upperDiff = std::stoll(upper) - nNum;
        long long int lowerDiff = nNum - std::stoll(lower);
        long long int normalDiff = std::abs(std::stoll(normal) - nNum);
        std::string ans = lower;
        // std::cout << "normal: " << normal << " diff: " << normalDiff << "\n"
        //     << "upper: " << upper << " diff: " << upperDiff << "\n"
        //     << "lower: " << lower << " diff: " << lowerDiff << "\n";
        if (upperDiff < lowerDiff) {
            ans  = upper;
        }
        if (normalDiff > 0 && normalDiff < lowerDiff && normalDiff <= upperDiff) {
            ans = normal;
        }
        return ans;
    }

    std::string normalize(std::string const & n) {
        std::string ans(n);
        if (n.size() < 2) {
            return ans;
        }
        for (int i = 0, j = n.size() - 1; i < j; i++, j--) {
            if (n[i] != n[j]) {
                ans[j] = ans[i];
            }
        }
        return ans;

    }
    bool isPalindromic(std::string const & str) {
        if (str.size() < 2) {
            return true;
        }
        for (int i = 0, j = str.size() - 1; i < j; i++, j--) {
            if (str[i] != str[j]) {
                return false;
            }
        }
        return true;
    }
};
