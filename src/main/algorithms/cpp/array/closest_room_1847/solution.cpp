#include "../../head.h"


#define AVOID_TLE_BY_USING_METHOD_OF_LOWER_BOUND
// #define DEBUG
class Solution {
public:
    std::vector<int> closestRoom(std::vector<std::vector<int>> rooms,
            std::vector<std::vector<int>> queries) {
        // plagiarizing from https://leetcode.com/problems/closest-room/discuss/1186023/C%2B%2BJava-Sort-Queries

        // sort the rooms in decreasing order with room's size
        auto cmp = [] (std::vector<int> const & left, std::vector<int> const & right) {
                assert(ROOM_SIZE <= left.size());
                assert(ROOM_SIZE <= right.size());
                return left[SIZE_IDX] > right[SIZE_IDX];
                };
        std::sort(std::begin(rooms), std::end(rooms), cmp);

        int const roomsSize = rooms.size();
        int const queriesSize = queries.size();

        for (int idx = 0; idx < queriesSize; idx++) {
            auto & query = queries[idx];
            query.emplace_back(idx);
        }
        std::sort(std::begin(queries), std::end(queries), cmp);

        std::set<int> ids;
        std::vector<int> ans(queriesSize, NOT_FOUND_FLAG);
        for (int idx = 0, roomIdx = 0; idx < queriesSize; idx++) {
            auto & query = queries[idx];
            #ifdef DEBUG
            std::cout << query[ROOMID_IDX] << ", " << query[SIZE_IDX] << ", " << query[QUERYID_IDX] << ";\t";
            #endif
            for (; roomIdx < roomsSize && rooms[roomIdx][SIZE_IDX] >= query[SIZE_IDX]; roomIdx++) {
                #ifdef DEBUG
                std::cout << " add: " << rooms[roomIdx][ROOMID_IDX] << ", ";
                #endif
                ids.insert(rooms[roomIdx][ROOMID_IDX]);
            }
            int queryIdx = query[QUERYID_IDX];
            int roomId = query[ROOMID_IDX];
            #ifdef AVOID_TLE_BY_USING_METHOD_OF_LOWER_BOUND
            auto it = ids.lower_bound(roomId);
            #else
            auto it = std::lower_bound(std::begin(ids), std::end(ids), roomId);
            #endif
            int left = (it == std::begin(ids) ? NOT_FOUND_FLAG : *(std::prev(it)));
            int right = (it == std::end(ids) ? NOT_FOUND_FLAG : *it);
            #ifdef DEBUG
            std::cout << "; queryIdx: " << queryIdx << ", roomId: " << roomId
                << ", left: " << left << ", right: " << right << "; ";
            #endif
            ans[queryIdx] = (NOT_FOUND_FLAG == std::min(left, right)) ? (std::max(left, right)) :
                (std::abs(roomId - left) <= std::abs(roomId - right) ? left : right);

            #ifdef DEBUG
            std::cout << "\n";
            #endif
        }
        return ans;
    }
private:
    static int const ROOM_SIZE = 2;
    static int const QUERY_SIZE = 3;
    static int const ROOMID_IDX = 0;
    static int const SIZE_IDX = 1;
    static int const QUERYID_IDX = 2;
    int const NOT_FOUND_FLAG = -1;
};
