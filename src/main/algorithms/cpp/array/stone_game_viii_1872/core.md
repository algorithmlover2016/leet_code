according to https://leetcode.com/problems/stone-game-viii/discuss/1224640/C%2B%2BPython-DP-O(N)-time-O(1)-space-(2-lines-1-line) analysis:
dp[N-1] means that choosing the (N-1)th element (0-index), which is not statisfied the problem request.
dp[N - 2] means that choosing the (N - 2)th element (0-index) as the next player starting index and til to (N - 1) element.
    Then according to the request, the player must select at least two elements. So the player will select all the elements left.
    If that, the player can get the only score with number prefix[N-1] (all the sum of the input stones)
dp[i] means that if the player start from i to N - 1 (included), what is the maximum score. He can make any choice from i to N - 1,
    and the index which gets the maximum score is the target index. dp[i] = max(prefix[j] - dp[j]) for i < j <= N - 2.
    Take one more attention, if we start from i, then the score will be prefix[N - 1] which is dp[N - 2]. It means that if we know the dp[i + 1],
    then we just do one more compution of (prefix[i + 1] - dp[i + 1]) and compare it with dp[i + 1].