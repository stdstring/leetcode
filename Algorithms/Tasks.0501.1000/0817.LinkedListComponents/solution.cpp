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
    int numComponents(ListNode* head, std::vector<int> const &nums) const
    {
        const std::unordered_set<int> numbers(nums.cbegin(), nums.cend());
        size_t componentsCount = 0;
        bool inComponent = false;
        while (head != nullptr)
        {
            if (numbers.count(head->val) == 1)
            {
                if (!inComponent)
                {
                    inComponent = true;
                    ++componentsCount;
                }
            }
            else
                inComponent = false;
            head = head->next;
        }
        return static_cast<int>(componentsCount);
    }
};

}

using CommonLib::createLinkedList;

namespace LinkedListComponentsTask
{

TEST(ReorderListTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.numComponents(createLinkedList({0, 1, 2, 3}, true).get(), {0, 1, 3}));
    ASSERT_EQ(2, solution.numComponents(createLinkedList({0, 1, 2, 3, 4}, true).get(), {0, 3, 1, 4}));
}

TEST(ReorderListTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.numComponents(createLinkedList({0, 1, 2}, true).get(), {0, 2}));
    ASSERT_EQ(1, solution.numComponents(createLinkedList({1, 2, 0, 4, 3}, true).get(), {3, 4, 0, 2, 1}));
}

}