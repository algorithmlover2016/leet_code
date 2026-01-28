#include "../../head.h"

class Solution {
public:
    std::string lexSmallestAfterDeletion(std::string s) {
        std::stack<char> stk;
        std::vector<int>cnt(26,0);
        for(auto &i : s) cnt[i-'a']++;
        
        int n = s.size();
        for(int i= 0; i < n;i++){
            if(stk.empty() || stk.top() <= s[i]) stk.push(s[i]);
            else{
                while(!stk.empty() && cnt[stk.top()-'a'] >= 2 && stk.top() > s[i]){
                    cnt[stk.top()-'a']--;
                    stk.pop();
                }
                stk.push(s[i]);
            }
        }

        std::string ans = "";
        while(!stk.empty()){
            ans += stk.top();  
            stk.pop();
        }

        std::reverse(ans.begin(),ans.end());

        n =ans.size();
        while( n >= 2 && cnt[ans[n-1]-'a'] > 1){
            cnt[ans[n-1]-'a']--;
            ans.pop_back();
            n = ans.size();
        }
        return ans;
    }
};
