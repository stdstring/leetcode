#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

typedef std::pair<std::string, size_t> TCountData;

class Solution
{
public:
    std::vector<std::string> topKFrequent(std::vector<std::string> const &words, int k) const
    {
        std::unordered_map<std::string, size_t> wordsCountMap;
        for (std::string const &word : words)
            ++wordsCountMap[word];
        std::vector<TCountData> wordsData;
        wordsData.reserve(wordsCountMap.size());
        std::transform(wordsCountMap.cbegin(), wordsCountMap.cend(), std::back_inserter(wordsData), [](auto const &entry){ return TCountData(entry.first, entry.second); });
        auto sortComparer = [](TCountData const& left, TCountData const& right) { return left.second > right.second || (left.second == right.second && left.first < right.first); };
        std::partial_sort(wordsData.begin(), wordsData.begin() + k, wordsData.end(), sortComparer);
        std::vector<std::string> result;
        result.reserve(k);
        std::transform(wordsData.cbegin(), wordsData.cbegin() + k, std::back_inserter(result), [](TCountData const &entry){ return entry.first; });
        return result;
    }
};

}

namespace TopKFrequentWordsTask
{

TEST(TopKFrequentWordsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"i", "love"}), solution.topKFrequent({"i", "love", "leetcode", "i", "love", "coding"}, 2));
    ASSERT_EQ(std::vector<std::string>({"the", "is", "sunny", "day"}), solution.topKFrequent({"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}, 4));
}

}