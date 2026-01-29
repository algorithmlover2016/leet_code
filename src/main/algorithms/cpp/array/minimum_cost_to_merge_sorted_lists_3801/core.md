# Minimum Cost to Merge Sorted Lists - Algorithm Analysis

## Problem Overview
We are given `N` sorted lists and need to merge them into a single sorted list. In each step, we pick two lists `a` and `b`, merge them, and the cost is `len(a) + len(b) + abs(median(a) - median(b))`. We want to minimize the total cost.

**Constraints:**
- `N <= 12` (Number of lists)
- Total elements `<= 2000`

## Naive Approach vs. Optimization
The original approach attempts to simulate every possible pair merge recursively. Since any two lists can be merged at any step, the number of possibilities is factorial in nature ($O(N! \cdot poly(N))$), leading to Time Limit Exceeded (TLE) for $N=12$.

### Key Insight
The cost of a merge depends on the **length** and **median** of the resulting list.
- **Length**: The length of a merged list is simply the sum of the lengths of its source lists.
- **Median**: Crucially, the median of a merged list depends **only** on the set of elements it contains. It does **not** depend on the order in which the smaller lists were merged to create it.

Because the state of a "merged list" is fully defined by the **subset of original lists** it contains, we can use **Dynamic Programming (DP) with Bitmasking**.

## Optimized Algorithm: Bitmask DP

### 1. State Representation
We use a bitmask (an integer from `0` to `2^N - 1`) to represent a subset of the original lists.
- If the $i$-th bit is set, the $i$-th list is included in this subset.
- `dp[mask]` stores the **minimum total cost** to merge all the lists represented by `mask` into a single list.

### 2. Precomputation
Before running the DP, we precompute two values for every possible `mask`:
- `mask_len[mask]`: The total number of elements in the subset.
- `mask_median[mask]`: The median value of all elements in the subset combined.
    - *Note*: Calculating the median efficiently is important. We can collect all elements into a single array with their source list index, sort them once, and then for each mask, iterate through this sorted array to find the element at the median index `(len-1)/2`.

**Time Complexity for Precomputation:** $O(2^N \cdot \text{TotalElements})$

### 3. DP Transitions
The target is to find `dp[(1<<N) - 1]`.
For a given `mask`, we consider it as the result of merging two smaller, disjoint subsets `subset` and `other` (where `subset | other == mask`).

The recurrence relation is:
$$dp[mask] = \min_{\text{subset} \subset \text{mask}} (dp[\text{subset}] + dp[\text{mask} \setminus \text{subset}] + \text{Cost}_{\text{merge}})$$

Where the merge cost at this specific step is:
$$\text{Cost}_{\text{merge}} = \text{mask\_len}[\text{mask}] + | \text{mask\_median}[\text{subset}] - \text{mask\_median}[\text{mask} \setminus \text{subset}] |$$

To implement this efficiently, we iterate `mask` from 1 to `2^N - 1`. For each `mask`, we iterate through its submasks. This is a standard technique that runs complexities of iterating submasks in $O(3^N)$.

**Time Complexity for DP:** $O(3^N)$

### 4. Complexity Summary
- **Time**: $O(2^N \cdot \sum L + 3^N)$. With $N=12$, $3^{12} \approx 5.3 \times 10^5$, which is well within the typical 1-second limit ($~10^8$ operations).
- **Space**: $O(2^N)$ to store the DP table and precomputed arrays.

## Implementation Details (C++)
- Use `long long` for cost accumulation to prevent overflow, although with strict constraints `int` might suffice, safe coding prefers `long long`.
- The median calculation uses a global sort of structure `{value, original_list_index}` to avoid sorting repeatedly for each mask.

```cpp
// Pseudocode for the core transition
for (int mask = 1; mask < (1 << n); ++mask) {
    for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
        int other = mask ^ sub;
        long long current_cost = dp[sub] + dp[other] + 
                                 mask_len[mask] + 
                                 abs(mask_median[sub] - mask_median[other]);
        dp[mask] = min(dp[mask], current_cost);
    }
}
```

### Technical Detail: Submask Enumeration Loop

The loop structure used to iterate over subsets is a standard bit manipulation technique:

```cpp
for (int s = (m - 1) & m; s > 0; s = (s - 1) & m) {
    int other = m ^ s;
    // ...
}
```

**Explanation:**
1.  **Initialization**: `s = (m - 1) & m`
    -   `m - 1` flips the lowest set bit of `m` to 0 and all lower bits to 1.
    -   `& m` ensures that we only keep bits that are actually set in the original mask `m`.
    -   This effectively effectively gives us the largest proper subset of `m`.

2.  **Update Step**: `s = (s - 1) & m`
    -   Using the same logic, this decrements `s` but then immediately removes any bits that aren't in `m`.
    -   This creates a sequence that visits every possible subset of `m` in descending order.

3.  **Why `s > 0`?**
    -   We usually handle the empty set case (0) separately or don't need it for partitioning problems (since we need non-empty splits).

4.  **Why `other = m ^ s`?**
    -   Since `s` is a subset of `m` (i.e., `s` has some bits of `m` set), the XOR operation `m ^ s` will flip those bits to 0 and leave the bits *not* in `s` (but in `m`) as 1.
    -   This perfectly calculates the complement set: `other = m \ s`.

**Efficiency**:
This technique is extremely efficient because it iterates **only** through valid submasks. It does not waste time checking numbers that aren't subsets of `m`. The total complexity of iterating submasks for all masks is $O(3^N)$, not $O(4^N)$ or $O(2^N \cdot 2^N)$.