#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<std::string>> findDuplicate(std::vector<std::string> const &paths) const
    {
        std::map<std::string, std::vector<std::string>> contentMap;
        for (std::string const &entry : paths)
            processDirectoryEntry(entry, contentMap);
        std::vector<std::vector<std::string>> result;
        for (auto const &entry : contentMap)
        {
            if (entry.second.size() > 1)
                result.push_back(entry.second);
        }
        return result;
    }

private:
    void processDirectoryEntry(std::string const &entry, std::map<std::string, std::vector<std::string>> &contentMap) const
    {
        size_t index = entry.find(' ', 0);
        const std::string directory(entry.substr(0, index));
        ++index;
        while (index < entry.size())
        {
            const size_t filenameEndPos = entry.find('(', index);
            std::string filename(entry.substr(index, filenameEndPos - index));
            index = filenameEndPos + 1;
            const size_t contentEndPos = entry.find(')', index);
            std::string content(entry.substr(index, contentEndPos - index));
            index = contentEndPos + 1;
            std::string path = directory + "/" + filename;
            std::map<std::string, std::vector<std::string>>::iterator it = contentMap.find(content);
            if (it == contentMap.end())
                contentMap.emplace(content, std::vector<std::string>({path}));
            else
                it->second.push_back(path);
            // process space
            ++index;
        }
    }
};

}

namespace FindDuplicateFileInSystemTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"root/a/1.txt", "root/c/3.txt"}, {"root/a/2.txt", "root/c/d/4.txt", "root/4.txt"}}),
              solution.findDuplicate({"root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"}));
}

}