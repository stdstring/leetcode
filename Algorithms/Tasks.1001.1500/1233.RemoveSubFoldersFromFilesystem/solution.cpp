#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> removeSubfolders(std::vector<std::string> const &folder) const
    {
        std::vector<std::string> sortedFolder(folder);
        std::sort(sortedFolder.begin(), sortedFolder.end());
        std::vector<std::string> dest;
        std::string lastFolder;
        for (std::string const &current : sortedFolder)
        {
            if (dest.empty() ||
                (current.size() < lastFolder.size()) ||
                ((current.compare(0, lastFolder.size(), lastFolder) != 0)))
            {
                dest.push_back(current);
                lastFolder.assign(current).push_back('/');
            }
        }
        return dest;
    }
};

}

namespace RemoveSubFoldersFromFilesystemTask
{

TEST(RemoveSubFoldersFromFilesystemTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"/a", "/c/d", "/c/f"}), solution.removeSubfolders({"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"}));
    ASSERT_EQ(std::vector<std::string>({"/a"}), solution.removeSubfolders({"/a", "/a/b/c", "/a/b/d"}));
    ASSERT_EQ(std::vector<std::string>({"/a/b/c", "/a/b/ca", "/a/b/d"}), solution.removeSubfolders({"/a/b/c", "/a/b/ca", "/a/b/d"}));
}

TEST(RemoveSubFoldersFromFilesystemTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"/ah/al"}), solution.removeSubfolders({"/ah/al/am", "/ah/al"}));
}

}