#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Node
{
public:
    Node(int value) : val(value), prev(nullptr), next(nullptr), child(nullptr)
    {
    }

    int val;
    Node* prev;
    Node* next;
    Node* child;
};

}

namespace
{

class Solution
{
public:
    Node* flatten(Node* head)
    {
        flattenDescendants(head);
        return head;
    }

private:
    Node* flattenDescendants(Node* head)
    {
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr)
        {
            current->prev = prev;
            if (prev != nullptr)
                prev->next = current;
            prev = current;
            Node* next = current->next;
            if (current->child != nullptr)
            {
                prev = flattenDescendants(current->child);
                current->next = current->child;
                current->child->prev = current;
                current->child = nullptr;
            }
            current = next;
        }
        return prev;
    }
};

}

namespace
{

void deleteStructure(Node* head)
{
    while (head != nullptr)
    {
        Node* next = head->next;
        if (head->child != nullptr)
            deleteStructure(head->child);
        delete head;
        head = next;
    }
}

std::shared_ptr<Node> createHolder(Node* head)
{
    return std::shared_ptr<Node>(head, deleteStructure);
}

class Codec
{
public:
    // Encodes an object into a single string.
    std::string serialize(Node* head) const;
    // Decodes your encoded data to object.
    std::shared_ptr<Node> deserialize(std::string const &data) const;

    static std::string createData(Node* head);
    static std::shared_ptr<Node> createObject(std::string const &data);

private:
    static constexpr char StartChar = '[';
    static constexpr char Delimiter = ',';
    static constexpr char FinishChar = ']';
    static constexpr char const* NullValue = "null";

    void serializeLevel(Node* head, size_t headShift, Node* &childHead, size_t &childHeadShift, std::string &dest) const;
    Node* deserializeLevel(std::string const &data, size_t &index, Node* prevLevelHead) const;
};

void Codec::serializeLevel(Node* head, size_t headShift, Node* &childHead, size_t &childHeadShift, std::string &dest) const
{
    for (size_t shift = 0; shift < headShift; ++shift)
    {
        if (!dest.empty())
            dest.push_back(Delimiter);
        dest.append(NullValue);
    }
    childHead = nullptr;
    childHeadShift = 0;
    size_t shift = 0;
    while (head != nullptr)
    {
        if (!dest.empty())
            dest.push_back(Delimiter);
        dest.append(std::to_string(head->val));
        if (head->child != nullptr)
        {
            childHead = head->child;
            childHeadShift = shift;
        }
        ++shift;
        head = head->next;
    }
}

std::string Codec::serialize(Node* head) const
{
    std::string dest;
    size_t currentShift = 0;
    while (head != nullptr)
    {
        if (!dest.empty())
        {
            dest.push_back(Delimiter);
            dest.append(NullValue);
        }
        Node* childHead = nullptr;
        size_t childHeadShift = 0;
        serializeLevel(head, currentShift, childHead, childHeadShift, dest);
        head = childHead;
        currentShift = childHeadShift;
    }
    return StartChar + dest + FinishChar;
}

Node* Codec::deserializeLevel(std::string const &data, size_t &index, Node* prevLevelHead) const
{
    if (data[index] == FinishChar)
        return nullptr;
    bool skip = true;
    bool stop = false;
    Node* head = nullptr;
    Node* current = nullptr;
    while (!stop && data[index] != FinishChar)
    {
        size_t delimiterPos = data.find(Delimiter, index);
        if (delimiterPos == std::string::npos)
            delimiterPos = data.size() - 1;
        std::string part(data.substr(index, delimiterPos - index));
        if (part == NullValue)
        {
            if (skip && prevLevelHead != nullptr)
                prevLevelHead = prevLevelHead->next;
            else
                stop = true;
        }
        else
        {
            skip = false;
            const int val = std::stoi(part);
            Node* node = new Node(val);
            if (head == nullptr)
            {
                current = head = node;
                if (prevLevelHead != nullptr)
                    prevLevelHead->child = head;
            }
            else
            {
                current->next = node;
                node->prev = current;
                current = node;
            }
        }
        index = delimiterPos + (data[delimiterPos] == FinishChar ? 0 : 1);
    }
    return head;
}

std::shared_ptr<Node> Codec::deserialize(std::string const &data) const
{
    // skip first '['
    size_t index = 1;
    Node* head = nullptr;
    Node* current = nullptr;
    head = current = deserializeLevel(data, index, nullptr);
    while (current != nullptr)
        current = deserializeLevel(data, index, current);
    return createHolder(head);
}

std::shared_ptr<Node> Codec::createObject(std::string const &data)
{
    return Codec().deserialize(data);
}

std::string Codec::createData(Node* head)
{
    return Codec().serialize(head);
}

}

namespace FlattenMultilevelDoublyLinkedListTask
{

TEST(FlattenMultilevelDoublyLinkedListTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ("[1,2,3,7,8,11,12,9,10,4,5,6]", Codec::createData(solution.flatten(Codec::createObject("[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]").get())));
    ASSERT_EQ("[1,3,2]", Codec::createData(solution.flatten(Codec::createObject("[1,2,null,3]").get())));
    ASSERT_EQ("[]", Codec::createData(solution.flatten(Codec::createObject("[]").get())));
}

TEST(FlattenMultilevelDoublyLinkedListTaskTests, CheckCodec)
{
    ASSERT_EQ("[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]", Codec::createData(Codec::createObject("[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]").get()));
    ASSERT_EQ("[1,2,3,7,8,11,12,9,10,4,5,6]", Codec::createData(Codec::createObject("[1,2,3,7,8,11,12,9,10,4,5,6]").get()));
    ASSERT_EQ("[1,2,null,3]", Codec::createData(Codec::createObject("[1,2,null,3]").get()));
    ASSERT_EQ("[1,3,2]", Codec::createData(Codec::createObject("[1,3,2]").get()));
    ASSERT_EQ("[]", Codec::createData(Codec::createObject("[]").get()));
}

}