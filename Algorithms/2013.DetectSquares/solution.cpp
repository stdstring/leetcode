#include <vector>

#include "gtest/gtest.h"

namespace
{

class DetectSquares
{
public:
    DetectSquares() = default;

    void add(std::vector<int> const &point)
    {
        int pointKey = calcPointKey(point[0], point[1]);
        auto iterator = _pointsMap.find(pointKey);
        if (iterator == _pointsMap.end())
            iterator = _pointsMap.emplace(pointKey, 0).first;
        ++iterator->second;
    }

    int count(std::vector<int> const &point)
    {
        const int startKey = calcPointKey(point[0], MinCoordValue);
        const int finishKey = calcPointKey(point[0] + 1, MinCoordValue);
        size_t count = 0;
        for (auto iterator = _pointsMap.lower_bound(startKey); (iterator != _pointsMap.cend()) && (iterator->first < finishKey); ++iterator)
        {
            std::vector<int> secondPoint(calcCoords(iterator->first));
            const int sideSize = std::abs(point[1] - secondPoint[1]);
            if (sideSize == 0)
                continue;
            if ((point[0] - sideSize) >= MinCoordValue)
            {
                const size_t thirdPointCount = getPointCount(calcPointKey(point[0] - sideSize, point[1]));
                const size_t fourthPointCount = getPointCount(calcPointKey(point[0] - sideSize, secondPoint[1]));
                count += (iterator->second) * thirdPointCount * fourthPointCount;
            }
            if ((point[0] + sideSize) <= MaxCoordValue)
            {
                const size_t thirdPointCount = getPointCount(calcPointKey(point[0] + sideSize, point[1]));
                const size_t fourthPointCount = getPointCount(calcPointKey(point[0] + sideSize, secondPoint[1]));
                count += (iterator->second) * thirdPointCount * fourthPointCount;
            }
        }
        return static_cast<int>(count);
    }

private:
    static constexpr int MaxCoordValue = 1000;
    static constexpr int MinCoordValue = 0;
    static constexpr int CoordBase = MaxCoordValue - MinCoordValue + 1;

    std::map<int, size_t> _pointsMap;

    [[nodiscard]] int calcPointKey(int x, int y) const
    {
        return CoordBase * (x - MinCoordValue) + (y - MinCoordValue);
    }

    [[nodiscard]] std::vector<int> calcCoords(int pointKey) const
    {
        return {pointKey / CoordBase, pointKey % CoordBase};
    }

    [[nodiscard]] size_t getPointCount(int pointKey) const
    {
        const auto iterator = _pointsMap.find(pointKey);
        return iterator == _pointsMap.end() ? 0 : iterator->second;
    }
};

}

namespace DetectSquaresTask
{

TEST(DetectSquaresTaskTests, Examples)
{
    DetectSquares detector;
    ASSERT_NO_THROW(detector.add({3, 10}));
    ASSERT_NO_THROW(detector.add({11, 2}));
    ASSERT_NO_THROW(detector.add({3, 2}));
    ASSERT_EQ(1, detector.count({11, 10}));
    ASSERT_EQ(0, detector.count({14, 8}));
    ASSERT_NO_THROW(detector.add({11, 2}));
    ASSERT_EQ(2, detector.count({11, 10}));
}

}