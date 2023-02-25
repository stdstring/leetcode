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
    std::vector<int> nodesBetweenCriticalPoints(ListNode* head) const
    {
        constexpr size_t npos = -1;
        size_t firstCriticalIndex = npos;
        size_t lastCriticalIndex = npos;
        int maxDistance = -1;
        int minDistance = -1;
        size_t currentIndex = 1;
        int prevValue = head->val;
        head = head->next;
        while (head->next != nullptr)
        {
            if (((prevValue < head->val) && (head->val > head->next->val)) ||
                ((prevValue > head->val) && (head->val < head->next->val)))
            {
                if (firstCriticalIndex == npos)
                    firstCriticalIndex = lastCriticalIndex = currentIndex;
                else
                {
                    maxDistance = static_cast<int>(currentIndex - firstCriticalIndex);
                    const int lastDistance = static_cast<int>(currentIndex - lastCriticalIndex);
                    minDistance = minDistance == -1 ? lastDistance : std::min(minDistance, lastDistance);
                    lastCriticalIndex = currentIndex;
                }
            }
            prevValue = head->val;
            head = head->next;
            ++currentIndex;
        }
        return {minDistance, maxDistance};
    }
};

}

using CommonLib::createLinkedList;

namespace FindMinMaxNumberOfNodesBetweenCriticalPointsTask
{

TEST(FindMinMaxNumberOfNodesBetweenCriticalPointsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.nodesBetweenCriticalPoints(createLinkedList({3, 1}, true).get()));
    ASSERT_EQ(std::vector<int>({1, 3}), solution.nodesBetweenCriticalPoints(createLinkedList({5, 3, 1, 2, 5, 1, 2}, true).get()));
    ASSERT_EQ(std::vector<int>({3, 3}), solution.nodesBetweenCriticalPoints(createLinkedList({1, 3, 2, 2, 3, 2, 2, 2, 7}, true).get()));
}

TEST(FindMinMaxNumberOfNodesBetweenCriticalPointsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1}), solution.nodesBetweenCriticalPoints(createLinkedList({4, 2, 4, 1}, true).get()));
}

}
