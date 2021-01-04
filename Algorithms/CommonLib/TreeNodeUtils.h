#pragma once

#include <memory>
#include <string>
#include <vector>

#include "TreeNode.h"

namespace CommonLib
{

std::shared_ptr<TreeNode> createTreeHolder(TreeNode* root);
void checkTreeNextLinks(std::vector<std::vector<int>> const &nextLinksLayers, TreeNode* root);
TreeNode* findNodeByValue(TreeNode* root, int value);

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(std::shared_ptr<TreeNode> const &root) const;
    // Decodes your encoded data to tree.
    std::shared_ptr<TreeNode> deserialize(std::string const &data) const;

    static std::shared_ptr<TreeNode> createTree(std::string const &data);
    static std::string createData(std::shared_ptr<TreeNode> const &root);
};

}