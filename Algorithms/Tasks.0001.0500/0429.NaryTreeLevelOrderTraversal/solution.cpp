#include <memory>
#include <queue>
#include <string>
#include <sstream>
#include <vector>

#include "gtest/gtest.h"

namespace
{

// TODO (std_string) : move into CommonLib
class Node
{
public:
    Node(int value) : val(value)
    {
    }

    int val;
    std::vector<Node*> children;
};

class Solution
{
public:
    std::vector<std::vector<int>> levelOrder(Node* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<std::vector<int>> result;
        processTree(root, 0, result);
        return result;
    }

private:
    void processTree(Node* root, size_t level, std::vector<std::vector<int>> &result) const
    {
        if (level == result.size())
            result.emplace_back();
        result[level].push_back(root->val);
        for (Node* child : root->children)
            processTree(child, level + 1, result);
    }
};

}

namespace
{

void deleteTree(Node* root)
{
    if (root == nullptr)
        return;
    for (Node* child : root->children)
        deleteTree(child);
    delete root;
}

Node* readNode(std::stringstream &stream)
{
    constexpr char nullHead = 'n';
    constexpr size_t nullTailSize = 3;
    if (stream.get() == nullHead)
    {
        for (size_t index = 0; index < nullTailSize; ++index)
            stream.get();
        return nullptr;
    }
    stream.unget();
    int value;
    stream >> value;
    return new Node(value);
}

// TODO (std_string) : move into CommonLib
std::shared_ptr<Node> createTreeHolder(Node* root)
{
    return std::shared_ptr<Node>(root, deleteTree);
}

// TODO (std_string) : move into CommonLib
class Codec
{
public:
    // Encodes a tree to a single string.
    // Decodes your encoded data to tree.
    std::shared_ptr<Node> deserialize(std::string const &data) const;
    Node* deserializeRaw(std::string const &data) const;

    static std::shared_ptr<Node> createTree(std::string const &data);
};

std::shared_ptr<Node> Codec::deserialize(std::string const &data) const
{
    return createTreeHolder(deserializeRaw(data));
}

Node* Codec::deserializeRaw(std::string const &data) const
{
    constexpr size_t emptySize = 2;
    if (data.size() == emptySize)
        return nullptr;
    std::stringstream source(data);
    char delimiter;
    source >> delimiter;
    Node* root = nullptr;
    std::queue<Node*> nodes;
    while (delimiter != ']')
    {
        Node* current = readNode(source);
        if (current == nullptr)
        {
            if (root == nullptr)
                root = nodes.front();
            else
                nodes.pop();
        }
        else
        {
            if (!nodes.empty())
                nodes.front()->children.push_back(current);
            nodes.push(current);
        }
        source >> delimiter;
    }
    return root;
}

std::shared_ptr<Node> Codec::createTree(std::string const &data)
{
    return Codec().deserialize(data);
}

}

namespace NaryTreeLevelOrderTraversalTask
{

TEST(NaryTreeLevelOrderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1}, {3, 2, 4}, {5, 6}}), solution.levelOrder(Codec::createTree("[1,null,3,2,4,null,5,6]").get()));
    ASSERT_EQ(std::vector<std::vector<int>>({{1}, {2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13}, {14}}),
              solution.levelOrder(Codec::createTree("[1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]").get()));
}

}