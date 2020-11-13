#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <unordered_map>
#include <map>

// plagiarizing from http://coliru.stacked-crooked.com/a/dede823b40af4662
namespace N {

    typedef std::tuple<int, char, char> key_t;

    struct key_hash : public std::unary_function<key_t, std::size_t> {
        std::size_t operator()(const key_t& k) const {
            return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
        }
    };

    struct key_equal : public std::binary_function<key_t, key_t, bool> {
        bool operator()(const key_t& v0, const key_t& v1) const {
            return (std::get<0>(v0) == std::get<0>(v1) &&
                    std::get<1>(v0) == std::get<1>(v1) &&
                    std::get<2>(v0) == std::get<2>(v1));
        }
    };

    struct data {
        std::string x;
    };

    typedef std::unordered_map<const key_t,data,key_hash,key_equal> map_t;

    typedef std::tuple<int, int> tuple_key_t;
    struct key_tuple_hash : public std::unary_function<tuple_key_t, std::size_t> {
        std::size_t operator()(const tuple_key_t& k) const {
            return (std::get<0>(k) << 10) | std::get<1>(k);
        }
    };

    struct key_tuple_equal : public std::binary_function<tuple_key_t, key_t, bool> {
        bool operator()(const tuple_key_t& v0, const tuple_key_t& v1) const {
            return (std::get<0>(v0) == std::get<0>(v1) &&
                    std::get<1>(v0) == std::get<1>(v1));
        }
    };

}

int main() {
    using namespace N;

    map_t m;
    data d;
    d.x = "test data";
    m[std::make_tuple(1, 'a', 'b')] = d;
    auto itr = m.find(std::make_tuple(1, 'a', 'b'));
    if (m.end() != itr) {
        std::cout << "x: " << itr->second.x;
    }
    std::cout << "\n";

    typedef std::unordered_map<tuple_key_t , std::string, key_tuple_hash, key_tuple_equal> map_tuple;
    map_tuple mt;
    mt[std::make_tuple(1, 20)] = "test_tuple";
    auto mt_itr = mt.find(std::make_tuple(1, 20));
    if (mt_itr != mt.end()) {
        std::cout << "tuple: " << mt_itr->second;
    }

    std::cout << "\n";
    std::map<std::tuple<int, int>, std::string> tuple_map; // not unordered_map
    tuple_map[std::make_pair<int, int>(1, 30)] = "map only need less operator, tuple have this relationship operator";

    auto tm_itr = tuple_map.find(std::make_tuple(1, 30));
    if (tm_itr != tuple_map.end()) {
        std::cout << "map_tuple: " << tm_itr->second;
    }
    std::cout << "\n";

    return 0;
}
