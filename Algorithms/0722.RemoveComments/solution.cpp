#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class ProcessMode { Usual, BlockComment };

class Solution
{
public:
    std::vector<std::string> removeComments(std::vector<std::string> const &source) const
    {
        std::vector<std::string> result;
        ProcessMode processMode = ProcessMode::Usual;
        std::string destLine;
        for (std::string const &sourceLine : source)
        {
            size_t sourceIndex = 0;
            while (sourceIndex < sourceLine.size())
            {
                switch (processMode)
                {
                    case ProcessMode::Usual:
                        processUsualMode(sourceLine, sourceIndex, processMode, destLine);
                        break;
                    case ProcessMode::BlockComment:
                        processBlockCommentMode(sourceLine, sourceIndex, processMode);
                        break;
                }
            }
            if (!destLine.empty() && (processMode == ProcessMode::Usual))
            {
                result.push_back(destLine);
                destLine.clear();
            }
        }
        if (!destLine.empty())
            result.push_back(destLine);
        return result;
    }

private:
    const std::string BlockCommentStart = "/*";
    const std::string BlockCommentEnd = "*/";
    const std::string LineCommentStart = "//";

    size_t findSubstring(std::string const &source, std::string const &substring, size_t initialPos) const
    {
        const size_t pos = source.find(substring, initialPos);
        return pos == std::string::npos ? source.size() : pos;
    }

    void processUsualMode(std::string const &sourceLine, size_t &sourceIndex, ProcessMode &processMode, std::string &destLine) const
    {
        const size_t blockCommentStart = sourceLine.find(BlockCommentStart, sourceIndex);
        const size_t lineCommentStart = sourceLine.find(LineCommentStart, sourceIndex);
        const size_t commentStart = std::min({sourceLine.size(), blockCommentStart, lineCommentStart});
        destLine.append(sourceLine.substr(sourceIndex, commentStart - sourceIndex));
        if ((commentStart == sourceLine.size()) || (commentStart == lineCommentStart))
            sourceIndex = sourceLine.size();
        else
        {
            sourceIndex = blockCommentStart + BlockCommentStart.size();
            processMode = ProcessMode::BlockComment;
        }
    }

    void processBlockCommentMode(std::string const &sourceLine, size_t &sourceIndex, ProcessMode &processMode) const
    {
        const size_t blockCommentEnd = findSubstring(sourceLine, BlockCommentEnd, sourceIndex);
        sourceIndex = blockCommentEnd + BlockCommentEnd.size();
        if (blockCommentEnd < sourceLine.size())
            processMode = ProcessMode::Usual;
    }
};

}

namespace RemoveCommentsTask
{

TEST(RemoveCommentsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"int main()", "{ ", "  ", "int a, b, c;", "a = b + c;", "}"}),
              solution.removeComments({"/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"}));
    ASSERT_EQ(std::vector<std::string>({"ab"}), solution.removeComments({"a/*comment", "line", "more_comment*/b"}));
}

}