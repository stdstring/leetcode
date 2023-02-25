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
    ListNode* removeZeroSumSublists(ListNode* head) const
    {
        const std::vector<int> source(convert(head));
        std::vector<int> dest;
        dest.reserve(source.size());
        std::unordered_multiset<int> prefixes;
        prefixes.insert(0);
        int prefixSum = 0;
        for (int number : source)
        {
            if (number == 0)
                continue;
            prefixSum += number;
            const auto currentIterator = prefixes.find(prefixSum);
            if (currentIterator == prefixes.cend())
            {
                prefixes.insert(prefixSum);
                dest.push_back(number);
            }
            else
            {
                const int currentSum = prefixSum;
                prefixSum -= number;
                while (prefixSum != currentSum)
                {
                    const auto iterator = prefixes.find(prefixSum);
                    prefixes.erase(iterator);
                    prefixSum -= dest.back();
                    dest.pop_back();
                }
            }
        }
        return convert(dest);
    }

private:
    std::vector<int> convert(ListNode* head) const
    {
        std::vector<int> dest;
        while (head != nullptr)
        {
            dest.push_back(head->val);
            head = head->next;
        }
        return dest;
    }

    [[nodiscard]] ListNode* convert(std::vector<int> const &numbers) const
    {
        ListNode* head = nullptr;
        ListNode* current = nullptr;
        for (const int number : numbers)
        {
            if (current == nullptr)
                head = current = new ListNode(number);
            else
            {
                ListNode* next = new ListNode(number);
                current->next = next;
                current = next;
            }
        }
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace RemoveZeroSumConsNodesFromLinkedListTask
{

TEST(RemoveZeroSumConsNodesFromLinkedListTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({3, 1}, solution.removeZeroSumSublists(createLinkedList({1, 2, -3, 3, 1}, true).get()));
    checkAndDeleteLinkedList({1, 2, 4}, solution.removeZeroSumSublists(createLinkedList({1, 2, 3, -3, 4}, true).get()));
    checkAndDeleteLinkedList({1}, solution.removeZeroSumSublists(createLinkedList({1, 2, 3, -3, -2}, true).get()));
}

TEST(RemoveZeroSumConsNodesFromLinkedListTaskTests, FromWrongAnswers)
{
    const Solution solution;
    checkAndDeleteLinkedList({}, solution.removeZeroSumSublists(createLinkedList({1, -1}, true).get()));
}

}