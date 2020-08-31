#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> restoreIpAddresses(std::string const &s)
    {
        std::array<size_t, 4> positions{};
        positions[0] = 0;
        std::vector<std::string> dest;
        processImpl(s, dest, positions, 1);
        return dest;
    }

private:
    void processImpl(std::string const &source, std::vector<std::string> &dest, std::array<size_t, 4> &positions, int part)
    {
        if (part == 4)
        {
            const size_t lastSize = source.size() - positions[3];
            if (lastSize > 3)
                return;
            tryAppendIpAddress(source, dest, positions);
        }
        else
        {
            for(size_t size = 1; size <= 3; ++size)
            {
                const size_t position = positions[part - 1] + size;
                if (position >= source.size())
                    return;
                positions[part] = position;
                processImpl(source, dest, positions, part + 1);
            }
        }
    }

    int createNumber(std::string const &source, size_t start, size_t end)
    {
        int result = 0;
        for (size_t pos = start; pos <= end; ++pos)
            result = result * 10 + (source[pos] - '0');
        return result;
    }

    void tryAppendIpAddress(std::string const &source, std::vector<std::string> &dest, std::array<size_t, 4> &positions)
    {
        const int maxValue = 255;
        if (source[positions[0]] == '0' && (positions[1] - positions[0]) > 1)
            return;
        if (source[positions[1]] == '0' && (positions[2] - positions[1]) > 1)
            return;
        if (source[positions[2]] == '0' && (positions[3] - positions[2]) > 1)
            return;
        if (source[positions[3]] == '0' && (source.size() - positions[3]) > 1)
            return;
        if (createNumber(source, positions[0], positions[1] - 1) > maxValue)
            return;
        if (createNumber(source, positions[1], positions[2] - 1) > maxValue)
            return;
        if (createNumber(source, positions[2], positions[3] - 1) > maxValue)
            return;
        if (createNumber(source, positions[3], source.size() - 1) > maxValue)
            return;
        dest.push_back(source.substr(positions[0], positions[1] - positions[0]) + "." +
                       source.substr(positions[1], positions[2] - positions[1]) + "." +
                       source.substr(positions[2], positions[3] - positions[2]) + "." +
                       source.substr(positions[3], source.size() - positions[3]));
    }
};

}

namespace RestoreIPAddressesTask
{

TEST(RestoreIPAddressesTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ(std::vector<std::string>({"255.255.11.135", "255.255.111.35"}), solution.restoreIpAddresses("25525511135"));
}

TEST(RestoreIPAddressesTaskTests, FromWrongAnswers)
{
    Solution solution;
    ASSERT_EQ(std::vector<std::string>({"0.10.0.10","0.100.1.0"}), solution.restoreIpAddresses("010010"));
}

}