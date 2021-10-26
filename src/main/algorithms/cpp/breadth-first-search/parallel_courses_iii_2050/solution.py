from collections import defaultdict
from functools import cache, lru_cache


class Solution:
    def minimumTime(self, n, R, T):
        G = defaultdict(list)
        for x, y in R:
            G[y].append(x)

        @lru_cache(None)
        def dp(node):
            return T[node - 1] + max([dp(child) for child in G[node]] + [0])

        return max(dp(i) for i in range(1, n+1))

class Solution:
    def minimumTime(self, n, R, T):
        G = defaultdict(list)
        for x, y in R: G[y] += [x]
        dp = cache(lambda x:T[x - 1] + max([dp(c) for c in G[x]] + [0]))
        return max(dp(i+1) for i in range(n))