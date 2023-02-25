#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> splitMessage(std::string const &message, int limit) const
    {
        const std::optional<size_t> portionCount = calcPortionCount(message.size(), limit);
        if (!portionCount.has_value())
            return {};
        std::vector<std::string> result;
        for (size_t portion = 1, index = 0; portion <= portionCount; ++portion)
        {
            std::stringstream servicePartStream;
            servicePartStream << "<" << portion << "/" << portionCount.value() << ">";
            std::string servicePart(servicePartStream.str());
            result.push_back(message.substr(index, limit - servicePart.size()).append(servicePart));
            index += (limit - servicePart.size());
        }
        return result;
    }

private:
    [[nodiscard]] std::optional<size_t> calcPortionCount(size_t messageSize, size_t limit) const
    {
        size_t rangeStart = 1;
        size_t rangeEnd = 10 * rangeStart - 1;
        // '<' - 1 char, '/' - 1 char, '>' 1 char + 1 char for total number, 1 char for index
        size_t servicePart = 5;
        size_t portionCount = 0;
        while (messageSize > 0)
        {
            if (servicePart >= limit)
                return {};
            const size_t rangePortionCount = rangeEnd - rangeStart + 1;
            const size_t rangeTotalSize = rangePortionCount * (limit - servicePart);
            if (rangeTotalSize >= messageSize)
            {
                portionCount += (messageSize / (limit - servicePart) + (messageSize % (limit - servicePart) == 0 ? 0 : 1));
                messageSize = 0;
            }
            else
            {
                messageSize -= rangeTotalSize;
                portionCount += rangePortionCount;
                // increase service part by 2
                messageSize += rangeEnd;
                rangeStart *= 10;
                rangeEnd = 10 * rangeStart - 1;
                servicePart += 2;
            }
        }
        return portionCount;
    }
};

}

namespace SplitMessageBasedOnLimitTask
{

TEST(SplitMessageBasedOnLimitTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"thi<1/14>",
                                        "s i<2/14>",
                                        "s r<3/14>",
                                        "eal<4/14>",
                                        "ly <5/14>",
                                        "a v<6/14>",
                                        "ery<7/14>",
                                        " aw<8/14>",
                                        "eso<9/14>",
                                        "me<10/14>",
                                        " m<11/14>",
                                        "es<12/14>",
                                        "sa<13/14>",
                                        "ge<14/14>"}),
              solution.splitMessage("this is really a very awesome message", 9));
    ASSERT_EQ(std::vector<std::string>({"short mess<1/2>", "age<2/2>"}),
              solution.splitMessage("short message", 15));
}

}