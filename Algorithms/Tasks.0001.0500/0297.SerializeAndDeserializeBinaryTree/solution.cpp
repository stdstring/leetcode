#include <deque>
#include <string>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) const
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
    TreeNode* deserialize(std::string const &data) const
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
                    processedNodes.front()->left=current;
                    leftChild = false;
                }
                else
                {
                    processedNodes.front()->right=current;
                    processedNodes.pop_front();
                    leftChild = true;
                }
            }
            index = endIndex;
        }
        return root;
    }
};

}

namespace SerializeAndDeserializeBinaryTreeTask
{

TEST(SerializeAndDeserializeBinaryTreeTaskTests, Examples)
{
    const Codec codec;
    ASSERT_EQ("[1,2,3,null,null,4,5]", codec.serialize(codec.deserialize("[1,2,3,null,null,4,5]")));
}

}