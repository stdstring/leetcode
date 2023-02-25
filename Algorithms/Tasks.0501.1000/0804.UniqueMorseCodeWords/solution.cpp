#include <string>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int uniqueMorseRepresentations(std::vector<std::string> const &words) const
    {
        std::unordered_set<std::string> transformations;
        for (std::string const &word : words)
            transformations.insert(convertWord(word));
        return static_cast<int>(transformations.size());
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr char const* MorseCode[AlphabetSize] = {".-",    // a
                                                            "-...",  // b
                                                            "-.-.",  // c
                                                            "-..",   // d
                                                            ".",     // e
                                                            "..-.",  // f
                                                            "--.",   // g
                                                            "....",  // h
                                                            "..",    // i
                                                            ".---",  // j
                                                            "-.-",   // k
                                                            ".-..",  // l
                                                            "--",    // m
                                                            "-.",    // n
                                                            "---",   // o
                                                            ".--.",  // p
                                                            "--.-",  // q
                                                            ".-.",   // r
                                                            "...",   // s
                                                            "-",     // t
                                                            "..-",   // u
                                                            "...-",  // v
                                                            ".--",   // w
                                                            "-..-",  // x
                                                            "-.--",  // y
                                                            "--.."}; // z

    std::string convertWord(std::string const &word) const
    {
        std::string dest;
        for (char letter : word)
            dest.append(MorseCode[letter - 'a']);
        return dest;
    }
};

}

namespace UniqueMorseCodeWordsTask
{

TEST(UniqueMorseCodeWordsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.uniqueMorseRepresentations({"gin", "zen", "gig", "msg"}));
}

}