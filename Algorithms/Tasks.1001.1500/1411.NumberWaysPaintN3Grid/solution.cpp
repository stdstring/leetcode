#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfWays(int n) const
    {
        constexpr int modValue = 1000000007;
        // cases
        constexpr size_t ryr = 0;
        constexpr size_t yry = 1;
        constexpr size_t rgr = 2;
        constexpr size_t grg = 3;
        constexpr size_t ygy = 4;
        constexpr size_t gyg = 5;
        constexpr size_t ryg = 6;
        constexpr size_t rgy = 7;
        constexpr size_t yrg = 8;
        constexpr size_t ygr = 9;
        constexpr size_t gry = 10;
        constexpr size_t gyr = 11;
        constexpr size_t casesCount = 12;
        std::vector<int> prevStep(casesCount, 1);
        std::vector<int> currentStep(casesCount, 0);
        for (int step = 2; step <= n; ++step)
        {
            for (size_t index = 0; index < casesCount; ++index)
                currentStep[index] = 0;
            // ryr -> yry, grg, ygy, yrg, gry
            currentStep[yry] = (currentStep[yry] + prevStep[ryr]) % modValue;
            currentStep[grg] = (currentStep[grg] + prevStep[ryr]) % modValue;
            currentStep[ygy] = (currentStep[ygy] + prevStep[ryr]) % modValue;
            currentStep[yrg] = (currentStep[yrg] + prevStep[ryr]) % modValue;
            currentStep[gry] = (currentStep[gry] + prevStep[ryr]) % modValue;
            // yry -> ryr, rgr, gyg, ryg, gyr
            currentStep[ryr] = (currentStep[ryr] + prevStep[yry]) % modValue;
            currentStep[rgr] = (currentStep[rgr] + prevStep[yry]) % modValue;
            currentStep[gyg] = (currentStep[gyg] + prevStep[yry]) % modValue;
            currentStep[ryg] = (currentStep[ryg] + prevStep[yry]) % modValue;
            currentStep[gyr] = (currentStep[gyr] + prevStep[yry]) % modValue;
            // rgr -> yry, grg, gyg, yrg, gry
            currentStep[yry] = (currentStep[yry] + prevStep[rgr]) % modValue;
            currentStep[grg] = (currentStep[grg] + prevStep[rgr]) % modValue;
            currentStep[gyg] = (currentStep[gyg] + prevStep[rgr]) % modValue;
            currentStep[yrg] = (currentStep[yrg] + prevStep[rgr]) % modValue;
            currentStep[gry] = (currentStep[gry] + prevStep[rgr]) % modValue;
            // grg -> ryr, rgr, ygy, rgy, ygr
            currentStep[ryr] = (currentStep[ryr] + prevStep[grg]) % modValue;
            currentStep[rgr] = (currentStep[rgr] + prevStep[grg]) % modValue;
            currentStep[ygy] = (currentStep[ygy] + prevStep[grg]) % modValue;
            currentStep[rgy] = (currentStep[rgy] + prevStep[grg]) % modValue;
            currentStep[ygr] = (currentStep[ygr] + prevStep[grg]) % modValue;
            // ygy -> ryr, grg, gyg, ryg, gyr
            currentStep[ryr] = (currentStep[ryr] + prevStep[ygy]) % modValue;
            currentStep[grg] = (currentStep[grg] + prevStep[ygy]) % modValue;
            currentStep[gyg] = (currentStep[gyg] + prevStep[ygy]) % modValue;
            currentStep[ryg] = (currentStep[ryg] + prevStep[ygy]) % modValue;
            currentStep[gyr] = (currentStep[gyr] + prevStep[ygy]) % modValue;
            // gyg -> yry, rgr, ygy, rgy, ygr
            currentStep[yry] = (currentStep[yry] + prevStep[gyg]) % modValue;
            currentStep[rgr] = (currentStep[rgr] + prevStep[gyg]) % modValue;
            currentStep[ygy] = (currentStep[ygy] + prevStep[gyg]) % modValue;
            currentStep[rgy] = (currentStep[rgy] + prevStep[gyg]) % modValue;
            currentStep[ygr] = (currentStep[ygr] + prevStep[gyg]) % modValue;
            // ryg -> yry, ygy, ygr, gry
            currentStep[yry] = (currentStep[yry] + prevStep[ryg]) % modValue;
            currentStep[ygy] = (currentStep[ygy] + prevStep[ryg]) % modValue;
            currentStep[ygr] = (currentStep[ygr] + prevStep[ryg]) % modValue;
            currentStep[gry] = (currentStep[gry] + prevStep[ryg]) % modValue;
            // rgy -> grg, gyg, yrg, gyr
            currentStep[grg] = (currentStep[grg] + prevStep[rgy]) % modValue;
            currentStep[gyg] = (currentStep[gyg] + prevStep[rgy]) % modValue;
            currentStep[yrg] = (currentStep[yrg] + prevStep[rgy]) % modValue;
            currentStep[gyr] = (currentStep[gyr] + prevStep[rgy]) % modValue;
            // yrg -> ryr, rgr, rgy, gyr
            currentStep[ryr] = (currentStep[ryr] + prevStep[yrg]) % modValue;
            currentStep[rgr] = (currentStep[rgr] + prevStep[yrg]) % modValue;
            currentStep[rgy] = (currentStep[rgy] + prevStep[yrg]) % modValue;
            currentStep[gyr] = (currentStep[gyr] + prevStep[yrg]) % modValue;
            // ygr -> grg, gyg, ryg, gry
            currentStep[grg] = (currentStep[grg] + prevStep[ygr]) % modValue;
            currentStep[gyg] = (currentStep[gyg] + prevStep[ygr]) % modValue;
            currentStep[ryg] = (currentStep[ryg] + prevStep[ygr]) % modValue;
            currentStep[gry] = (currentStep[gry] + prevStep[ygr]) % modValue;
            // gry -> ryr, rgr, ryg, ygr
            currentStep[ryr] = (currentStep[ryr] + prevStep[gry]) % modValue;
            currentStep[rgr] = (currentStep[rgr] + prevStep[gry]) % modValue;
            currentStep[ryg] = (currentStep[ryg] + prevStep[gry]) % modValue;
            currentStep[ygr] = (currentStep[ygr] + prevStep[gry]) % modValue;
            // gyr -> yry, ygy, rgy, yrg
            currentStep[yry] = (currentStep[yry] + prevStep[gyr]) % modValue;
            currentStep[ygy] = (currentStep[ygy] + prevStep[gyr]) % modValue;
            currentStep[rgy] = (currentStep[rgy] + prevStep[gyr]) % modValue;
            currentStep[yrg] = (currentStep[yrg] + prevStep[gyr]) % modValue;
            std::swap(prevStep, currentStep);
        }
        int result = 0;
        for (int caseValue : prevStep)
            result = (result + caseValue) % modValue;
        return result;
    }
};

}

namespace NumberWaysPaintN3GridTask
{

TEST(NumberWaysPaintN3GridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.numOfWays(1));
    ASSERT_EQ(30228214, solution.numOfWays(5000));
}

TEST(NumberWaysPaintN3GridTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(54, solution.numOfWays(2));
    ASSERT_EQ(246, solution.numOfWays(3));
}

}