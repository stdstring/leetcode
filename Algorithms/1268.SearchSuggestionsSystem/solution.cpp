#include <cstdlib>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<std::string>> suggestedProducts(std::vector<std::string> const &products, std::string const &searchWord) const
    {
        std::vector<std::vector<int>> trie(1, std::vector<int>(AlphabetSize, 0));
        generateTrie(trie, products);
        std::vector<std::vector<std::string>> result;
        size_t currentNode = 0;
        std::string currentPrefix;
        for (const char ch : searchWord)
        {
            if (currentNode == trie.size() || trie[currentNode][ch - AlphabetStart] == 0)
            {
                currentNode = trie.size();
                result.emplace_back();
                continue;
            }
            currentPrefix.push_back(ch);
            std::vector<std::string> currentProducts;
            if (trie[currentNode][ch - AlphabetStart] == EndOfWordNode)
            {
                currentProducts.push_back(currentPrefix);
                currentNode = trie.size();
            }
            else
            {
                if (trie[currentNode][ch - AlphabetStart] < 0)
                    currentProducts.push_back(currentPrefix);
                currentNode = std::abs(trie[currentNode][ch - AlphabetStart]);
                findBestProducts(trie, currentNode, currentPrefix, currentProducts);
            }
            result.push_back(currentProducts);
        }
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t MaxBestProductSize = 3;
    static constexpr int EndOfWordNode = INT_MIN;

    void generateTrie(std::vector<std::vector<int>> &trie, std::vector<std::string> const &products) const
    {
        for (std::string const& product : products)
        {
            size_t currentNode = 0;
            // process chars
            for (size_t index = 0; index < product.size() - 1; ++index)
            {
                const char currentChar = product[index];
                int nextNode = trie[currentNode][currentChar - AlphabetStart];
                if (nextNode == 0)
                {
                    trie[currentNode][currentChar - AlphabetStart] = nextNode = static_cast<int>(trie.size());
                    trie.emplace_back(AlphabetSize, 0);
                }
                if (nextNode == EndOfWordNode)
                {
                    nextNode = static_cast<int>(trie.size());
                    trie[currentNode][currentChar - AlphabetStart] = -nextNode;
                    trie.emplace_back(AlphabetSize, 0);
                }
                currentNode = std::abs(nextNode);
            }
            // process last char
            const char lastChar = product.back();
            trie[currentNode][lastChar - AlphabetStart] = trie[currentNode][lastChar - AlphabetStart] == 0 ? EndOfWordNode : -trie[currentNode][lastChar - AlphabetStart];
        }
    }

    void findBestProducts(std::vector<std::vector<int>> const &trie, size_t currentNode, std::string &currentProduct, std::vector<std::string> &bestProducts) const
    {
        for (size_t index = 0; index < AlphabetSize && bestProducts.size() < MaxBestProductSize; ++index)
        {
            if (trie[currentNode][index] == 0)
                continue;
            currentProduct.push_back(static_cast<char>(AlphabetStart + index));
            if  (trie[currentNode][index] > 0)
                findBestProducts(trie, trie[currentNode][index], currentProduct, bestProducts);
            if  (trie[currentNode][index] < 0)
            {
                bestProducts.push_back(currentProduct);
                if (trie[currentNode][index] != EndOfWordNode)
                    findBestProducts(trie, std::abs(trie[currentNode][index]), currentProduct, bestProducts);
            }
            currentProduct.pop_back();
        }
    }
};

}

namespace SearchSuggestionsSystemTask
{

TEST(SearchSuggestionsSystemTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"mobile", "moneypot", "monitor"}, {"mobile", "moneypot", "monitor"}, {"mouse", "mousepad"}, {"mouse", "mousepad"}, {"mouse", "mousepad"}}),
              solution.suggestedProducts({"mobile", "mouse", "moneypot", "monitor", "mousepad"}, "mouse"));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}}), solution.suggestedProducts({"havana"}, "havana"));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"baggage", "bags", "banner"}, {"baggage", "bags", "banner"}, {"baggage", "bags"}, {"bags"}}),
              solution.suggestedProducts({"bags", "baggage", "banner", "box", "cloths"}, "bags"));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{}, {}, {}, {}, {}, {}, {}}), solution.suggestedProducts({"havana"}, "tatiana"));
}

}