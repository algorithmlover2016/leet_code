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


class Solution {
public:
    struct Position {
        int mousePos;
        int catPos;
        int curTurn;
        int ans;
        Position(int mouse, int cat, int next, int ans_) :
            mousePos(mouse), catPos(cat), curTurn(next), ans(ans_) {
            }
    };

    int catMouseGame(std::vector<std::vector<int>> const & graph) {
        int const nodesLen = graph.size();
        int state[MAX_SIZE][MAX_SIZE][TURN_SIZE] = {DRAW};
        int childCnt[MAX_SIZE][MAX_SIZE][TURN_SIZE] = {0};
        for (int mouse = 0; mouse < nodesLen; mouse++) {
            for (int cat = 0; cat < nodesLen; cat++) {
                childCnt[mouse][cat][MOUSE_IDX] = graph[mouse].size();
                childCnt[mouse][cat][CAT_IDX] = graph[cat].size();
                if (HOLE == graph[cat][JUST_ZERO]) {
                    // cat can't jump into HOLE
                    childCnt[mouse][cat][CAT_IDX]--;
                }
                // cat can't jump from HOLE
            }
            childCnt[mouse][HOLE][CAT_IDX] = 0;
        }

        std::queue<Position> que;

        // init mouse will always win
        for (int cat = 1; cat < nodesLen; cat++) {
            Position mP1(HOLE, cat, MOUSE_IDX, MOUSE_WIN);
            state[HOLE][cat][MOUSE_IDX] = MOUSE_WIN;
            que.push(mP1);

            Position mP2(HOLE, cat, CAT_IDX, MOUSE_WIN);
            state[HOLE][cat][CAT_IDX] = MOUSE_WIN;
            que.push(mP2);
        }

        // init cat will always win
        for (int cat = 1; cat < nodesLen; cat++) {
            Position cP1(cat, cat, MOUSE_IDX, CAT_WIN);
            state[cat][cat][MOUSE_IDX] = CAT_WIN;
            que.push(cP1);

            Position cP2(cat, cat, CAT_IDX, CAT_WIN);
            state[cat][cat][CAT_IDX] = CAT_WIN;
            que.push(cP2);
        }

        while (!que.empty()) {
            Position p = que.front(); que.pop();
            if (CAT_IDX == p.curTurn) {
                // now it's cat's turn, and
                // its previous turn is mouseTurn and the previous status can be
                for (int const nei : graph[p.mousePos]) {
                    if (DRAW != state[nei][p.catPos][MOUSE_IDX]) {
                        // the state already update
                        continue;
                    }

                    if (MOUSE_WIN == p.ans) {
                        // mouse can jump from previous state to cur staus with won
                        state[nei][p.catPos][MOUSE_IDX] = MOUSE_WIN;
                        Position mP(nei, p.catPos, MOUSE_IDX, MOUSE_WIN);
                        que.push(mP);
                    } else if (CAT_WIN == p.ans) {
                        // mouse can't win when taking this step, just record a fail jump
                        --childCnt[nei][p.catPos][MOUSE_IDX];
                        if (JUST_ZERO == childCnt[nei][p.catPos][MOUSE_IDX]) {
                            // no matter how to jump, it will make cat win
                            state[nei][p.catPos][MOUSE_IDX] = CAT_WIN;
                            Position cP(nei, p.catPos, MOUSE_IDX, CAT_WIN);
                            que.push(cP);
                        }
                    }
                }
            } else {
                for (int const nei : graph[p.catPos]) {
                    if (HOLE == nei) {
                        // cat can't jump from HOLE
                        continue;
                    }
                    if (DRAW != state[p.mousePos][nei][CAT_IDX]) {
                        continue;
                    }

                    if (CAT_WIN == p.ans) {
                        state[p.mousePos][nei][CAT_IDX] = CAT_WIN;
                        Position cP(p.mousePos, nei, CAT_IDX, CAT_WIN);
                        que.push(cP);
                    } else if (MOUSE_WIN == p.ans) {
                        --childCnt[p.mousePos][nei][CAT_IDX];
                        if (JUST_ZERO == childCnt[p.mousePos][nei][CAT_IDX]) {
                            state[p.mousePos][nei][CAT_IDX] = MOUSE_WIN;
                            Position mP(p.mousePos, nei, CAT_IDX, MOUSE_WIN);
                            que.push(mP);
                        }
                    }
                }
            }
        }
        return state[1][2][0];
    }

private:
    static int const MAX_SIZE = 50;

    static int const MOUSE_WIN = 1;
    static int const CAT_WIN = 2;
    static int const DRAW = 0;

    static int const TURN_SIZE = 2;
    static int const MOUSE_IDX = 0;
    static int const CAT_IDX = 1;

    static int const HOLE = 0;

    static int const JUST_ZERO = 0;
};
