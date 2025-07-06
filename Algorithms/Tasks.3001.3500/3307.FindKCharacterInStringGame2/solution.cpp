#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] char kthCharacter(long long k, std::vector<int> const &operations) const
    {
        const long long charIndex = k - 1;
        std::vector<PartData> parts({PartData(0, 1, 1)});
        long long partSize = 2;
        for (int part = 2; charIndex >= (parts.back().Start + parts.back().Size); ++part)
        {
            PartData const &prevPart(parts.back());
            parts.emplace_back(prevPart.OperationIndex + 1, prevPart.Start + prevPart.Size, partSize);
            partSize <<= 1;
        }
        return findCharacter(operations, parts, charIndex);
    }

private:
    struct PartData
    {
        PartData(size_t operationIndex, long long start, long long size) : OperationIndex(operationIndex), Start(start), Size(size)
        {
        }
        size_t OperationIndex;
        long long Start;
        long long Size;
    };

    [[nodiscard]] PartData findPart(std::vector<PartData> const &parts, long long index) const
    {
        for (PartData const &part : parts)
        {
            if ((part.Start + part.Size) > index)
                return part;
        }
        throw std::logic_error("bad index");
    }

    [[nodiscard]] char findCharacter(std::vector<int> const &operations, std::vector<PartData> const &parts, long long index) const
    {
        if (index == 0)
            return 'a';
        const PartData currentPart(findPart(parts, index));
        const char prevChar = findCharacter(operations, parts, index - currentPart.Start);
        return operations[currentPart.OperationIndex] == 0 ? prevChar : static_cast<char>(prevChar == 'z' ? 'a' : prevChar + 1);
    }
};

}

namespace FindKCharacterInStringGame2Task
{

TEST(FindKCharacterInStringGame2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ('a', solution.kthCharacter(5, {0, 0, 0}));
    ASSERT_EQ('b', solution.kthCharacter(10, {0, 1, 0, 1}));
}

}