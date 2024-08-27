#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "TreeNode.h"
#include "TreeNodeUtils.h"

namespace
{

void writeNode(std::stringstream &stream, CommonLib::TreeNode* node)
{
    if (stream.str().size() > 1)
        stream << ',';
    if (node == nullptr)
        stream << "null";
    else
        stream << node->val;
}

void writeNode(std::stringstream &stream, CommonLib::NTreeNode* node)
{
    if (stream.str().size() > 1)
        stream << ',';
    if (node == nullptr)
        stream << "null";
    else
        stream << node->val;
}

CommonLib::TreeNode* readTreeNode(std::stringstream &stream)
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

CommonLib::NTreeNode* readNTreeNode(std::stringstream& stream)
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
    return new CommonLib::NTreeNode(value);
}

}

void CommonLib::deleteTree(TreeNode* root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void CommonLib::deleteTree(NTreeNode* root)
{
    if (root == nullptr)
        return;
    for (NTreeNode* child : root->children)
        deleteTree(child);
    delete root;
}

std::shared_ptr<CommonLib::TreeNode> CommonLib::createTreeHolder(TreeNode* root)
{
    return std::shared_ptr<TreeNode>(root, [](TreeNode* node){ deleteTree(node); });
}

std::shared_ptr<CommonLib::NTreeNode> CommonLib::createTreeHolder(NTreeNode* root)
{
    return std::shared_ptr<NTreeNode>(root, [](NTreeNode* node){ deleteTree(node); });
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
    std::queue<TreeNode*> processedNodes;
    if (root != nullptr)
        processedNodes.push(root);
    int lastNonNullIndex = root != nullptr ? 0 : -1;
    while (lastNonNullIndex >= 0)
    {
        TreeNode* current = processedNodes.front();
        writeNode(dest, current);
        processedNodes.pop();
        --lastNonNullIndex;
        if (current != nullptr)
        {
            processedNodes.push(current->left);
            if (current->left != nullptr)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
            processedNodes.push(current->right);
            if (current->right != nullptr)
                lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
        }
    }
    dest << ']';
    return dest.str();
}

std::string CommonLib::Codec::serialize(std::shared_ptr<NTreeNode> const &root) const
{
    return serializeRaw(root.get());
}

std::string  CommonLib::Codec::serializeRaw(NTreeNode* root) const
{
    std::stringstream dest;
    dest << '[';
    std::queue<NTreeNode*> processedNodes;
    if (root != nullptr)
        processedNodes.push(root);
    int lastNonNullIndex = root != nullptr ? 0 : -1;
    while (lastNonNullIndex >= 0)
    {
        NTreeNode* current = processedNodes.front();
        writeNode(dest, current);
        processedNodes.pop();
        --lastNonNullIndex;
        if (current != nullptr)
        {
            for(NTreeNode* child : current->children)
            {
                processedNodes.push(child);
                if (child != nullptr)
                    lastNonNullIndex = static_cast<int>(processedNodes.size()) - 1;
            }
        }
    }
    dest << ']';
    return dest.str();
}

// Decodes your encoded data to tree.
std::shared_ptr<CommonLib::TreeNode> CommonLib::Codec::deserialize(std::string const &data) const
{
    return createTreeHolder(deserializeRaw(data));
}

CommonLib::TreeNode* CommonLib::Codec::deserializeRaw(std::string const &data) const
{
    constexpr size_t emptySize = 2;
    if (data.size() == emptySize)
        return nullptr;
    std::stringstream source(data);
    char delimiter;
    source >> delimiter;
    std::queue<TreeNode*> processedNodes;
    TreeNode* root = nullptr;
    bool leftChild = true;
    while (delimiter != ']')
    {
        TreeNode* current = readTreeNode(source);
        if (current != nullptr)
            processedNodes.push(current);
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
                processedNodes.pop();
                leftChild = true;
            }
        }
        source >> delimiter;
    }
    return root;
}

std::shared_ptr<CommonLib::NTreeNode> CommonLib::Codec::deserializeN(std::string const &data) const
{
    return createTreeHolder(deserializeRawN(data));
}

CommonLib::NTreeNode* CommonLib::Codec::deserializeRawN(std::string const &data) const
{
    constexpr size_t emptySize = 2;
    if (data.size() == emptySize)
        return nullptr;
    std::stringstream source(data);
    char delimiter;
    source >> delimiter;
    std::queue<NTreeNode*> processedNodes;
    NTreeNode* root = nullptr;
    NTreeNode* parent = nullptr;
    while (delimiter != ']')
    {
        NTreeNode* current = readNTreeNode(source);
        if (root == nullptr)
            root = current;
        if (current == nullptr)
        {
            parent = processedNodes.front();
            processedNodes.pop();
        }
        else
        {
            processedNodes.push(current);
            if (parent != nullptr)
                parent->children.emplace_back(current);
        }
        source >> delimiter;
    }
    return root;
}

std::shared_ptr<CommonLib::TreeNode> CommonLib::Codec::createTree(std::string const &data)
{
    return Codec().deserialize(data);
}

CommonLib::TreeNode* CommonLib::Codec::createTreeRaw(std::string const &data)
{
    return Codec().deserializeRaw(data);
}

std::shared_ptr<CommonLib::NTreeNode> CommonLib::Codec::createNTree(std::string const &data)
{
    return Codec().deserializeN(data);
}

CommonLib::NTreeNode* CommonLib::Codec::createNTreeRaw(std::string const &data)
{
    return Codec().deserializeRawN(data);
}

std::string CommonLib::Codec::createData(std::shared_ptr<TreeNode> const &root)
{
    return Codec().serialize(root);
}

std::string CommonLib::Codec::createDataRaw(TreeNode* root)
{
    return Codec().serializeRaw(root);
}

std::string CommonLib::Codec::createData(std::shared_ptr<NTreeNode> const &root)
{
    return Codec().serialize(root);
}

std::string CommonLib::Codec::createDataRaw(NTreeNode* root)
{
    return Codec().serializeRaw(root);
}