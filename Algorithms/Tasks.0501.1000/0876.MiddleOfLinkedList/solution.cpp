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
    ListNode* middleNode(ListNode* head) const
    {
        ListNode* firstHead = head;
        ListNode* secondHead = head;
        while (secondHead != nullptr && secondHead->next != nullptr)
        {
            firstHead = firstHead->next;
            secondHead = secondHead->next->next;
        }
        return firstHead;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::convertLinkedListToVector;

namespace MiddleOfLinkedListTask
{

TEST(MiddleOfLinkedListTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 4, 5}), convertLinkedListToVector(solution.middleNode(createLinkedList({1, 2, 3, 4, 5}, true).get())));
    ASSERT_EQ(std::vector<int>({4, 5, 6}), convertLinkedListToVector(solution.middleNode(createLinkedList({1, 2, 3, 4, 5, 6}, true).get())));
}

}