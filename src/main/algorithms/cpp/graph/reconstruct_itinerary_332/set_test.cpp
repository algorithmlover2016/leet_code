// constructing sets
#include <iostream>
#include <string>
#include <set>
using namespace std;
bool fncomp (string const & lhs, string const & rhs) {
    int lhsSize = lhs.size(), rhsSize = rhs.size();
    int i = 0;
    for (;i < lhsSize && i < rhsSize; i++) {
        if (lhs[i] < rhs[i]) {
            return true;
        } else if (lhs[i] > rhs[i]) {
            return false;
        }
        
    }
    if (i <= rhsSize) {
        return true;
    } else {
        return false;
    }
    
    return true ;
}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  std::set<int> first;                           // empty set of ints

  int myints[]= {10,20,30,40,50};
  std::set<int> second (myints,myints+5);        // range

  std::set<int> third (second);                  // a copy of second

  std::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  std::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(string const & ,string const &) = fncomp;
  std::set<string, bool(*)(string const & ,string const &) > sixth (fn_pt);  // function pointer as Compare
  sixth.emplace("foo");
  sixth.emplace("bar");
   sixth.emplace("s");
  sixth.emplace("absfdss");
  for (auto & ele : sixth){
      std::cout << ele << "\t";
  }
  std::cout << "\n";
  std::set<string> seven(sixth.begin(), sixth.end());
  seven.emplace("isf");
  for (auto & ele : seven){
      std::cout << ele << "\t";
  }
  std::cout << std::endl;

  return 0;
}
