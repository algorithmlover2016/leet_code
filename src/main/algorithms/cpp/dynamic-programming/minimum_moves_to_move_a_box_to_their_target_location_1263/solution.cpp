#include "../../head.h"


class Solution {
private:
    struct Data {
        int total;
        int moves;
        struct Box {
            int row;
            int col;
            Box(int _row = 0, int _col = 0) : row(_row), col(_col) {
            }
        };
        struct Box box;
        struct Person {
            int row;
            int col;
            Person(int _row = 0, int _col = 0) : row(_row), col(_col) {
            }
        };
        struct Person person;

        Data(int _total, int _moves, struct Box _box, struct Person _person) :
            total(_total), moves(_moves), box(_box), person(_person) {
        }
        Data(int _total, int _moves, int brow, int bcol, int prow, int pcol) :
            total(_total), moves(_moves), box(brow, bcol), person(prow, pcol) {
        }
    };
    class cmp {
    public:
        bool operator()(struct Data & lhs, struct Data & rhs) {
            // return lhs > rhs;
            return lhs.total > rhs.total;
        }
    };
public:
    int minPushBox(std::vector<std::vector<char>> & grid) {
        int rowSize = grid.size();
        if (0 == rowSize) {
            return -1;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return -1;
        }
        std::vector<int> target;
        std::vector<int> box;
        std::vector<int> start;
        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                switch (grid[row][col]) {
                    case 'T':
                        target = {row, col};break;
                    case 'B':
                        box = {row, col};break;
                    case 'S':
                        start = {row, col};break;
                    default:;break;
                }
            }
        }
        std::set<std::string> visited;
        std::priority_queue<struct Data, std::vector<struct Data>, cmp> minHeap;
        struct Data data(heuristic(target, box), 0, box[0], box[1], start[0], start[1]);
        minHeap.emplace(data);
        while (minHeap.size()) {
            struct Data const & cur = minHeap.top();
            int moves = cur.moves;
            std::vector<int> curBox{cur.box.row, cur.box.col};
            int curRow = cur.person.row;
            int curCol = cur.person.col;
            // std::cout << "heap: " << cur.total << "\t";
            minHeap.pop();
            if (curBox == target) {
                return moves;
            }
            std::string code = std::to_string(curBox[0]) + "@"
                + std::to_string(curBox[1]) + "@"
                + std::to_string(curRow) + "@"
                + std::to_string(curCol);
            if (visited.find(code) != visited.end()) {
                continue;
            }
            visited.emplace(code);
            // std::cout << "code: " << code << "\n";

            for (int index = 0; index < DIRECTION_SIZE; index++) {
                int newRow = curRow + direction[index];
                int newCol = curCol + direction[index + 1];
                if (onBound(grid, newRow, newCol)) {
                    continue;
                }
                // std::cout << "(newRow, newCol): " << newRow << "\t" << newCol << "\n";
                if (curBox[0] == newRow && curBox[1] == newCol) {
                    int newBRow = newRow + direction[index];
                    int newBCol = newCol + direction[index + 1];
                    if (onBound(grid, newBRow, newBCol)) {
                        continue;
                    } else {
                        // std::cout << "(newBRow, newBCol): " << newBRow << "\t" << newBCol << "\n";
                        struct Data data(heuristic(target, {newBRow, newBCol}) + moves + 1,
                                moves + 1, newBRow, newBCol, newRow, newCol);
                        minHeap.emplace(data);
                    }
                } else {
                        struct Data data(heuristic(target, curBox) + moves,
                                moves, curBox[0], curBox[1], newRow, newCol);
                        minHeap.emplace(data);
                }
            }
        }
        return -1;
    }
private:
    bool onBound(std::vector<std::vector<char>> const & grid, int row, int col) {
        if (row < 0 || row >= grid.size() ||
                col < 0 || col >= grid[row].size() ||
                '#' == grid[row][col]) {
            return true;
        }
        return false;
    }

    int heuristic(std::vector<int> const & target, std::vector<int> const & box) {
        assert(target.size() == box.size());
        int ans = 0;
        for (int index = 0; index < target.size(); index++) {
            ans += std::abs(target[index] - box[index]);
        }
        return ans;
    }

    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> direction;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::direction = {0, 1, 0, -1, 0};



class SolutionBetterRuntime {
private:
    struct Node {
        int bx;
        int by;
        int px;
        int py;
        int h;
        int g;

        int key() const {
            return ((by * m + bx) << 2) | ((bx - px) + 1) | ((by - py) + 1) >> 1;
        }

        int f() const { return g + h; }
        bool operator< (const Node& o) const {
            return f() > o.f();
        }
        static int m;
    };
public:
    int minPushBox(std::vector<std::vector<char>> const & grid) {
        const std::vector<int> dirs{0, -1, 0, 1, 0};
        const int n = grid.size();
        const int m = Node::m = grid[0].size();
        Node start;
        Node end;

        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                if (grid[y][x] == 'B') {
                    start.bx = x;
                    start.by = y;
                } else if (grid[y][x] == 'S') {
                    start.px = x;
                    start.py = y;
                } else if (grid[y][x] == 'T') {
                    end.bx = x;
                    end.by = y;
                }

        auto isValid = [&](int x, int y) {
            return !(x < 0 || x >= m || y < 0 || y >= n || grid[y][x] == '#');
        };

        auto hasPath = [&](const Node& cur, int tx, int ty) {
            if (!isValid(tx, ty)) return false;
            std::vector<int> seen(m*n);
            std::queue<int> q;
            q.push(cur.py * m + cur.px);
            seen[cur.py * m + cur.px] = 1;
            while (q.size()) {
                int x = q.front() % m;
                int y = q.front() / m;
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i];
                    int ny = y + dirs[i + 1];
                    if (!isValid(nx, ny)) continue;
                    if (nx == cur.bx && ny == cur.by) continue;
                    if (nx == tx && ny == ty) return true;
                    if (seen[ny * m  + nx]++) continue;
                    q.push(ny * m + nx);
                }
            }
            return false;
        };

        auto canPush = [&](const Node& cur, int dx, int dy, Node* nxt) {
            nxt->bx = cur.bx + dx;
            nxt->by = cur.by + dy;
            nxt->px = cur.bx;
            nxt->py = cur.by;
            nxt->g = cur.g + 1;
            nxt->h = std::abs(nxt->bx - end.bx) + std::abs(nxt->by - end.by);
            if (!isValid(nxt->bx, nxt->by)) return false;
            return hasPath(cur, cur.bx - dx, cur.by - dy);
        };

        std::vector<int> seen(m*n*4);
        std::priority_queue<Node> q;
        start.g = 0;
        start.h = std::abs(start.bx - end.bx) + std::abs(start.by - end.by);
        q.push(start);

        while (q.size()) {
            Node cur = q.top();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                Node nxt;
                if (!canPush(cur, dirs[i], dirs[i + 1], &nxt) || seen[nxt.key()]++) continue;
                if (nxt.bx == end.bx && nxt.by == end.by) return nxt.g;
                q.push(nxt);
            }
        }
        return -1;
    }
};
int Solution::Node::m;

class Solution {
public:
    int minPushBox(std::vector<std::vector<char>> const & grid) {
        // plagiarizing from https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/discuss/431431/Java-straightforward-BFS-solution
        int rowSize = grid.size();
        if (0 == rowSize) {
            return -1;
        }
        int colSize = grid[0].size();
        if (0 == colSize) {
            return -1;
        }
        int tRow = 0, tCol = 0;
        int bRow = 0, bCol = 0;
        int pRow = 0, pCol = 0;

        for (int row = 0; row < rowSize; row++) {
            for (int col = 0; col < colSize; col++) {
                switch(grid[row][col]) {
                    case 'T':
                        tRow = row;
                        tCol = col;
                        break;
                    case 'B':
                        bRow = row;
                        bCol = col;
                        break;
                    case 'S':
                        pRow = row;
                        pCol = col;
                        break;
                    default:;break;
                }
            }
        }
        int res = INT_MAX;
        std::unordered_map<int, int> dp;
        std::queue<int> todo;
        int code = encode(bRow, bCol, pRow, pCol);
        todo.emplace(code);
        dp[code] = 0;
        while (todo.size()) {
            int curBRow = 0, curBCol = 0, curPRow = 0, curPCol = 0;
            int cur = todo.front(); todo.pop();
            if (dp[cur] >= res) {
                continue;
            }

            decode(cur, curBRow, curBCol, curPRow, curPCol);
            // std::cout << "bRow, bCol: " << curBRow <<"\t" << curBCol
            //    <<"\tpRow, pCol: " << curPRow <<"\t" << curPCol << "\n";
            if (tRow == curBRow && tCol == curBCol) {
                res = std::min(res, dp[cur]);
                continue;
            }

            for (int index = 0; index < DIRECTION_SIZE; index++) {
                int newPRow = curPRow + direction[index];
                int newPCol = curPCol + direction[index + 1];
                if (onBound(grid, newPRow, newPCol)) {
                    continue;
                }
                // std::cout << "newPRow, newPCol: " << newPRow << "\t" << newPCol << "\n";
                if (newPRow == curBRow && newPCol == curBCol) {
                    int newBRow = curBRow + direction[index];
                    int newBCol = curBCol + direction[index + 1];
                    if (onBound(grid, newBRow, newBCol)) {
                        continue;
                    } else {
                        // std::cout << "newBRow, newBCol: " << newBRow << "\t" << newBCol << "\n";
                        int code = encode(newBRow, newBCol, newPRow, newPCol);
                        if (dp.find(code) == dp.end() || dp[code] > dp[cur] + 1) {
                            dp[code] = dp[cur] + 1;
                            todo.emplace(code);
                        }
                    }
                } else {
                    int code = encode(curBRow, curBCol, newPRow, newPCol);
                    if (dp.find(code) == dp.end() || dp[code] > dp[cur]) {
                        dp[code] = dp[cur];
                        todo.emplace(code);
                    }
                }
            }
        }
        return res == INT_MAX ? -1 : res;
    }

private:
    bool onBound(std::vector<std::vector<char>> const & grid, int row, int col) {
        if (row < 0 || row >= grid.size() ||
                col < 0 || col >= grid[row].size() ||
                '#' == grid[row][col]) {
            return true;
        }
        return false;
    }

    int encode(int bRow, int bCol, int pRow, int pCol) {
        int res = (bRow << 24) | (bCol << 16) | (pRow << 8) | (pCol);
        return res;
    }

    void decode(int res, int & bRow, int & bCol, int & pRow, int & pCol) {
        pCol = res & 0xFF;
        pRow = (res >> 8) & 0xFF;
        bCol = (res >> 16) & 0xFF;
        bRow = (res >> 24) & 0xFF;
    }

    static int const DIRECTION_ARRAY_SIZE = 5;
    static int const DIRECTION_SIZE = DIRECTION_ARRAY_SIZE - 1;
    static std::array<int, DIRECTION_ARRAY_SIZE> direction;
};
std::array<int, Solution::DIRECTION_ARRAY_SIZE> Solution::direction = {0, 1, 0, -1, 0};
