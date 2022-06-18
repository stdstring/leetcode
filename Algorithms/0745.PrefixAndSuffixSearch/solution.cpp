#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class WordFilter
{
public:
    WordFilter(std::vector<std::string> const &words)
    {
        std::string bufferKey;
        bufferKey.reserve(MaxPrefixSize + MaxSuffixSize + 1);
        for (size_t wordIndex = 0; wordIndex < words.size(); ++wordIndex)
        {
            std::string const &word(words[wordIndex]);
            for (size_t prefixLength = 1; prefixLength <= std::min(MaxPrefixSize, word.size()); ++prefixLength)
            {
                for (size_t suffixLength = 1; suffixLength <= std::min(MaxSuffixSize, word.size()); ++suffixLength)
                {
                    bufferKey.resize(0);
                    std::copy(std::prev(word.cend(), static_cast<int>(suffixLength)), word.cend(), std::back_inserter(bufferKey));
                    bufferKey.push_back(Delimiter);
                    std::copy(word.cbegin(), std::next(word.cbegin(), static_cast<int>(prefixLength)), std::back_inserter(bufferKey));
                    auto iterator = _suffixPrefixMap.find(bufferKey);
                    if (iterator == _suffixPrefixMap.end())
                        _suffixPrefixMap.emplace(bufferKey, wordIndex);
                    else
                        iterator->second = wordIndex;
                }
            }
        }
    }

    [[nodiscard]] int f(std::string const &prefix, std::string const &suffix) const
    {
        std::string key;
        key.reserve(prefix.size() + suffix.size() + 1);
        std::copy(suffix.cbegin(), suffix.cend(), std::back_inserter(key));
        key.push_back(Delimiter);
        std::copy(prefix.cbegin(), prefix.cend(), std::back_inserter(key));
        const auto iterator = _suffixPrefixMap.find(key);
        return iterator == _suffixPrefixMap.cend() ? -1 : static_cast<int>(iterator->second);
    }

private:
    static constexpr size_t MaxPrefixSize = 10;
    static constexpr size_t MaxSuffixSize = 10;
    static constexpr char Delimiter = '#';
    std::unordered_map<std::string, size_t> _suffixPrefixMap;
};

}

namespace PrefixAndSuffixSearchTask
{

TEST(PrefixAndSuffixSearchTaskTests, Examples)
{
    const WordFilter filter({ "apple" });
    ASSERT_EQ(0, filter.f("a", "e"));
}

TEST(PrefixAndSuffixSearchTaskTests, FromWrongAnswers)
{
    const WordFilter filter({"cabaabaaaa", "ccbcababac", "bacaabccba", "bcbbcbacaa", "abcaccbcaa", "accabaccaa", "cabcbbbcca", "ababccabcb", "caccbbcbab", "bccbacbcba"});
    ASSERT_EQ(9, filter.f("bccbacbcba", "a"));
    ASSERT_EQ(4, filter.f("ab", "abcaccbcaa"));
    ASSERT_EQ(5, filter.f("a", "aa"));
    ASSERT_EQ(0, filter.f("cabaaba", "abaaaa"));
    ASSERT_EQ(8, filter.f("cacc", "accbbcbab"));
    ASSERT_EQ(1, filter.f("ccbcab", "bac"));
    ASSERT_EQ(2, filter.f("bac", "cba"));
    ASSERT_EQ(5, filter.f("ac", "accabaccaa"));
    ASSERT_EQ(3, filter.f("bcbb", "aa"));
    ASSERT_EQ(1, filter.f("ccbca", "cbcababac"));
}

}