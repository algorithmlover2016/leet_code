# Solution Q&A: SOS DP Explanation

This document summarizes the explanation of the Sum Over Subsets (SOS) Dynamic Programming logic used in `solution.cpp`.

## 1. What is the First Loop doing?

```cpp
// 3. dp[mask] = number of array elements exactly equal to mask
vector<int> dp(totalMasks, 0);
for (int x : nums) dp[x]++;

for (int bit = 1; bit < totalMasks; bit <<= 1)
    for (int mask = 0; mask < totalMasks; mask++)
        if (mask & bit)
            dp[mask] += dp[mask ^ bit];
```

**Function:** This calculates the **SOS DP (Sum Over Subsets)**, also known as high-dimensional prefix sum.

**Meaning:**
- **Initial:** `dp[mask]` counts elements in `nums` equal to `mask`.
- **After Loop:** `dp[mask]` counts how many elements in `nums` are a **submask** of `mask`.
  - A number `x` is a submask of `mask` if `(x & mask) == x`.
  - Effectively, it sums up the initial counts of all `x` such that `x ⊆ mask`.

## 2. What exactly is a "Submask"?

In the context of bitmasks, $A$ is a submask of $B$ if all bits set to 1 in $A$ are also set to 1 in $B$.
Mathematically equivalent identities:
- `x & mask == x`
- `x | mask == mask`
- The set of bits in `x` is a subset of the bits in `mask`.

## 3. How does iterating single bits cover all subsets?

The code iterates `bit` from 1, 2, 4... This works via **propagation**.
- When processing `bit = 1`: We combine counts for the 0th dimension. `dp[...1]` collects values from `dp[...0]`.
- When processing `bit = 2`: We combine counts for the 1st dimension. Since `dp[...01]` already collected `dp[...00]`, adding `dp[...01]` to `dp[...11]` effectively propagates the sum.
It's like rolling a snowball; each layer adds a new dimension of combinations, eventually covering all $2^N$ subsets.

## 4. Can we swap the loops?

**Q:** Can we put `mask` loop outside and `bit` loop inside?
**A: NO.** This would cause **double counting**.
- Example: `dp[11]` needs values from `00`, `01`, `10`.
- If `mask` is outer: When updating `dp[11]`, you might add `dp[01]` (which contains `00`) and then `dp[10]` (which also contains `00`). The value of `00` gets added twice.
- **Rule:** The dimension loop (`bit`) must be the **outer** loop to ensure each dimension is folded in exactly once.

**Q:** Can we reverse the inner `mask` loop order?
**A: YES.** Inside the bit loop, the source data (`mask` with bit 0) is separate from target data (`mask` with bit 1). The order of updates within the same bit layer doesn't matter.

**Q:** Can we reverse the outer `bit` loop order?
**A: YES.** SOS DP is dimension-independent. You can process dimensions (bits) in any order (0 to N, or N to 0), just like you can calculate 2D prefix sums by doing rows then columns, or columns then rows.

## 5. What is the full logic flow?

```cpp
// A. SOS DP (Forward)
for (int bit...) dp[mask] += dp[mask^bit];

// B. Combinatorics
for (int mask...) dp[mask] = pow2[dp[mask]] - 1;

// C. Inverse SOS DP (Backward)
for (int bit...) dp[mask] -= dp[mask^bit];
```

1.  **SOS DP (Sum)**:
    - Calculates: "How many elements in `nums` satisfy `element & mask == element`?"
    - Result: `k = count of valid elements` for each mask.

2.  **Combinatorics ($2^k - 1$)**:
    - Calculates: "How many non-empty subsequences can we form using ONLY elements that are submasks of `mask`?"
    - Since any OR combination of subsets of `mask` is still a subset of `mask`, this step counts all subsequences whose OR sum is a **subset** of `mask`.

3.  **Inverse SOS DP (Difference)**:
    - Applies Inclusion-Exclusion Principle.
    - Converts: "Count of subsequences with OR sum $\subseteq$ mask" $\to$ "Count of subsequences with OR sum **exactly equal to** mask".
    - It subtracts the cases where the OR sum is a strict subset (missing at least one bit).