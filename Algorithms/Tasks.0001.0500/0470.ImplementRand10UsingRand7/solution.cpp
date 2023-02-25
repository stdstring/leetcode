#include <random>

#include "gtest/gtest.h"

namespace
{

int rand7()
{
    std::mt19937 generator = std::mt19937(std::random_device()());
    std::uniform_int_distribution<> distribution(1, 7);
    return distribution(generator);
}

class Solution
{
public:
    int rand10()
    {
        int randomNumber;
        do
        {
            randomNumber = 7 * (rand7() - 1) + rand7();
        } while (randomNumber > 40);
        return (randomNumber % 10) + 1;
    }
};

}

namespace
{

bool contains(std::vector<int> const &sourceValues, int value)
{
    return std::find(sourceValues.cbegin(), sourceValues.cend(), value) != sourceValues.cend();
}

void checkRand10(size_t callCount)
{
    Solution solution;
    // TODO (std_string) : think about check for uniform distribution
    for (size_t callIndex = 0; callIndex < callCount; ++callIndex)
        ASSERT_EQ(true, contains({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, solution.rand10()));
}

}

namespace ImplementRand10UsingRand7Task
{

TEST(ImplementRand10UsingRand7TaskTests, Examples)
{
    checkRand10(1);
    checkRand10(2);
    checkRand10(3);
}

TEST(ImplementRand10UsingRand7TaskTests, FromWrongAnswers)
{
    checkRand10(10);
    checkRand10(100);
}

}