#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <forward_list>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

#include <algorithm>
#include <cassert>
#include <cctype>
#include <chrono>
#include <ctime>
#include <functional>
#include <iterator>
#include <limits>
#include <locale>
#include <random>
#include <regex>
#include <utility>

#define DEBUG
/**
 * Common interface of the generator protocol 
 * Don't modify this class
 **/
/**
 * Common interface of the generator protocol
 * Don't modify this class
 **/
class Generator {
public:
  /**
   * Return positive ascending integers infinitely when invoked consecutively.
   * You can assume no overflow issue.
   **/
  virtual int get() = 0;
};

///////////////////////////////////////////////////////////////////////
////  Please implement the following 3 subclasses of Generator  ///////
///////////////////////////////////////////////////////////////////////

class Intersection: public Generator {
  // You can add fields here
public:

	Intersection(Generator *a_, Generator *b_) : a(a_), b(b_) {
    // TODO
  }

  /**
   * Return common elements of a and b. Don't return the same value twice.
   **/
  int get() override {
    // TODO
    int aNum = a->get();
    int bNum = b->get();
    while (true) {
      while (aNum > bNum) {
        bNum = b->get();
      }
      while (bNum > aNum) {
        aNum = a->get();
      }
      if (aNum == bNum) {
        return aNum;
      }
    }
    return 0;
  }

private:
  Generator* a;
  Generator *b;
};

////////////////////////////////////////////////////

class Union: public Generator {
  // You can add fields here
public:

  Union(Generator *a_, Generator *b_) : a(a_), b(b_)  {
    // TODO
  }

  /**
   * Return elements either in a or b. Don't return the same value twice.
   **/
  int get() override {
    if (0 == aNum) {
      aNum = a->get();
    }
    if (0 == bNum) {
      bNum = b->get();
    }
    int ans = 0;
    if (aNum > bNum) {
        ans = bNum;
        bNum = b->get();
    } else if (aNum == bNum) {
        ans = bNum;
        aNum = a->get();
        bNum = b->get();
    } else {
        ans = aNum;
        aNum = a->get();
    }
    return ans;
  }

private:
  int aNum = 0;
  int bNum = 0;
  Generator* a;
  Generator *b;
};

////////////////////////////////////////////////////

class Subtraction: public Generator {
    // You can add fields here
    public:

        Subtraction(Generator *a, Generator *b) {
        }

        /**
         * Return elements in a but NOT in b.
         **/
        int get() override {
            // TODO
            return 0;
        }

};


/**
 * Arithmetic progression
 **/
class AP: public Generator {

    int start;
    int step;
    int next;

    public:

    AP(int start, int step): start(start), step(step) {
        next = start - step;
    }

    int get() override {
        next += step;
        return next;
    }
};

////////////////////////////////////////////////////

int main() {
    AP a(3, 3);
    AP b(2, 2);

    // Intersection compose(&a, &b);
    Union compose(&a, &b);
    // Subtraction compose(&a, &b);

    for (int i = 1; i <= 20; i++) {
        int x = compose.get();
        std::cout << i << ": " << x << std::endl;
    }

    return 0;
}
