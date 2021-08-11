#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct LogEntry
{
    LogEntry(std::string const &id, std::string const &body) : Id(id), Body(body)
    {
    }

    std::string Id;
    std::string Body;
};

class Solution
{
public:
    std::vector<std::string> reorderLogFiles(std::vector<std::string> const &logs) const
    {
        std::vector<LogEntry> letterLogs;
        std::vector<LogEntry> digitLogs;
        for (std::string const &log : logs)
        {
            const size_t delimiterPos = log.find(' ');
            std::string id(log.substr(0, delimiterPos));
            std::string body(log.substr(delimiterPos + 1));
            if (std::isdigit(body.front()))
                digitLogs.emplace_back(id, body);
            else
                letterLogs.emplace_back(id, body);
        }
        std::sort(letterLogs.begin(), letterLogs.end(), [](LogEntry const &left, LogEntry const &right){ return (left.Body < right.Body) || (left.Body == right.Body && left.Id < right.Id); });
        std::vector<std::string> result;
        result.reserve(letterLogs.size() + digitLogs.size());
        for (LogEntry const &entry : letterLogs)
            result.push_back(entry.Id + " " + entry.Body);
        for (LogEntry const &entry : digitLogs)
            result.push_back(entry.Id + " " + entry.Body);
        return result;
    }
};

}

namespace ReorderDataInLogFilesTask
{

TEST(ReorderDataInLogFilesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"let1 art can", "let3 art zero", "let2 own kit dig", "dig1 8 1 5 1","dig2 3 6"}),
              solution.reorderLogFiles({"dig1 8 1 5 1", "let1 art can","dig2 3 6", "let2 own kit dig", "let3 art zero"}));
    ASSERT_EQ(std::vector<std::string>({"g1 act car", "a8 act zoo", "ab1 off key dog", "a1 9 2 3 1", "zo4 4 7"}),
              solution.reorderLogFiles({"a1 9 2 3 1", "g1 act car", "zo4 4 7", "ab1 off key dog", "a8 act zoo"}));
}

}