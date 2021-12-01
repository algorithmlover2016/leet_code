#-*- coding:utf-8 -*-

# because bigInt in c++ is not supported, so I will copy the original codes from website directly
# BinarySearch with Rabin-Karp, reference to https://leetcode.com/problems/longest-duplicate-substring/discuss/695029/Python-Binary-search-O(n-log-n)-average-with-Rabin-Karp-explained

from typing import DefaultDict


class Solution:
    def RabinKarp(self,text, M, q):
        if M == 0: return True
        # h means the left mostest position need shifting. 256 = (1 << 8), h = (1 << (8 * (M - 1))), each digit is represented by 256-decimal
        h, t, d = (1<<(8*M-8))%q, 0, 256

        dic = DefaultDict(list)

        for i in range(M): 
            t = (d * t + ord(text[i]))% q

        dic[t].append(i-M+1)

        for i in range(len(text) - M):
            t = (d*(t-ord(text[i])*h) + ord(text[i + M]))% q
            for j in dic[t]:
                if text[i+1:i+M+1] == text[j:j+M]:
                    return (True, text[j:j+M])
            dic[t].append(i+1)
        return (False, "")

    def longestDupSubstring(self, S):
        beg, end = 0, len(S)
        q = (1<<31) - 1 
        Found = ""
        while beg + 1 < end:
            mid = (beg + end)//2
            isFound, candidate = self.RabinKarp(S, mid, q)
            if isFound:
                beg, Found = mid, candidate
            else:
                end = mid

        return Found

# reference to https://leetcode.com/problems/longest-duplicate-substring/discuss/290871/Python-Binary-Search
import functools
class SolutionLee215:
    def longestDupSubstring(self, S):
       A = [ord(c) - ord('a') for c in S]
       mod = 2**63 - 1

       def test(L):
           p = pow(26, L, mod)
           cur = functools.reduce(lambda x, y: (x * 26 + y) % mod, A[:L], 0)
           seen = {cur}
           for i in range(L, len(S)):
               cur = (cur * 26 + A[i] - A[i - L] * p) % mod
               if cur in seen: return i - L + 1
               seen.add(cur)
       res, lo, hi = 0, 0, len(S)
       while lo < hi:
           mi = (lo + hi + 1) / 2
           pos = test(mi)
           if pos:
               lo = mi
               res = pos
           else:
               hi = mi - 1
       return S[res:res + lo]