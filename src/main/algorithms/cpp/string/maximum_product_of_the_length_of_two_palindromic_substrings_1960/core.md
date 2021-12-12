# [Finding all sub-palindromes](https://cp-algorithms.com/string/manacher.html)
* **must set odd or even length to position the center**<br>
## Trivial algorithm
```
vector<int> d1(n),  d2(n);
for (int i = 0; i < n; i++) {
    d1[i] = 1;
    while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) {
        d1[i]++;
    }

    d2[i] = 0;
    while (0 <= i - d2[i] - 1 && i + d2[i] < n && s[i - d2[i] - 1] == s[i + d2[i]]) {
        d2[i]++;
    }
}
```
## Manacher's algorithm
```
# odd len implementation
vector<int> d1(n);
for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 1 : min(d1[l + r - i] /*find the mirror position*/, r - i + 1);
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
        k++;
    }
    d1[i] = k--; // record the length of the current index
    if (i + k > r) {
        l = i - k; // record the leftmost position(inclusive), because k have minus one when recording
        r = i + k; // record the rightmost position(inclusive)
    }
}

# even len implementation
vector<int> d2(n);
for (int i = 0, l = 0, r = -1; i < n; i++) {
    // the mirror position is (l + r - i), however, when the length is even, the i idx is the later one,
    // and the position of (l + r - i) is the former one. so we need plus one to be (l + r - i + 1)
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1); 
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
        k++;
    }
    d2[i] = k--; // to record the half of the lenght
    if (i + k > r) {
        l = i - k - 1; // to record the leftmost(inclusive) position
        r = i + k ; // to record the rightmost(inclusive) position
    }
}
```
