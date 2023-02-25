#include <vector>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

namespace
{

using CommonLib::ListNode;

class Solution
{
public:
    ListNode* rotateRight(ListNode* head, int k) const
    {
        if (head == nullptr)
            return head;
        std::vector<ListNode*> nodes;
        while (head != nullptr)
        {
            nodes.push_back(head);
            head = head->next;
        }
        const size_t shift = static_cast<size_t>(k) % nodes.size();
        if (shift == 0)
            return nodes[0];
        head = nodes[nodes.size() - shift];
        ListNode* current = head;
        for (size_t index = 1; index < nodes.size(); ++index)
        {
            current->next = nodes[(nodes.size() - shift + index) % nodes.size()];
            current = current->next;
        }
        current->next = nullptr;
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace RotateListTask
{

TEST(RotateListTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({4, 5, 1, 2, 3}, solution.rotateRight(createLinkedList({1, 2, 3, 4, 5}, false).get(), 2));
    checkAndDeleteLinkedList({2, 0, 1}, solution.rotateRight(createLinkedList({0, 1, 2}, false).get(), 4));
}

TEST(RotateListTaskTests, FromWrongAnswers)
{
    const Solution solution;
    checkAndDeleteLinkedList({}, solution.rotateRight(createLinkedList({}, false).get(), 0));
}

}