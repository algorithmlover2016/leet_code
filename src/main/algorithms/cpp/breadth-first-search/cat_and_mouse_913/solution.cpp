#include "../../head.h"


class Solution {
public:
    int catMouseGame(std::vector<std::vector<int>> const & graph) {
        // plagiarizing idea from https://youtu.be/oGKnucI_ejw
        std::unordered_map<int, int> dpState;
        return dfs(graph, dpState, 1, 2, 1);
    }

private:
    int dfs(std::vector<std::vector<int>> const & graph,
            std::unordered_map<int, int> & dpState,
            int mouse, int cat, int step) {
        if (mouse == cat) {
            return CAT_WIN;
        }

        if (HOLE == mouse) {
            return MOUSE_WIN;
        }

        if (step > MAX_STEP) {
            return DRAW;
        }

        int coded = encode(mouse, cat, step);
        if (dpState.find(coded) != dpState.end()) {
            return dpState[coded];
        }

        if (step & MOUSE_STEP) {
            int canDraw = false;
            for (int const nei : graph[mouse]) {
                int ans = dfs(graph, dpState, nei, cat, step + 1);
                if (MOUSE_WIN == ans) {
                    return dpState[coded] = MOUSE_WIN;
                } else if (DRAW == ans) {
                    canDraw = true;
                }
            }
            if (canDraw) {
                return dpState[coded] = DRAW;
            } else {
                return dpState[coded] = CAT_WIN;
            }
        } else {
            int canDraw = false;
            for (int const nei : graph[cat]) {
                if (HOLE == nei) {
                    continue;
                }
                int ans = dfs(graph, dpState, mouse, nei, step + 1);
                if (CAT_WIN == ans) {
                    return dpState[coded] = CAT_WIN;
                } else if (DRAW == ans) {
                    canDraw = true;
                }
            }
            if (canDraw) {
                return dpState[coded] = DRAW;
            } else {
                return dpState[coded] = MOUSE_WIN;
            }
        }
    }
    void decode(int coded, int & mouse, int & cat, int & step) {
        mouse = (coded >> MOUSE_SHIFT_BITS) & 0xFF;
        cat = (coded >> CAT_SHIFT_BITS) & 0xFF;
        step = coded & 0xFF;
    }

    int encode(int mouse, int cat, int step) {
        return ((mouse & 0xFF) << MOUSE_SHIFT_BITS) |
            ((cat & 0xFF) << CAT_SHIFT_BITS) |
            (step & 0xFF);
    }
private:
    static int const MOUSE_SHIFT_BITS = 16;
    static int const CAT_SHIFT_BITS = 8;
    static int const MOUSE_WIN = 1;
    static int const CAT_WIN = 2;
    static int const DRAW = 0;
    static int const HOLE = 0;
    static int const MAX_STEP = 0xFF;
    static int const MOUSE_STEP = 0x01;
};

#define MAX_SIZE 50
class Solution {
public:
    struct Position {
        int mouse_pos;
        int cat_pos;
        int turn;
        int result;
        Position(int mouse_pos_, int cat_pos_, int turn_, int result_) :
            mouse_pos(mouse_pos_), cat_pos(cat_pos_), turn(turn_), result(result_) {}
    };

    int catMouseGame(std::vector<std::vector<int>> const & graph) {
        int n = graph.size();
        //int MAX_SIZE = 50;
        std::queue<Position> q;

        // mouse_pos, cat_pos, turn 0: mouse, turn 1: cat
        // State 0: draw, State 1: Mouse, State 2: Cat
        int states[MAX_SIZE][MAX_SIZE][2] = {0};
        int child_count[MAX_SIZE][MAX_SIZE][2] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                child_count[i][j][0] = graph[i].size();
                child_count[i][j][1] = graph[j].size();
                if (graph[j][0] == 0) {
                    child_count[i][j][1] --;
                }
                if (j == 0) {
                    child_count[i][j][1] = 0;
                }
            }
        }

        // Mouse wins when mouse is at hole
        for (int j = 0; j < n; j++) {
            states[0][j][0] = 1;
            states[0][j][1] = 1;
            Position p1(0, j, 0, 1);
            Position p2(0, j, 1, 1);
            q.push(p1);
            q.push(p2);
        }
        // Cat wins when cat and mouse overlap.
        for (int k = 1; k < n; k++) {
            states[k][k][0] = 2;
            states[k][k][1] = 2;
            Position p1(k, k, 0, 2);
            Position p2(k, k, 1, 2);
            q.push(p1);
            q.push(p2);
        }
        while (!q.empty()) {
            Position p = q.front();
            q.pop();
            if (p.turn == 1) {
                for (int i : graph[p.mouse_pos]) {
                    if (states[i][p.cat_pos][0] != 0) {
                        continue;
                    }
                    // Mouse is able to move to a mouse-win node
                    if (p.result == 1) {
                        states[i][p.cat_pos][0] = 1;
                        Position p1(i, p.cat_pos, 0, 1);
                        q.push(p1);
                    } else if (p.result == 2) {
                        // node i has a few node to go
                        child_count[i][p.cat_pos][0]--;
                        if (child_count[i][p.cat_pos][0] == 0) {
                            // No way to go when mouse at i and cat at cat_pos
                            // so the cat wins
                            states[i][p.cat_pos][0] = 2;
                            Position p1(i, p.cat_pos, 0, 2);
                            q.push(p1);
                        }
                    }
                }
            } else {
                for (int j : graph[p.cat_pos]) {
                    if (j == 0) {
                        continue;
                    }
                    if (states[p.mouse_pos][j][1] != 0) {
                        continue;
                    }
                    // Cat is able to move to a cat-win node
                    if (p.result == 2) {
                        states[p.mouse_pos][j][1] = 2;
                        Position p1(p.mouse_pos, j, 1, 2);
                        q.push(p1);
                    } else if (p.result == 1) {
                        child_count[p.mouse_pos][j][1]--;
                        if (child_count[p.mouse_pos][j][1] == 0) {
                            states[p.mouse_pos][j][1] = 1;
                            Position p1(p.mouse_pos, j, 1, 1);
                            q.push(p1);
                        }
                    }
                }
            }
        }
        return states[1][2][0];
    }

};
