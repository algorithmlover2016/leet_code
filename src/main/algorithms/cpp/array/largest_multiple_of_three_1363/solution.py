class Solution:
    def largestMultipleOfThree(self, digits: List[int]) -> str:
        # plagiarizing from https://leetcode.com/problems/largest-multiple-of-three/discuss/517628/Python-Basic-Math
        dp = [-1,-1,-1]
        for a in sorted(digits)[::-1]:
            for x in dp[:] + [0]:
                # the y will be very large, for example, len(digits) = 10 ^ 4, each digit is 9.
                y = x * 10 + a
                # print(x, a, y, y % 3)
                dp[y % 3] = max(dp[y % 3], y)
        return str(dp[0]) if dp[0] >= 0 else ""
