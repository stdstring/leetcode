#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "ListNode.h"
#include "ListNodeUtils.h"

namespace
{

void deleteLinkedList(CommonLib::ListNode* root)
{
    CommonLib::ListNode* current = root;
    while (current != nullptr)
    {
        CommonLib::ListNode* next = current->next;
        delete current;
        current = next;
    }
}

}

std::shared_ptr<CommonLib::ListNode> CommonLib::createLinkedList(std::vector<int> const &source, bool withDeleter)
{
    ListNode *current = nullptr;
    for (std::vector<int>::const_reverse_iterator it = source.crbegin(); it != source.crend(); ++it)
        current = new ListNode(*it, current);
    return createLinkedListHolder<CommonLib::ListNode>(current, withDeleter);
}

std::vector<int> CommonLib::convertLinkedListToVector(ListNode* current)
{
    std::vector<int> dest;
    while (current != nullptr)
    {
        dest.push_back(current->val);
        current = current->next;
    }
    return dest;
}

void CommonLib::checkAndDeleteLinkedList(std::vector<int> const &expectedValues, ListNode *current)
{
    std::shared_ptr<ListNode> linkedListHolder(current, deleteLinkedList);
    const std::vector<int> actualValues(convertLinkedListToVector(current));
    ASSERT_EQ(expectedValues, actualValues);
    if (expectedValues.empty())
        ASSERT_EQ(nullptr, current);
}