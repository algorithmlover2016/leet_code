#include <iostream>
#include <sstream>
#include <string>

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        unordered_map<int, unordered_map<int, int> > citiesPrices;
        for (int index = 0; index < flights.size(); index++) {
            vector<int> & flight = flights[index];
            if (flight.size() != 3) {
                continue;
            }
            citiesPrices[flight[0]][flight[1]] = flight[2];
        }
        std::priority_queue<std::vector<int>, std::vector<std::vector<int> >,
            std::greater<vector<int>> > breadStep;
        breadStep.push(vector<int>{0, src, K + 1});
        while(!breadStep.empty()) {
            const std::vector<int> & nums = breadStep.top();
            int price = nums[0];
            int city = nums[1];
            int step = nums[2];
            breadStep.pop();
            if (city == dst) {
                return price;
            }
            if (step > 0) {
                unordered_map<int, int> nextCity = citiesPrices[city];
                for (unordered_map<int, int>::iterator it = nextCity.begin(); it != nextCity.end(); it++) {
                    breadStep.push(vector<int> {price + it->second, it->first, step - 1});
                }
            }
        }
        return -1;
    }
};

// make a storage for each source with each k
class betterSolution {
public:
    int findCheapestPrice( int n, vector<vector<int>>& flights, int src, int dst, int K ) {
        vector<unordered_map<int, int>> graph( n );
        for( auto& f : flights ) graph[f[0]][f[1]] = f[2];

        unordered_map<int, int> cost;

        auto cmp = []( tuple<int,int,int>& l, tuple<int,int,int>& r ) { return get<0>(l) > get<0>(r); };
        // { cost, city, stops }
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, decltype(cmp)> q( cmp );

        q.push( make_tuple(0, src, 0) );

        while( !q.empty() ) {
            auto& t = q.top();
            int c = get<0>( t );
            int s = get<1>( t );
            int k = get<2>( t );
            q.pop();

            // cout << "Pop [" << c << ", " << s << ", " << k << "]" << endl;

            if( s == dst ) return c;

            if( k > K ) continue;

            auto i = cost.find( s + k * n );
            if( i != cost.end() && i->second < c ) continue;

            for( auto& edge : graph[s] ) {
                int nc = c + edge.second;
                int key = edge.first + (k + 1) * n;

                auto it = cost.find( key );
                if( it == cost.end() || nc < it->second ) {
                    // cout << "\t Push [" << nc << ", " << edge.first << ", " << k + 1 << "]" << endl;
                    if( it != cost.end() ) it->second = nc;
                    else cost[key] = nc;
                    q.push( make_tuple(nc, edge.first, k + 1) );
                }
            }
        }

        return -1;
    }
};
// g++ -std=c++11  -o main solution.cpp
