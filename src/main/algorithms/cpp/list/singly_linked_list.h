#ifndef LEET_CODE_ALGORITHMS_LIST_SINGLY_LINKED_LIST_H 
#define LEET_CODE_ALGORITHMS_LIST_SINGLY_LINKED_LIST_H
#include "../head.h"
/**
 * Definition for singly-linked list.
 */
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
#endif
