#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> shortestSubstrings(std::vector<std::string> const &arr) const
    {
        // prepare
        std::unordered_map<std::string, SubstringData> knownSubstrings;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            for (size_t start = 0; start < arr[index].size(); ++start)
            {
                std::string current;
                current.reserve(arr[index].size() - start);
                for (size_t end = start; end < arr[index].size(); ++end)
                {
                    current.push_back(arr[index][end]);
                    auto iterator = knownSubstrings.find(current);
                    if (iterator == knownSubstrings.cend())
                        knownSubstrings.emplace(current, SubstringData(1, index));
                    else if (index != iterator->second.Index)
                        ++iterator->second.Count;
                }
            }
        }
        // answer
        std::vector<std::string> answer(arr.size(), "");
        for (auto const &[substring, data] : knownSubstrings)
        {
            if (data.Count > 1)
                continue;
            const size_t index = data.Index;
            if (answer[index].empty() ||
                (substring.size() < answer[index].size()) ||
                ((substring.size() == answer[index].size()) && (substring < answer[index])))
                answer[index] = substring;
        }
        return answer;
    }

private:
    struct SubstringData
    {
        SubstringData(size_t count, size_t index) : Count(count), Index(index)
        {
        }

        size_t Count;
        size_t Index;
    };
};

}

namespace ShortestUncommonSubstrInArrayTask
{

TEST(ShortestUncommonSubstrInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"ab", "", "ba", ""}), solution.shortestSubstrings({"cab", "ad", "bad", "c"}));
    ASSERT_EQ(std::vector<std::string>({"", "", "abcd"}), solution.shortestSubstrings({"abc", "bcd", "abcd"}));
}

TEST(ShortestUncommonSubstrInArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"g", "x", "z", "r", "i", "c", "h"}),
              solution.shortestSubstrings({"gfnt", "xn", "mdz", "yfmr", "fi", "wwncn", "hkdy"}));
    ASSERT_EQ(std::vector<std::string>({"b", "g", "n", "k", "a"}),
              solution.shortestSubstrings({"vbb", "grg", "lexn", "oklqe", "yxav"}));
}

}