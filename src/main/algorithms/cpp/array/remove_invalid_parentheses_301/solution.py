#-*- coding:utf-8 -*-
# https://leetcode.com/problems/remove-invalid-parentheses/discuss/75028/Short-Python-BFS

class Solution:
    def removeInvalidParentheses(self, s : str) -> list[str]:
        level = {s}
        while True:
            valid = []
            for s in level:
                try:
                    eval('0,' + "".join(filter('()'.count, s)).replace(')', '),'))
                    valid.append(s)
                except:
                    pass
            if valid:
                return valid
            level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}

class Solution2:
    def removeInvalidParentheses(self, s) -> list[str]:
        def isvalid(s):
            ctr = 0
            for c in s:
                if c == '(':
                    ctr += 1
                elif c == ')':
                    ctr -= 1
                    if ctr < 0:
                        return False
            return ctr == 0
        level = {s}
        while True:
            valid = list(filter(isvalid, level))
            if valid:
                return valid
            level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}
    
class Solution3:
    def removeInvalidParentheses(self, s):
        def isvalid(s):
            try:
                eval('0,' + "".join(filter('()'.count, s)).replace(')', '),'))
                return True
            except:
                pass
        level = {s}
        while True:
            valid = list(filter(isvalid, level))
            if valid:
                return valid
            level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}

class Solution4:
    def removeInvalidParentheses(self, s):
        def isvalid(s):
            s = "".join(filter('()'.count, s))
            while '()' in s:
                s = s.replace('()', '')
            return not s
        level = {s}
        while True:
            valid = list(filter(isvalid, level))
            if valid:
                return valid
            level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}

if __name__ == "__main__":
    print("begin")
    obj = Solution()
    print("debug")
    print(obj.removeInvalidParentheses("()())()"))
    print("solution done")

    obj = Solution2()
    print(obj.removeInvalidParentheses("()())()"))
    print("solution2 done")
    obj = Solution3()
    print(obj.removeInvalidParentheses("()())()"))
    print("solution3 done")
    obj = Solution4()
    print(obj.removeInvalidParentheses("()())()"))
    print("solution4 done")
