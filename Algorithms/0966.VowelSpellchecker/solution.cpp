#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct SpellcheckerEntry
{
    SpellcheckerEntry()
    {
    }

    SpellcheckerEntry(std::string const &leader) : Leader(leader)
    {
    }

    std::string Leader;
    std::unordered_set<std::string> Values;
};

class Solution
{
public:
    std::vector<std::string> spellchecker(std::vector<std::string> const &wordlist, std::vector<std::string> const &queries) const
    {
        std::unordered_map<std::string, SpellcheckerEntry> spellcheckerMap;
        std::unordered_map<std::string, std::string> universalSpellcheckerMap;
        for (std::string const &word : wordlist)
        {
            std::string key(generateKey(word));
            if (spellcheckerMap.count(key) == 0)
                spellcheckerMap.emplace(key, SpellcheckerEntry(word));
            spellcheckerMap[key].Values.emplace(word);
            std::string universalKey(generateUniversalKey(word));
            if (universalSpellcheckerMap.count(universalKey) == 0)
                universalSpellcheckerMap.emplace(universalKey, word);
        }
        std::vector<std::string> result;
        for (std::string const &query : queries)
        {
            auto keyResult = spellcheckerMap.find(generateKey(query));
            if (keyResult == spellcheckerMap.cend())
            {
                auto universalKeyResult = universalSpellcheckerMap.find(generateUniversalKey(query));
                result.push_back(universalKeyResult == universalSpellcheckerMap.cend() ? "" : universalKeyResult->second);
            }
            else
            {
                std::unordered_set<std::string> const &values = keyResult->second.Values;
                auto exactMatchResult = values.find(query);
                result.push_back(exactMatchResult == values.cend() ? keyResult->second.Leader : *exactMatchResult);
            }
        }
        return result;
    }

private:
    std::string generateKey(std::string const &word) const
    {
        std::string key(word.size(), ' ');
        std::transform(word.cbegin(), word.cend(), key.begin(), [](char ch){ return std::tolower(ch); });
        return key;
    }

    std::string generateUniversalKey(std::string const &word) const
    {
        std::string key(word.size(), '*');
        for (size_t index = 0; index < word.size(); ++index)
        {
            if (!isVowel(word[index]))
                key[index] = static_cast<char>(std::tolower(word[index]));
        }
        return key;
    }

    bool isVowel(char ch) const
    {
        return ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' || ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O' || ch == 'u' || ch == 'U';
    }
};

}

namespace VowelSpellcheckerTask
{

TEST(TVowelSpellcheckerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"kite", "KiTe", "KiTe", "Hare", "hare", "", "", "KiTe", "", "KiTe"}),
              solution.spellchecker({"KiTe", "kite", "hare", "Hare"}, {"kite", "Kite", "KiTe", "Hare", "HARE", "Hear", "hear", "keti", "keet", "keto"}));
    ASSERT_EQ(std::vector<std::string>({"yellow"}), solution.spellchecker({"yellow"}, {"YellOw"}));
}

}