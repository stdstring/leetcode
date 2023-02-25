#include <vector>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* removeNodes(ListNode* head) const
    {
        std::vector<int> resultValues;
        while (head != nullptr)
        {
            while (!resultValues.empty() && resultValues.back() < head->val)
                resultValues.pop_back();
            resultValues.emplace_back(head->val);
            head = head->next;
        }
        ListNode* result = nullptr;
        for (auto rIterator = resultValues.crbegin(); rIterator != resultValues.crend(); ++rIterator)
            result = new ListNode(*rIterator, result);
        return result;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace RemoveNodesFromLinkedListTask
{

TEST(RemoveNodesFromLinkedListTaskTests, Examples)
{
    constexpr Solution solution;
    checkAndDeleteLinkedList({13, 8}, solution.removeNodes(createLinkedList({5, 2, 13, 3, 8}, true).get()));
    checkAndDeleteLinkedList({1, 1, 1, 1}, solution.removeNodes(createLinkedList({1, 1, 1, 1}, true).get()));
}

}