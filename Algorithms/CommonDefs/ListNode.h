#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

namespace CommonDefs
{

struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr)
    {
    }
    ListNode(int x) : val(x), next(nullptr)
    {
    }
    ListNode(int x, ListNode *next) : val(x), next(next)
    {
    }
};

std::shared_ptr<ListNode> createLinkedList(std::vector<int> const &source, bool withDeleter)
{
    std::function<void(ListNode*)> linkedListDeleter = [](ListNode* root)
    {
        ListNode* current = root;
        while (current != nullptr)
        {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    };
    ListNode *current = nullptr;
    for (std::vector<int>::const_reverse_iterator it = source.crbegin(); it != source.crend(); ++it)
        current = new ListNode(*it, current);
    return std::shared_ptr<ListNode>(current, withDeleter ? linkedListDeleter : [](ListNode* root) { /* do nothing */ });
}

std::vector<int> convertLinkedListToVector(ListNode* current)
{
    std::vector<int> dest;
    while (current != nullptr)
    {
        dest.push_back(current->val);
        current = current->next;
    }
    return dest;
}

void checkAndDeleteLinkedList(std::vector<int> const &expectedValues, ListNode *current)
{
    std::function<void(ListNode*)> linkedListDeleter = [](ListNode* root)
    {
        ListNode* current = root;
        while (current != nullptr)
        {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    };
    std::shared_ptr<ListNode> linkedListHolder(current, linkedListDeleter);
    std::vector<int> actualValues(convertLinkedListToVector(current));
    ASSERT_EQ(expectedValues, actualValues);
}

}