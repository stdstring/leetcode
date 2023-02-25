#include <stack>
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
    std::vector<int> nextLargerNodes(ListNode* head) const
    {
        std::vector<int> result;
        while (head != nullptr)
        {
            result.push_back(head->val);
            head = head->next;
        }
        std::stack<int> nextGreaterNumberStack;
        for (size_t index = 0; index < result.size(); ++index)
        {
            int current = result[result.size() - 1 - index];
            while (!nextGreaterNumberStack.empty() && nextGreaterNumberStack.top() <= current)
                nextGreaterNumberStack.pop();
            result[result.size() - 1 - index] = nextGreaterNumberStack.empty() ? 0 : nextGreaterNumberStack.top();
            nextGreaterNumberStack.push(current);
        }
        return result;
    }
};

}

using CommonLib::createLinkedList;

namespace NextGreaterNodeInLinkedListTask
{

TEST(NextGreaterNodeInLinkedListTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({5, 5, 0}), solution.nextLargerNodes(createLinkedList({2, 1, 5}, true).get()));
    ASSERT_EQ(std::vector<int>({7, 0, 5, 5, 0}), solution.nextLargerNodes(createLinkedList({2, 7, 4, 3, 5}, true).get()));
    ASSERT_EQ(std::vector<int>({7, 9, 9, 9, 0, 5, 0, 0}), solution.nextLargerNodes(createLinkedList({1, 7, 5, 1, 9, 2, 5, 1}, true).get()));
}

}