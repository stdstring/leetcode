#include <iterator>
#include <map>

#include "gtest/gtest.h"

namespace
{

class LUPrefix
{
public:
    LUPrefix(int n) : _count(n)
    {
    }

    void upload(int video)
    {
        const auto iterator = _storage.upper_bound(video);
        const int nextVideo = iterator == _storage.end() ? _count + 2 : iterator->first;
        auto prevIterator = iterator;
        int prevVideo = -1;
        if (iterator != _storage.begin())
        {
            prevIterator = std::prev(iterator, 1);
            prevVideo = prevIterator->first + prevIterator->second - 1;
        }
        int videoRangeSize = 1;
        if ((video + 1) == nextVideo)
        {
            videoRangeSize += iterator->second;
            _storage.erase(iterator);
        }
        if ((prevVideo + 1) == video)
            prevIterator->second += videoRangeSize;
        else
            _storage.emplace(video, videoRangeSize);
    }

    int longest()
    {
        const auto iterator = _storage.cbegin();
        return (iterator == _storage.cend()) || iterator->first > 1 ? 0 : iterator->second;
    }

private:
    std::map<int, int> _storage;
    int _count;
};

}

namespace LongestUploadedPrefixTask
{

TEST(LongestUploadedPrefixTaskTests, Examples)
{
    LUPrefix luPrefix(4);
    ASSERT_NO_THROW(luPrefix.upload(3));
    ASSERT_EQ(0, luPrefix.longest());
    ASSERT_NO_THROW(luPrefix.upload(1));
    ASSERT_EQ(1, luPrefix.longest());
    ASSERT_NO_THROW(luPrefix.upload(2));
    ASSERT_EQ(3, luPrefix.longest());
}

TEST(LongestUploadedPrefixTaskTests, CustomExamples)
{
    LUPrefix luPrefix(4);
    ASSERT_NO_THROW(luPrefix.upload(3));
    ASSERT_EQ(0, luPrefix.longest());
    ASSERT_NO_THROW(luPrefix.upload(2));
    ASSERT_EQ(0, luPrefix.longest());
    ASSERT_NO_THROW(luPrefix.upload(1));
    ASSERT_EQ(3, luPrefix.longest());
}

}