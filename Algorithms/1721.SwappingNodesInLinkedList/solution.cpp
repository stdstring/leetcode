#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* swapNodes(ListNode* head, int k) const
    {
        std::vector<int> data;
        ListNode* source = head;
        while (source != nullptr)
        {
            data.push_back(source->val);
            source = source->next;
        }
        std::swap(data[static_cast<size_t>(k) - 1], data[data.size() - k]);
        ListNode* dest = new ListNode(data[0]);
        ListNode* current = dest;
        for (size_t index = 1; index < data.size(); ++index)
        {
            current->next = new ListNode(data[index]);
            current = current->next;
        }
        return dest;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace SwappingNodesInLinkedListTask
{

TEST(SwappingNodesInLinkedListTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({1, 4, 3, 2, 5}, solution.swapNodes(createLinkedList({1, 2, 3, 4, 5}, true).get(), 2));
    checkAndDeleteLinkedList({7, 9, 6, 6, 8, 7, 3, 0, 9, 5}, solution.swapNodes(createLinkedList({7, 9, 6, 6, 7, 8, 3, 0, 9, 5}, true).get(), 5));
    checkAndDeleteLinkedList({1}, solution.swapNodes(createLinkedList({1}, true).get(), 1));
    checkAndDeleteLinkedList({2, 1}, solution.swapNodes(createLinkedList({1, 2}, true).get(), 1));
    checkAndDeleteLinkedList({1, 2, 3}, solution.swapNodes(createLinkedList({1, 2, 3}, true).get(), 2));
}

}