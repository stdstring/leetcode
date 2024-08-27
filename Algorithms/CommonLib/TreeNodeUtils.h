#pragma once

#include <memory>
#include <string>
#include <vector>

#include "TreeNode.h"

namespace CommonLib
{

void deleteTree(TreeNode* root);
void deleteTree(NTreeNode* root);
std::shared_ptr<TreeNode> createTreeHolder(TreeNode* root);
std::shared_ptr<NTreeNode> createTreeHolder(NTreeNode* root);
void checkTreeNextLinks(std::vector<std::vector<int>> const &nextLinksLayers, TreeNode* root);
TreeNode* findNodeByValue(TreeNode* root, int value);

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(std::shared_ptr<TreeNode> const &root) const;
    std::string serializeRaw(TreeNode* root) const;
    std::string serialize(std::shared_ptr<NTreeNode> const &root) const;
    std::string serializeRaw(NTreeNode* root) const;
    // Decodes your encoded data to tree.
    std::shared_ptr<TreeNode> deserialize(std::string const &data) const;
    TreeNode* deserializeRaw(std::string const &data) const;
    std::shared_ptr<NTreeNode> deserializeN(std::string const &data) const;
    NTreeNode* deserializeRawN(std::string const &data) const;

    static std::shared_ptr<TreeNode> createTree(std::string const &data);
    static TreeNode* createTreeRaw(std::string const &data);
    static std::shared_ptr<NTreeNode> createNTree(std::string const &data);
    static NTreeNode* createNTreeRaw(std::string const &data);
    static std::string createData(std::shared_ptr<TreeNode> const &root);
    static std::string createDataRaw(TreeNode* root);
    static std::string createData(std::shared_ptr<NTreeNode> const &root);
    static std::string createDataRaw(NTreeNode* root);
};

}