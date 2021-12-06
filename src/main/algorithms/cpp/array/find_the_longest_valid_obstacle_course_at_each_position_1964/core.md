# longest increasing sequence(LIS)
* **strictly increasing**<br>
    ***`std::lower_bound`***<br>
* **non-decreaing**<br>
    ***`std::upper_bound`***<br>
## demo code
```
std::vector<int> ins;
for (int idx = 0; idx < nums.size(); idx++) {
    // if we need strictly increasing sequence, use std::lower_bound
    // if we need non-decreasing sequence, use std::upper_bound instead
    auto & it = std::lower_bound(std::begin(ins), std::end(ins), nums[idx]);
    if (it == ins.end()) {
        // nums[idx] is the current maximum element in ins
        ins.emplace_back(nums[idx]);
        it = std::prev(std::end(ins.end()));
    } else {
        // there is at least one element in ins not less than nums[idx]
        *it = nums[idx];
    }
}
```

# Fenwick Tree
* **get the value by `idx` to avoid too many search by `idx -= (idx & (-idx))`, however, `idx` must be geater than zero**<br>
```
int get(int idx) {
    int ans = 0;
    for (; idx > 0; idx -= idx & (-idx)) {
        // user-defined logic for the problem
        ans = std::max(ans, bits[idx]);
    }
    return ans;
}
```
* **update the value by update from `idx` to the end by `idx += (idx & (-idx))`**<br>
```
void update(int idx, int val) {
    for (; idx < bits.size(); idx += idx & (-idx)) {
        // user-defined logic for the problem
        bits[idx] = std::max(bits[idx], val);
    }
}
```
* **the reason in this problem why use max function is because we need consider the order of elements appearing. And all the former elements can be seen by the later**<br>