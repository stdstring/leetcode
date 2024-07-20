#include <unordered_set>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    [[nodiscard]] ListNode* modifiedList(std::vector<int> const &nums, ListNode* head) const
    {
        const std::unordered_set<int> numbers(nums.cbegin(), nums.cend());
        ListNode* resultHead = nullptr;
        ListNode* resultTail = nullptr;
        while (head != nullptr)
        {
            if (!numbers.contains(head->val))
            {
                if (resultHead == nullptr)
                    resultHead = resultTail = new ListNode(head->val);
                else
                {
                    resultTail->next = new ListNode(head->val);
                    resultTail = resultTail->next;
                }
            }
            head = head->next;
        }
        return resultHead;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace DeleteNodesFromLinkedListPresentInArrayTask
{

TEST(DeleteNodesFromLinkedListPresentInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    checkAndDeleteLinkedList({4, 5}, solution.modifiedList({1, 2, 3}, createLinkedList({1, 2, 3, 4, 5}, true).get()));
    checkAndDeleteLinkedList({2, 2, 2}, solution.modifiedList({1}, createLinkedList({1, 2, 1, 2, 1, 2}, true).get()));
    checkAndDeleteLinkedList({1, 2, 3, 4}, solution.modifiedList({5}, createLinkedList({1, 2, 3, 4}, true).get()));
}

}