#include "../../head.h"



class MovieRentingSystemVec {
    // plagiarizing from https://leetcode.com/problems/design-movie-rental-system/discuss/1298735/C%2B%2B-Vector%2BOrdered-Sets
public:
    MovieRentingSystemVec(int n, std::vector<std::vector<int>>& entries) {
        for (auto & entry : entries) {
            if (entry.size() < ENTRY_LEN) {
                continue;
            }
            int s = entry[SHOP_INDEX];
            int m = entry[MOVIE_INDEX];
            int p = entry[PRICE_INDEX];
            available[m].insert(std::make_pair(p, s));
            getPrice[m].insert(std::make_pair(s, p));
        }
    }

    std::vector<int> search(int movie) {
        std::vector<int> ans;
        for (auto & ele : available[movie]) {
            ans.emplace_back(ele.second);
            if (ans.size() >= MAX_RETURN_LEN) {
                break;
            }
        }
        return ans;
    }

    void rent(int shop, int movie) {
        auto it = getPrice[movie].lower_bound(std::make_pair(shop, INT_MIN));
        if (it == getPrice[movie].end()) {
            // there is no movie in any shop
            return;
        }
        int p = (*it).second;
        int s = (*it).first;
        if (s != shop) {
            // there is no movie in target shop
            return;
        }
        int cnt = available[movie].erase(std::make_pair(p, shop));
        if (cnt == 0) {
            // The movie in this shop has been rented.
            return;
        }
        rented.insert(std::make_pair(p, std::make_pair(shop, movie)));
    }

    void drop(int shop, int movie) {
        auto it = getPrice[movie].lower_bound(std::make_pair(shop, INT_MIN));
        if (it == getPrice[movie].end() || (shop != (*it).first)) {
            // There is no movie in not less than target shop
            return;
        }
        int p = (*it).second;
        int cnt = rented.erase(std::make_pair(p, std::make_pair(shop, movie)));
        if (cnt == 0) {
            // there is no movie in shop has been rented
            return;
        }
        available[movie].insert(std::make_pair(p, shop));
    }

    std::vector<std::vector<int>> report() {
        std::vector<std::vector<int>> ans;
        for (auto & ele: rented) {
            ans.push_back({ele.second.first, ele.second.second});
            if (ans.size() >= MAX_RETURN_LEN) {
                break;
            }
        }
        return ans;
    }
private:
    // storage the unrented movies in movie price and shop.
    std::vector<std::set<std::pair<int, int>>> available = std::vector<std::set<std::pair<int, int>>>(MAX_MOVIE_NUM);
    //
    std::vector<std::set<std::pair<int, int>>> getPrice = std::vector<std::set<std::pair<int, int>>>(MAX_MOVIE_NUM);
    std::set<std::pair<int, std::pair<int, int>>> rented;
private:
    static int const MAX_MOVIE_NUM = 1e4 + 1;
    static int const ENTRY_LEN = 3;
    static int const SHOP_INDEX = 0;
    static int const MOVIE_INDEX = 1;
    static int const PRICE_INDEX = 2;
    static int const MAX_RETURN_LEN = 5;
};
static bool _foo = std::ios::sync_with_stdio(false);
static std::ostream* _bar = std::cin.tie(NULL);

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */

class MovieRentingSystem {
    // plagiarizing from https://leetcode.com/problems/design-movie-rental-system/discuss/1298452/Ordered-Sets
public:
    MovieRentingSystem(int n, std::vector<std::vector<int>>& entries) {
        for (auto & entry : entries) {
            if (entry.size() < ENTRY_LEN) {
                continue;
            }
            int s = entry[SHOP_INDEX];
            int m = entry[MOVIE_INDEX];
            int p = entry[PRICE_INDEX];
            available[m].insert({p, s});
            getPrice[m][s] = p;
        }
    }

    std::vector<int> search(int movie) {
        std::vector<int> ans;
        for (auto & ele : available[movie]) {
            ans.emplace_back(ele.second);
            if (ans.size() == MAX_RETURN_LEN) {
                break;
            }
        }
        return ans;
    }

    void rent(int shop, int movie) {
        if (getPrice.find(movie) == getPrice.end() || getPrice[movie].find(shop) == getPrice[movie].end()) {
            return;
        }
        int p = getPrice[movie][shop];
        int cnt = available[movie].erase(std::make_pair(p, shop));
        if (cnt == 0) {
            // The movie in this shop has been rented.
            return;
        }
        rented.insert(std::make_pair(p, std::make_pair(shop, movie)));
    }

    void drop(int shop, int movie) {
        if (getPrice.find(movie) == getPrice.end() || getPrice[movie].find(shop) == getPrice[movie].end()) {
            return;
        }
        int p = getPrice[movie][shop];
        int cnt = rented.erase(std::make_pair(p, std::make_pair(shop, movie)));
        if (cnt == 0) {
            // there is no movie in shop has been rented
            return;
        }
        available[movie].insert(std::make_pair(p, shop));
    }

    std::vector<std::vector<int>> report() {
        std::vector<std::vector<int>> ans;
        for (auto & ele: rented) {
            ans.push_back({ele.second.first, ele.second.second});
            if (ans.size() >= MAX_RETURN_LEN) {
                break;
            }
        }
        return ans;
    }
private:
    // storage the unrented movies in movie price and shop.
    std::unordered_map<int, std::set<std::pair<int, int>>> available;
    //
    std::unordered_map<int, std::unordered_map<int, int>> getPrice;
    std::set<std::pair<int, std::pair<int, int>>> rented;
private:
    static int const MAX_MOVIE_NUM = 1e4 + 1;
    static int const ENTRY_LEN = 3;
    static int const SHOP_INDEX = 0;
    static int const MOVIE_INDEX = 1;
    static int const PRICE_INDEX = 2;
    static int const MAX_RETURN_LEN = 5;
};