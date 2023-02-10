#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long distinctNames(std::vector<std::string> const &ideas) const
    {
        std::unordered_map<std::string, int> ideasMap;
        std::array<FirstLetterData, AlphabetSize> letterData;
        for (std::string const &idea : ideas)
            ideasMap.emplace(idea, 0);
        for (auto iterator = ideasMap.begin(); iterator != ideasMap.end(); ++iterator)
        {
            std::string current(iterator->first);
            const size_t currentIndex = current.front() - AlphabetStart;
            ++letterData[currentIndex].Count;
            for (char ch = AlphabetStart; ch <= AlphabetEnd; ++ch)
            {
                current.front() = ch;
                if (ideasMap.count(current) > 0)
                {
                    const size_t letterIndex = ch - AlphabetStart;
                    iterator->second |= (1 << letterIndex);
                    ++letterData[currentIndex].FirstLetterInvalidCounts[letterIndex];
                }
            }
        }
        size_t result = 0;
        for (auto const &[idea, invalidMask] : ideasMap)
        {
            const size_t ideaIndex = idea.front() - AlphabetStart;
            for (char ch = AlphabetStart; ch <= AlphabetEnd; ++ch)
            {
                const size_t letterIndex = ch - AlphabetStart;
                const int letterMask = 1 << letterIndex;
                if ((invalidMask & letterMask) > 0)
                    continue;
                result += (letterData[letterIndex].Count - letterData[letterIndex].FirstLetterInvalidCounts[ideaIndex]);
            }
        }
        return static_cast<long long>(result);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr char AlphabetStart = 'a';
    static constexpr char AlphabetEnd = 'z';

    struct FirstLetterData
    {
        FirstLetterData()
        {
            FirstLetterInvalidCounts.fill(0);
        }

        size_t Count = 0;
        std::array<size_t, AlphabetSize> FirstLetterInvalidCounts = {};
    };
};

}

namespace NamingCompanyTask
{

TEST(NamingCompanyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.distinctNames({"coffee", "donuts", "time", "toffee"}));
    ASSERT_EQ(0, solution.distinctNames({"lack", "back"}));
}

TEST(NamingCompanyTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4934, solution.distinctNames({"sfuzder", "spklurny", "kvdolme", "kbbdklkpgk", "za", "mdbsmnjiu", "pzydbfwiw", "lvvyshmd",
                                            "ow", "ssipb", "jucpsquexm", "ffuzder", "uftruik", "ringlxh", "jz", "sjlxouiv", "csdbtsvg",
                                            "openygbaix", "dcn", "r", "hwql", "ok", "y", "sze", "ttptd", "atxp", "ejfpsea", "vjfpsea",
                                            "lj", "drmvufbt", "zxambug", "ozpxq", "qzydbfwiw", "lqxik", "bjo", "rrmvufbt", "jvl", "rzxaaa",
                                            "nmfydhawa", "shlwkf", "rcl", "hhn", "yrmcsc", "yieuzizaeh", "nrmvufbt", "rinsldgdpp", "wqg",
                                            "tyhkgqcu", "rsdbtsvg", "zvehtqiqxa", "jtz", "mjaguebiy", "fztbpozhf", "zzpxq", "ue", "foktqxiqe",
                                            "ztf", "dn", "lxambug", "kinsldgdpp", "jhn", "k", "i", "qxtava", "roktqxiqe", "hr", "bwzw",
                                            "mot", "cadj", "x", "bcep", "u", "kzydbfwiw", "ahku", "ijo"}));
}

}