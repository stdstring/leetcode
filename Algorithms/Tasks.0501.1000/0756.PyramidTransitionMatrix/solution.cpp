#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool pyramidTransition(std::string const &bottom, std::vector<std::string> const &allowed) const
    {
        std::unordered_map<std::string, std::vector<char>> allowedMap;
        for (std::string const &entry : allowed)
            allowedMap[entry.substr(0, 2)].emplace_back(entry.back());
        std::unordered_set<std::string> knownValues;
        return processLayer(bottom, allowedMap, knownValues);
    }

private:
    [[nodiscard]] bool processLayer(std::string const &current,
                                    std::unordered_map<std::string, std::vector<char>> const &allowed,
                                    std::unordered_set<std::string> &knownValues) const
    {
        if (current.size() == 2)
            return allowed.contains(current);
        std::vector<std::vector<char> const*> nextLayerCases(current.size() - 1);
        for (size_t index = 1; index < current.size(); ++index)
        {
            std::string baseValue(current.substr(index - 1, 2));
            auto iterator = allowed.find(baseValue);
            if (iterator == allowed.cend())
                return false;
            nextLayerCases[index - 1] = &(iterator->second);
        }
        std::string next;
        return buildNextLayer(nextLayerCases, 0, next, allowed, knownValues);
    }

    [[nodiscard]] bool buildNextLayer(std::vector<std::vector<char> const*> const &nextLayerCases,
                                      size_t index,
                                      std::string &next,
                                      std::unordered_map<std::string, std::vector<char>> const &allowed,
                                      std::unordered_set<std::string> &knownValues) const
    {
        for (const char ch : *nextLayerCases[index])
        {
            next.push_back(ch);
            if (buildNextLayerImpl(nextLayerCases, index, next, allowed, knownValues))
                return true;
            next.pop_back();
        }
        return false;
    }

    [[nodiscard]] bool buildNextLayerImpl(std::vector<std::vector<char> const*> const &nextLayerCases,
                                          size_t index,
                                          std::string &next,
                                          std::unordered_map<std::string, std::vector<char>> const &allowed,
                                          std::unordered_set<std::string> &knownValues) const
    {
        if (index == (nextLayerCases.size() - 1))
        {
            if (knownValues.contains(next))
                return false;
            knownValues.emplace(next);
            return processLayer(next, allowed, knownValues);
        }
        return buildNextLayer(nextLayerCases, index + 1, next, allowed, knownValues);
    }
};

}

namespace PyramidTransitionMatrixTask
{

TEST(PyramidTransitionMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.pyramidTransition("BCD", {"BCC", "CDE", "CEA", "FFF"}));
    ASSERT_EQ(false, solution.pyramidTransition("AAAA", {"AAB", "AAC", "BCD", "BBE", "DEF"}));
}

TEST(PyramidTransitionMatrixTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.pyramidTransition("DBCDA", {"DBD", "BCC", "CDD", "DAD", "DDA", "AAC", "CCA", "BCD"}));
}

}