#include <deque>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "TreeNode.h"
#include "TreeNodeUtils.h"

namespace
{

void deleteTree(CommonLib::TreeNode* root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void writeNode(std::stringstream& stream, CommonLib::TreeNode* node)
{
    if (stream.str().size() > 1)
        stream << ',';
    if (node == nullptr)
        stream << "null";
    else
        stream << node->val;
}

CommonLib::TreeNode* readNode(std::stringstream& stream)
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
    return new CommonLib::TreeNode(value);
}

}

std::shared_ptr<CommonLib::TreeNode> CommonLib::createTreeHolder(TreeNode* root)
{
    return std::shared_ptr<TreeNode>(root, deleteTree);
}

void CommonLib::checkTreeNextLinks(std::vector<std::vector<int>> const &nextLinksLayers, TreeNode* root)
{
    TreeNode* leader = root;
    for (std::vector<int> const &layer : nextLinksLayers)
    {
        ASSERT_NE(nullptr, leader);
        TreeNode* current = leader;
        for (int value : layer)
        {
            ASSERT_NE(nullptr, current);
            ASSERT_EQ(value, current->val);
            current = current->next;
        }
        ASSERT_EQ(nullptr, current);
        // move to next leader
        while (leader != nullptr)
        {
            if (leader->left != nullptr)
            {
                leader = leader->left;
                break;
            }
            if (leader->right != nullptr)
            {
                leader = leader->right;
                break;
            }
            leader = leader->next;
        }
    }
}

CommonLib::TreeNode* CommonLib::findNodeByValue(CommonLib::TreeNode* root, int value)
{
    if (root == nullptr)
        return nullptr;
    if (root->val == value)
        return root;
    TreeNode* leftSearch = findNodeByValue(root->left, value);
    if (leftSearch != nullptr)
        return leftSearch;
    return findNodeByValue(root->right, value);
}

// Encodes a tree to a single string.
std::string CommonLib::Codec::serialize(std::shared_ptr<TreeNode> const &root) const
{
    return serializeRaw(root.get());
}

std::string CommonLib::Codec::serializeRaw(TreeNode* root) const
{
    std::stringstream dest;
    dest  <<  '[';
    std::deque<TreeNode*> processedNodes;
    if (root != nullptr)
        processedNodes.push_back(root);
    int lastNonNullIndex = root != nullptr ? 0 : -1;
    while (lastNonNullIndex >= 0)
    {
        TreeNode* current = processedNodes.front();
        writeNode(dest, current);
        processedNodes.pop_front();
        --lastNonNullIndex;
        if (current != nullptr)
        {
            processedNodes.push_back(current->left);
            if (current->left)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
            processedNodes.push_back(current->right);
            if (current->right)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
        }
    }
    dest << ']';
    return dest.str();
}

// Decodes your encoded data to tree.
std::shared_ptr<CommonLib::TreeNode> CommonLib::Codec::deserialize(std::string const& data) const
{
    return createTreeHolder(deserializeRaw(data));
}

CommonLib::TreeNode* CommonLib::Codec::deserializeRaw(std::string const& data) const
{
    constexpr size_t emptySize = 2;
    if (data.size() == emptySize)
        return nullptr;
    std::stringstream source(data);
    char delimiter;
    source >> delimiter;
    std::deque<TreeNode*> processedNodes;
    TreeNode* root = nullptr;
    bool leftChild = true;
    while (delimiter != ']')
    {
        TreeNode* current = readNode(source);
        if (current != nullptr)
            processedNodes.push_back(current);
        if (root == nullptr)
            root = current;
        else
        {
            if (leftChild)
            {
                processedNodes.front()->left = current;
                leftChild = false;
            }
            else
            {
                processedNodes.front()->right = current;
                processedNodes.pop_front();
                leftChild = true;
            }
        }
        source >> delimiter;
    }
    return root;
}

std::shared_ptr<CommonLib::TreeNode> CommonLib::Codec::createTree(std::string const &data)
{
    return Codec().deserialize(data);
}

CommonLib::TreeNode* CommonLib::Codec::createTreeRaw(std::string const& data)
{
    return Codec().deserializeRaw(data);
}

std::string CommonLib::Codec::createData(std::shared_ptr<TreeNode> const &root)
{
    return Codec().serialize(root);
}

std::string CommonLib::Codec::createDataRaw(TreeNode* root)
{
    return Codec().serializeRaw(root);
}