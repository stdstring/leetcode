#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> getFolderNames(std::vector<std::string> const &names) const
    {
        std::vector<std::string> uniqueNames;
        uniqueNames.reserve(names.size());
        std::unordered_map<std::string, int> knownFolderNames;
        knownFolderNames.reserve(names.size());
        for (std::string const &name : names)
        {
            if (knownFolderNames.count(name) == 0)
                appendUniqueName(name, uniqueNames, knownFolderNames);
            else
            {
                std::pair<std::string, int> uniqueName(findUniqueName(name, knownFolderNames));
                knownFolderNames[name] = uniqueName.second + 1;
                appendUniqueName(uniqueName.first, uniqueNames, knownFolderNames);
            }
        }
        return uniqueNames;
    }

private:
    [[nodiscard]] std::pair<std::string, int> findUniqueName(std::string const &name, std::unordered_map<std::string, int> const &knownFolderNames) const
    {
        int uniqueNumber = knownFolderNames.at(name);
        while (true)
        {
            std::string uniqueName(name);
            uniqueName.append("(").append(std::to_string(uniqueNumber)).append(")");
            if (knownFolderNames.count(uniqueName) == 0)
                return {uniqueName, uniqueNumber};
            ++uniqueNumber;
        }
    }

    void appendUniqueName(std::string const &uniqueName, std::vector<std::string> &uniqueNames, std::unordered_map<std::string, int> &knownFolderNames) const
    {
        knownFolderNames.emplace(uniqueName, 1);
        uniqueNames.push_back(uniqueName);
    }
};

}

namespace MakingFileNamesUniqueTask
{

TEST(MakingFileNamesUniqueTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"pes", "fifa", "gta", "pes(2019)"}), solution.getFolderNames({"pes", "fifa", "gta", "pes(2019)"}));
    ASSERT_EQ(std::vector<std::string>({"gta", "gta(1)", "gta(2)", "avalon"}), solution.getFolderNames({"gta", "gta(1)", "gta", "avalon"}));
    ASSERT_EQ(std::vector<std::string>({"onepiece", "onepiece(1)", "onepiece(2)", "onepiece(3)", "onepiece(4)"}), solution.getFolderNames({"onepiece", "onepiece(1)", "onepiece(2)", "onepiece(3)", "onepiece"}));
    ASSERT_EQ(std::vector<std::string>({"wano", "wano(1)", "wano(2)", "wano(3)"}), solution.getFolderNames({"wano", "wano", "wano", "wano"}));
    ASSERT_EQ(std::vector<std::string>({"kaido", "kaido(1)", "kaido(2)", "kaido(1)(1)"}), solution.getFolderNames({"kaido", "kaido(1)", "kaido", "kaido(1)"}));
    ASSERT_EQ(std::vector<std::string>({"kaido", "kaido(1)", "kaido(2)", "kaido(1)(1)"}), solution.getFolderNames({"kaido", "kaido(1)", "kaido", "kaido(1)"}));
    ASSERT_EQ(std::vector<std::string>({"t", "t(2)", "t(4)", "t(1)", "t(3)"}), solution.getFolderNames({"t", "t(2)", "t(4)", "t", "t"}));
}

TEST(MakingFileNamesUniqueTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"kaido", "kaido(1)", "kaido(2)", "kaido(1)(1)", "kaido(2)(1)"}), solution.getFolderNames({"kaido", "kaido(1)", "kaido", "kaido(1)", "kaido(2)"}));
}

}