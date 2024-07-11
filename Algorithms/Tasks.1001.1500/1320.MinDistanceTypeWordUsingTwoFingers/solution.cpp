#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDistance(std::string const &word) const
    {
        const std::vector<TCell> keyboard(generateKeyboard());
        constexpr int fingerPosCount = AlphabetSize + 1;
        constexpr int fingersPosCount = fingerPosCount * fingerPosCount;
        std::vector<int> currentState(fingersPosCount, INT_MAX);
        currentState[0] = 0;
        for (const char ch : word)
        {
            std::vector<int> nextState(fingersPosCount, INT_MAX);
            for (int fingersPosition = 0; fingersPosition < fingersPosCount; ++fingersPosition)
            {
                if (currentState[fingersPosition] == INT_MAX)
                    continue;
                const int firstFinger = fingersPosition / fingerPosCount;
                const int secondFinger = fingersPosition % fingerPosCount;
                const int currentCost = currentState[fingersPosition];
                // move first finger
                const int newFirstFingerPositions = (ch - AlphabetStart + 1) * fingerPosCount + secondFinger;
                const int newFirstFingerCost = calcMoveCost(firstFinger, ch, keyboard);
                nextState[newFirstFingerPositions] = std::min(nextState[newFirstFingerPositions], currentCost + newFirstFingerCost);
                // move second finger
                const int newSecondFingerPositions = firstFinger * fingerPosCount + (ch - AlphabetStart + 1);
                const int newSecondFingerCost = calcMoveCost(secondFinger, ch, keyboard);
                nextState[newSecondFingerPositions] = std::min(nextState[newSecondFingerPositions], currentCost + newSecondFingerCost);
            }
            std::swap(currentState, nextState);
        }
        return *std::ranges::min_element(currentState);
    }

private:
    typedef std::pair<int, int> TCell;

    static constexpr int AlphabetStart = 'A';
    static constexpr int AlphabetSize = 26;

    [[nodiscard]] std::vector<TCell> generateKeyboard() const
    {
        constexpr int keyboardColumnCount = 6;
        std::vector<TCell> keyboard(AlphabetSize);
        for (int row = 0, column = 0, letter = 0; letter < AlphabetSize; ++letter)
        {
            if (column == keyboardColumnCount)
            {
                ++row;
                column = 0;
            }
            keyboard[letter] = TCell(row, column++);
        }
        return keyboard;
    }

    [[nodiscard]] int calcMoveCost(int currentFinger, char currentCh, std::vector<TCell> const &keyboard) const
    {
        if (currentFinger == 0)
            return 0;
        const int currentLetter = currentCh - AlphabetStart;
        const int currentFingerLetter = currentFinger - 1;
        return std::abs(keyboard[currentFingerLetter].first - keyboard[currentLetter].first) +
               std::abs(keyboard[currentFingerLetter].second - keyboard[currentLetter].second);
    }
};

}

namespace MinDistanceTypeWordUsingTwoFingersTask
{

TEST(MinDistanceTypeWordUsingTwoFingersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumDistance("CAKE"));
    ASSERT_EQ(6, solution.minimumDistance("HAPPY"));
}

}