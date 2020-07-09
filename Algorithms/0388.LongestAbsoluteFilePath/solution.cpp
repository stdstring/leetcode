#include <algorithm>
#include <stack>
#include <string>
#include <tuple>

#include "gtest/gtest.h"

namespace
{

struct DirData
{
    DirData(int totalSize, int level) : TotalSize(totalSize), Level(level)
    {
    }

    int TotalSize;
    int Level;
};

class Solution
{
public:
    int lengthLongestPath(std::string const &input) const
    {
        std::stack<DirData> dirStack;
        // add root
        dirStack.push(DirData(0, -1));
        size_t index = 0;
        int maxSize = 0;
        while (index < input.size())
        {
            const int level = readLevel(input, index);
            while (dirStack.top().Level >= level)
                dirStack.pop();
            int size = 0;
            bool isFile = false;
            std::tie(size, isFile) = readName(input, index);
            if (isFile)
                maxSize = std::max(maxSize, calcTotalSize(dirStack.top(), size));
            else
                dirStack.push(DirData(calcTotalSize(dirStack.top(), size), level));
            // read tail of name - '/n' char
            ++index;
        }
        return maxSize;
    }

private:
    int readLevel(std::string const &input, size_t &index) const
    {
        int level = 0;
        while (input[index] == '\t')
        {
            ++level;
            ++index;
        }
        return level;
    }

    std::tuple<int, bool> readName(std::string const &input, size_t &index) const
    {
        int size = 0;
        bool isFile = false;
        while (index < input.size() && input[index] != '\n')
        {
            ++size;
            if (input[index] == '.')
                isFile = true;
            ++index;
        }
        return std::make_tuple(size, isFile);
    }

    int calcTotalSize(DirData const &parent, int size) const
    {
        return parent.TotalSize == 0 ? size : parent.TotalSize + 1 + size;
    }
};

}

namespace LongestAbsoluteFilePathTask
{

TEST(LongestAbsoluteFilePathTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(20, solution.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"));
    ASSERT_EQ(32, solution.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"));
}

}