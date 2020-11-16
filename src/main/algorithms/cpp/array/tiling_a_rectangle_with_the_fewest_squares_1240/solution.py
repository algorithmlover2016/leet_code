class Solution:
    # plagiarizing from https://www.youtube.com/watch?v=KRuwiEqY6j0
    def tilingRectangle(self, n: int, m: int) -> int:
        @lru_cache(None)
        def dp(skyLine):
            # first find the smallest height at this skyLine
            minHeight = sys.maxsize;
            start = 0
            for idx, height in enumerate(skyLine):
                if minHeight > height:
                    minHeight = height
                    start = idx;

            # all rectangle is full
            if minHeight == n:
                return 0

            ans = sys.maxsize
            nextSkyLine = list(skyLine)
            for end in range(start, m):
                if minHeight == skyLine[end]:
                    addHeight = end - start + 1
                    if minHeight + addHeight <= n:
                        # add a square with addHeight * addHeight
                        nextSkyLine[start: end + 1] = [addHeight + minHeight] * addHeight
                        ans = min(ans, dp(tuple(nextSkyLine)) + 1);
                else:
                    break

            return ans
        return dp(tuple([0] * m));
