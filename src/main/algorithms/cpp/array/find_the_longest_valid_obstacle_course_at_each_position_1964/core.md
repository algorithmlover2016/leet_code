# longest increasing series(LIS)
* **strictly increasing**<br>
    ***`std::lower_bound`***<br>
* ****<br>
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