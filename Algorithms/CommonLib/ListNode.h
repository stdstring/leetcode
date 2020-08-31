#pragma once

namespace CommonLib
{

struct ListNode
{
    int val;
    ListNode *next;

    ListNode();
    explicit ListNode(int x);
    ListNode(int x, ListNode *next);
};

}