#include "ListNode.h"

CommonLib::ListNode::ListNode() : val(0), next(nullptr)
{
}

CommonLib::ListNode::ListNode(int x) : val(x), next(nullptr)
{
}

CommonLib::ListNode::ListNode(int x, ListNode* next) : val(x), next(next)
{
}