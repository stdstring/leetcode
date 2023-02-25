#include <algorithm>
#include <memory>
#include <random>
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
    Solution(ListNode* head) : _generator(std::random_device()())
    {
        while (head != nullptr)
        {
            _nodes.push_back(head);
            head = head->next;
        }
        _distribution = std::uniform_int_distribution<>(0, static_cast<int>(_nodes.size() - 1));
    }

    // Returns a random node's value.
    int getRandom()
    {
        return _nodes[_distribution(_generator)]->val;
    }

private:
    std::mt19937 _generator;
    std::uniform_int_distribution<> _distribution;
    std::vector<ListNode*> _nodes;
};

}

using CommonLib::createLinkedList;

namespace
{

bool contains(std::vector<int> const &sourceValues, int value)
{
    return std::find(sourceValues.cbegin(), sourceValues.cend(), value) != sourceValues.cend();
}

}

namespace LinkedListRandomNodeTask
{

TEST(LinkedListRandomNodeTaskTests, Examples)
{
    const std::vector<int> values({1, 2, 3});
    const std::shared_ptr<ListNode> linkedList(createLinkedList(values, true));
    Solution solution(linkedList.get());
    // TODO (std_string) : think about check for uniform distribution
    constexpr size_t caseCount = 5;
    for (size_t caseIndex = 0; caseIndex < caseCount; ++caseIndex)
        ASSERT_TRUE(contains(values, solution.getRandom()));
}

}