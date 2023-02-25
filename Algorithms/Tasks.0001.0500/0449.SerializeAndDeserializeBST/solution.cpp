#include <deque>
#include <memory>
#include <string>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

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
        bool serializationStart = true;
        std::deque<TreeNode*> processedNodes;
        if (root != nullptr)
            processedNodes.push_back(root);
        int lastNonNullIndex = root != nullptr ? 0 : -1;
        while (lastNonNullIndex >= 0)
        {
            TreeNode* current = processedNodes.front();
            if (!serializationStart)
               dest.push_back(',');
            dest.append(current == nullptr ? "" : std::to_string(current->val));
            serializationStart = false;
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
        return dest;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string const &data) const
    {
        size_t index = 0;
        bool deserializationStart = true;
        std::deque<TreeNode*> processedNodes;
        TreeNode* root = nullptr;
        bool leftChild = true;
        while (index < data.size())
        {
            // process ',' char
            if (!deserializationStart)
                ++index;
            size_t endIndex = index;
            while (endIndex < data.size() && data[endIndex] != ',')
                ++endIndex;
            std::string part = data.substr(index, endIndex - index);
            TreeNode* current = part.empty() ? nullptr : new TreeNode(std::stoi(part));
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
            deserializationStart = false;
        }
        return root;
    }
};

}

using CommonLib::createTreeHolder;

namespace SerializeAndDeserializeBSTTask
{

TEST(SerializeAndDeserializeBSTTaskTests, Examples)
{
    const Codec codec;
    const std::shared_ptr<TreeNode> sourceTree = CommonLib::Codec::createTree("[2,1,3]");
    const std::shared_ptr<TreeNode> destTree = createTreeHolder(codec.deserialize(codec.serialize(sourceTree.get())));
    ASSERT_EQ("[2,1,3]", CommonLib::Codec::createData(destTree));
}

TEST(SerializeAndDeserializeBSTTaskTests, FromWrongAnswers)
{
    const Codec codec;
    const std::shared_ptr<TreeNode> sourceTree = CommonLib::Codec::createTree("[1,null,2]");
    const std::shared_ptr<TreeNode> destTree = createTreeHolder(codec.deserialize(codec.serialize(sourceTree.get())));
    ASSERT_EQ("[1,null,2]", CommonLib::Codec::createData(destTree));
}

}
