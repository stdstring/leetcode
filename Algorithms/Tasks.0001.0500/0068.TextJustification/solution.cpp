#include <string>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct PortionData
{
    PortionData(size_t portionCount, size_t portionSize) : PortionCount(portionCount), PortionSize(portionSize)
    {
    }

    size_t PortionCount;
    size_t PortionSize;
};

class Solution
{
public:
    std::vector<std::string> fullJustify(std::vector<std::string> const &words, int maxWidth) const
    {
        std::vector<std::string> dest;
        size_t index = 0;
        const size_t maxSize = static_cast<size_t>(maxWidth);
        while (index < words.size())
        {
            const PortionData portionData(calcWordsPortionSize(words, maxSize, index));
            if ((index + portionData.PortionCount) == words.size())
                dest.push_back(buildLastLine(words, maxSize, index, portionData.PortionSize));
            else
                dest.push_back(buildLine(words, maxSize, index, portionData.PortionCount, portionData.PortionSize));
            index += portionData.PortionCount;
        }
        return dest;
    }

private:
    PortionData calcWordsPortionSize(std::vector<std::string> const &words, size_t maxSize, size_t index) const
    {
        size_t portionCount = 1;
        size_t portionSize = words[index++].size();
        while (index < words.size() && (portionSize + portionCount + words[index].size()) <= maxSize)
        {
            portionSize += words[index].size();
            ++portionCount;
            ++index;
        }
        return PortionData(portionCount, portionSize);
    }

    std::string buildLine(std::vector<std::string> const &words, size_t maxSize, size_t start, size_t count, size_t size) const
    {
        std::string dest;
        const size_t spacesCount = maxSize - size;
        if (count == 1)
        {
            dest.append(words[start]);
            generateSpaces(dest, spacesCount);
        }
        else
        {
            const size_t spacesPortionSize = spacesCount / (count - 1);
            size_t spacesPortionRest = spacesCount % (count - 1);
            dest.append(words[start]);
            for (size_t index = 1; index < count; ++index)
            {
                generateSpaces(dest, spacesPortionSize + (spacesPortionRest > 0 ? 1 : 0));
                dest.append(words[start + index]);
                if (spacesPortionRest > 0)
                    --spacesPortionRest;
            }
        }
        return dest;
    }

    std::string buildLastLine(std::vector<std::string> const &words, size_t maxSize, size_t start, size_t size) const
    {
        const size_t count = words.size() - start;
        std::string dest;
        dest.append(words[start]);
        for (size_t index = start + 1; index < words.size(); ++index)
        {
            dest.push_back(' ');
            dest.append(words[index]);
        }
        generateSpaces(dest, maxSize - size - (count - 1));
        return dest;
    }

    void generateSpaces(std::string &dest, size_t count) const
    {
        for (size_t index = 0; index < count; ++index)
            dest.push_back(' ');
    }
};

}

namespace TextJustificationTask
{

TEST(TextJustificationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"This    is    an", "example  of text", "justification.  "}), solution.fullJustify({"This", "is", "an", "example", "of", "text", "justification."}, 16));
    ASSERT_EQ(std::vector<std::string>({"What   must   be", "acknowledgment  ", "shall be        "}), solution.fullJustify({"What","must","be","acknowledgment","shall","be"}, 16));
    ASSERT_EQ(std::vector<std::string>({"Science  is  what we", "understand      well", "enough to explain to", "a  computer.  Art is", "everything  else  we", "do                  "}),
              solution.fullJustify({"Science","is","what","we","understand","well","enough","to","explain", "to","a","computer.","Art","is","everything","else","we","do"}, 20));
}

}