#include <deque>
#include <memory>
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
    std::string dest;
    dest.push_back('[');
    std::deque<TreeNode*> processedNodes;
    if (root != nullptr)
        processedNodes.push_back(root);
    int lastNonNullIndex = root != nullptr ? 0 : -1;
    while (lastNonNullIndex >= 0)
    {
        TreeNode* current = processedNodes.front();
        if (dest.size() > 1)
            dest.push_back(',');
        dest.append(current == nullptr ? "null" : std::to_string(current->val));
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
    dest.push_back(']');
    return dest;
}

// Decodes your encoded data to tree.
std::shared_ptr<CommonLib::TreeNode> CommonLib::Codec::deserialize(std::string const& data) const
{
    return createTreeHolder(deserializeRaw(data));
}

CommonLib::TreeNode* CommonLib::Codec::deserializeRaw(std::string const &data) const
{
    //data[0] == '['
    //data[data.size() - 1] == ']'
    size_t index = 1;
    std::deque<TreeNode*> processedNodes;
    TreeNode* root = nullptr;
    bool leftChild = true;
    while (index < (data.size() - 1))
    {
        // process ',' char
        if (root != nullptr)
            ++index;
        size_t endIndex = index + 1;
        while (data[endIndex] != ',' && data[endIndex] != ']')
            ++endIndex;
        std::string part = data.substr(index, endIndex - index);
        TreeNode* current = part == "null" ? nullptr : new TreeNode(std::stoi(part));
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
        index = endIndex;
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