#include "../../head.h"


// #define DEBUG
auto ioSys = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
class MKAverageTLE {
public:
    // plagiarizing from https://youtu.be/z32DPe1tuXM
    MKAverage(int m_, int k_) : m(m_), k(k_) {
    }

    void addElement(int num) {
        // add the item into deque and compute the sum of the sliding window
        totalSum += num;
        slidingNums.emplace_back(num);
        // adjust the ksmallest sum
        // find the first element that not less than num and num should insert at this pos
        // either lower_bound or upper_bound is ok
        // auto curIt = sortedNums.upper_bound(num);
        auto curIt = sortedNums.lower_bound(num);
        int leftDis = std::distance(sortedNums.begin(), curIt);
        int sortNumsSize = sortedNums.size();
        #ifdef DEBUG
        std::cout << "\n from DEGIN: " << slidingNums.size() << ", " << leftDis << ", " <<  num << ", ";
        #endif

        if (leftDis < k) {
            // it means that the smallest k elements should be changed
            kSmallSum += num;
            #ifdef DEBUG
            std::cout << " small add: " << num << ", ";
            #endif
            if (sortNumsSize >= k) {
                auto beginIt = sortedNums.begin();
                std::advance(beginIt, k - 1);
                kSmallSum -= *(beginIt);
                #ifdef DEBUG
                std::cout << " not the s k: " << *beginIt << ", " << kSmallSum << ", ";
                #endif
            }
        }

        // adjust the kbiggest sum
        if (leftDis > sortNumsSize - k) {
            // it means that the biggest k elements should be changed
            #ifdef DEBUG
            std::cout << " big add: " << num << ", ";
            #endif
            kBigSum += num;
            if (sortNumsSize >= k) {
                // sortedNums.end() - 1 - (k - 1) means the kth smallest element from the end
                auto endIt = sortedNums.end();
                endIt = std::prev(endIt, k);
                kBigSum -= *(endIt);
                #ifdef DEBUG
                std::cout << " not the b k: " << *endIt << ", " << kBigSum << ", ";
                #endif
            }
        }
        #ifdef DEBUG
        std::cout << " s sum: " << kSmallSum << ", b Sum: " << kBigSum << ";\t";
        #endif
        sortedNums.insert(curIt, num); // similar to sortedNums.insert(num);

        if (slidingNums.size() > m) {
            // if the size of sliding window is greater than m (window size), we need remove first element
            // we need remove the first element in the sliding window
            int frontEle = slidingNums.front();
            #ifdef DEBUG
            std::cout << "need pop: " << slidingNums.size() << " pop " << frontEle << ", ";
            #endif
            slidingNums.pop_front();
            totalSum -= frontEle;

            auto needDelIt = sortedNums.find(frontEle);
            // we should first compute the distance and then we can erase the target iterator, otherwise, we use pointer who has been deleted
            int leftDis = std::distance(sortedNums.begin(), needDelIt);
            sortedNums.erase(needDelIt);
            #ifdef DEBUG
            std::cout << "need remove: " << leftDis << ", ";
            #endif

            if (leftDis < k) {
                kSmallSum -= frontEle;
                auto beginIt = sortedNums.begin();
                std::advance(beginIt, k - 1);
                kSmallSum += *(beginIt);
            }

            if (/*no need to judege sortedNums.size() >= k because m > 2 * k and slidingNums.size() == sortedNums.size()*/
                    leftDis > sortedNums.size() - k) {
                kBigSum -= frontEle;
                auto endIt = sortedNums.end();
                endIt = std::prev(endIt, k);
                kBigSum += *(endIt);
            }
        }
    }

    int calculateMKAverage() {
        if (slidingNums.size() < m) {
            #ifdef DEBUG
            std::cout << -1 << "\n";
            #endif
            return -1;
        }
        int ans = (totalSum - kSmallSum - kBigSum) / (m - 2 * k);
        #ifdef DEBUG
        std::cout << ans << "\n";
        #endif
        return ans;
    }
    private:
    int m;
    int k;
    long totalSum = 0;
    long kSmallSum = 0;
    long kBigSum = 0;
    std::deque<int> slidingNums;
    std::multiset<int> sortedNums;
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */


// #define DEBUG
class MKAverage {
public:
    // plagiarizing from https://leetcode.com/problems/finding-mk-average/discuss/1152724/C%2B%2B-Balance-3-Multisets
    // and https://leetcode.com/problems/finding-mk-average/discuss/1152418/C%2B%2B-3-multisets

    MKAverage(int m_, int k_) : m(m_), k(k_) {
        midSize = m - 2 * k;
        assert(midSize >= 0);
        std::vector<int>(m).swap(slidingNums);
    }

    void addElement(int num) {
        int mod = pos % m;
        if (pos >= m) {
            remove(slidingNums[mod]);
        }
        add(num);
        slidingNums[mod] = num;
        pos++;
    }

    int calculateMKAverage() {
        if (bigRight.size() < k) {
            return -1;
        }
        int ans = sum / midSize;
        #ifdef DEBUG
        std::cout << ans << "\n";
        #endif
        return ans;
    }
private:
    void add(int num) {
        leftSmall.insert(num);
        if (leftSmall.size() > k) {
            // if we do like this
            // auto needDelIt = leftSmall.rbegin();
            /* error: note: candidate function not viable: no known conversion from 'std::reverse_iterator<std::_Rb_tree_const_iterator<int>>' to 'std::multiset<int, std::less<int>, std::allocator<int>>::const_iterator' (aka '_Rb_tree_const_iterator<int>') for 1st argument
      erase(const_iterator __position)
            */
            auto needDelIt = std::prev(std::end(leftSmall));
            sum += *needDelIt;
            midNums.insert(*needDelIt);
            leftSmall.erase(needDelIt);
        }

        if (midNums.size() > midSize) {
            auto needDelIt = std::prev(std::end(midNums));
            sum -= *needDelIt;
            bigRight.insert(*needDelIt);
            midNums.erase(needDelIt);
        }
    }
    void remove(int target) {
        // the k smallest
        if (target <= *std::rbegin(leftSmall)) {
            leftSmall.erase(leftSmall.find(target));
        } else if (target <= *std::rbegin(midNums)) {
            sum -= target;
            midNums.erase(midNums.find(target));
        } else {
            bigRight.erase(bigRight.find(target));
        }

        if (leftSmall.size() < k) {
            int addEle = *std::begin(midNums);
            leftSmall.emplace(addEle);
            sum -= addEle;
            midNums.erase(std::begin(midNums));
        }

        if (midNums.size() < midSize) {
            int addEle = *bigRight.begin();
            midNums.insert(addEle);
            sum += addEle;
            bigRight.erase(bigRight.begin());
        }

    }

private:
    int m;
    int k;
    int midSize = 0;
    long sum = 0;
    int pos = 0;
    std::vector<int> slidingNums;
    std::multiset<int> leftSmall;
    std::multiset<int> midNums;
    std::multiset<int> bigRight;
};

// #define DEBUG
class MKAverage {
    static const int N = 100001;
    int m, k;
    std::deque<int> q;
    long fw0[N] = {}, fw1[N] = {};
public:
    void add(long i, long v) {
        #ifdef DEBUG
        std::cout << __func__ <<" add : " << v << "\n";
        #endif
        long u = v > 0 ? 1 : -1; // to judge we do a plus or minus operation
        for (; i < N; i |= i+1) {
            fw0[i] += u; // the cnt of the numbers add u, 线段树结构，存储某一特定区间中元素个数
            fw1[i] += v; // the sum of the numbers for a special interval 线段树结构
            #ifdef DEBUG
            std::cout << "index: " << i << ", cnt: " << fw0[i] << ", sum: " << fw1[i] << "; ";
            #endif
        }
    }

    std::tuple<long, long, long> kth(int k) {
        #ifdef DEBUG
        std::cout << __func__ << "\n";
        #endif
        long ans = 0, c = 0, s = 0;
        #ifdef DEBUG
        // get the left most bit set number for the maximum number;
        // which means get the mostest significant bit(1) for N - 1;
        std::cout << "bits: " << __builtin_clz(N - 1) << " bitShift: " << (1 << (31 - __builtin_clz(N - 1))) << "\n";
        #endif
        for (long i = 1 << (31 - __builtin_clz(N - 1)); i; i >>= 1) {
            #ifdef DEBUG
            std::cout << i << ", ";
            #endif
            if (ans + i < N && c + fw0[ans + i - 1] <= k) {
                // we count the sum at 1, 11, 111, 1111, ..., 111...11, so we need minus 1
                // ans is the next element that we need visit
                ans += i, c += fw0[ans - 1], s += fw1[ans - 1];
                #ifdef DEBUG
                std::cout << "ans: " << ans << ", c: " << c << ", s: " << s << "; ";
                #endif
            }
        }
        // c <= k must be true. and if c != k, it means that there are too many ans that make c + number of (ans) > k and c < k
        return {ans, c, s};
    }

    long sum(long a[], long i) {
        long s = 0;
        for (; i; i &= i-1) {
            s += a[i-1];
        }
        return s;
    }
    MKAverage(int m, int k) : m(m), k(k) {
        // same to https://leetcode.com/problems/finding-mk-average/discuss/1173779/c%2B%2B-segment-tree-get-the-solution-from-the-accepted-answer
        #ifdef DEBUG
        std::bitset<32> nBin(N);
        std::cout << N << ", hex: " << std::hex << N << std::dec << ", bin: " << nBin << "\n";
        #endif

    }

    void addElement(int num) {
        if (q.size() == m) {
            // we have storage m elements, to add a new element, we must remove the front element
            // to keep the sliding window
            int v = q.front();
            q.pop_front();
            // the base data structure also need remove the most front element
            add(v, -v);
        }
        // add the new element to queue to record the input order
        q.push_back(num);
        // add the new element into storage
        add(num, num);
    }

    int calculateMKAverage() {
        if (q.size() < m) {
            return -1;
        }
        auto [l, c0, s0] = kth(k);
        auto [r, c1, s1] = kth(m-k);
        // c0 < k and we can't add all the l, because the appearence times of l plusing c0 is larger than k
        // we just need k - c0 which is less than cnt[l];
        s0 += (k - c0) * l;

        // same to k - c0;
        s1 += (m - k - c1) * r;

        return (s1 - s0) / (m - 2 * k);
    }
};
