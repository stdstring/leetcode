#include <string>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    // Anyone can see the following:
    // 1. When presses = 0, then we have only one (init) state
    // 2. When n = 1, then there are only 2 states: "1" & "0"
    // 3a. When n = 2 & presses = 1, there are 3 states (from init state): b1, b2, b3 (here b means button)
    // 3b. When n = 2 & presses = 2, there are 4 states (from init state): b1-b1, b1-b2, b1-b3, b2-b3 (here b means button)
    // ...
    // 4a. When n = 3 & presses = 1, there are 4 states (from init state): b1, b2, b3, b4 (here b means button)
    // 4b. When n = 3 & presses = 2, there are 7 states (from init state): b1-b1, b1-b2, b1-b3, b1-b4, b2-b3, b2-b4, b3-b4 (here b means button)
    // 4c. When n = 3 & presses = 3, there are 8 states (from init state): b1-b1-b1, b1-b1-b2, b1-b1-b3, b1-b1-b4, b1-b2-b3, b1-b2-b4, b1-b3-b4, b2-b3-b4 (here b means button)
    // ...
    [[nodiscard]] int flipLightsMath(int n, int presses) const
    {
        if (presses == 0)
            return 1;
        if (n == 1)
            return 2;
        if (n == 2)
            return presses > 1 ? 4 : 3;
        // n >= 3
        if (presses == 1)
            return 4;
        return presses == 2 ? 7 : 8;
    }

    [[nodiscard]] int flipLightsBFS(int n, int presses) const
    {
        const std::string start(n, LightOn);
        std::unordered_set<std::string> states({start});
        for (size_t pressIndex = 0; pressIndex < static_cast<size_t>(presses); ++pressIndex)
        {
            std::unordered_set<std::string> nextStates;
            for (std::string const &state : states)
            {
                nextStates.insert(pressButton1(state));
                nextStates.insert(pressButton2(state));
                nextStates.insert(pressButton3(state));
                nextStates.insert(pressButton4(state));
            }
            std::swap(states, nextStates);
        }
        return static_cast<int>(states.size());
    }

private:
    static constexpr char LightOn = '1';
    static constexpr char LightOff = '0';

    void flipLight(std::string &state, size_t index) const
    {
        state[index] = state[index] == LightOn ? LightOff : LightOn;
    }

    // Flips the status of all the bulbs.
    [[nodiscard]] std::string pressButton1(std::string const &source) const
    {
        std::string result(source);
        for (size_t index = 1; index <= result.size(); ++index)
            flipLight(result, index - 1);
        return result;
    }

    // Flips the status of all the bulbs with even labels (i.e., 2, 4, ...).
    [[nodiscard]] std::string pressButton2(std::string const &source) const
    {
        std::string result(source);
        for (size_t index = 2; index <= result.size(); index += 2)
            flipLight(result, index - 1);
        return result;
    }

    // Flips the status of all the bulbs with odd labels (i.e., 1, 3, ...).
    [[nodiscard]] std::string pressButton3(std::string const &source) const
    {
        std::string result(source);
        for (size_t index = 1; index <= result.size(); index += 2)
            flipLight(result, index - 1);
        return result;
    }

    // Flips the status of all the bulbs with a label j = 3k + 1 where k = 0, 1, 2, ... (i.e., 1, 4, 7, 10, ...).
    [[nodiscard]] std::string pressButton4(std::string const &source) const
    {
        std::string result(source);
        for (size_t index = 1; index <= result.size(); index += 3)
            flipLight(result, index - 1);
        return result;
    }
};

}

namespace
{

void checkFlipLights(int n, int presses, int expectedStatusesCount)
{
    const Solution solution;
    ASSERT_EQ(expectedStatusesCount, solution.flipLightsMath(n, presses));
    ASSERT_EQ(expectedStatusesCount, solution.flipLightsBFS(n, presses));
}

}

namespace BulbSwitcherIITask
{

TEST(BulbSwitcherIITaskTests, Examples)
{
    checkFlipLights(1, 1, 2);
    checkFlipLights(2, 1, 3);
    checkFlipLights(3, 1, 4);
    checkFlipLights(1, 0, 1);
    checkFlipLights(1, 2, 2);
}

}
