# increasing seq:
* **from left to right**<br>
```
std::vector<int> incStack;
for (int idx = start; idx < end; idx++) {
    while (!incStack.empty() && (values[idx] > values[incStack.back()])) {
        // do yourself logic operation
        incStack.pop_back();
    }
    if (!incStack.empty()) {
        // do your operations
        ;
    }
    incStack.emplace_back(idx);
}
```
* **from right to left**<br>
```
std::vector<int> incStack;
for (int idx = end - 1; idx >= start; idx--) {
    while (!incStack.empty() && (values[idx] > values[incStack.back()])) {
        // do yourself logic operation
        incStack.pop_back();
    }
    if (!incStack.empty()) {
        // do your operations
        ;
    }
    incStack.emplace_back(idx);
}
```

# descreasing seq:
* **from left to right**<br>
```
std::vector<int> incStack;
for (int idx = start; idx < end; idx++) {
    while (!incStack.empty() && (values[incStack.back()] < values[idx])) {
        // do yourself logic operation
        incStack.pop_back();
    }
    if (!incStack.empty()) {
        // do your operations
        ;
    }
    incStack.emplace_back(idx);
}
```
* **from right to left**<br>
```
std::vector<int> incStack;
for (int idx = end - 1; idx >= start; idx--) {
    while (!incStack.empty() && (values[idx] < values[incStack.back()])) {
        // do yourself logic operation
        incStack.pop_back();
    }
    if (!incStack.empty()) {
        // do your operations
        ;
    }
    incStack.emplace_back(idx);
}
```
**Notice:**<br>
* **https://leetcode.com/problems/number-of-visible-people-in-a-queue/discuss/1359702/Monostack**<br>
* **https://leetcode.com/problems/number-of-visible-people-in-a-queue/discuss/1359707/JavaC%2B%2BPython-Stack-Solution-Next-Greater-Element**<br>