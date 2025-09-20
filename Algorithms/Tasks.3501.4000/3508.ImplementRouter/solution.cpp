#include <algorithm>
#include <deque>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Router
{
public:
    Router(int memoryLimit) : _memoryLimit(memoryLimit)
    {
    }

    bool addPacket(int source, int destination, int timestamp)
    {
        if (timestamp > _lastTimestamp)
        {
            _lastTimestamp = timestamp;
            _timestampPackets.clear();
        }
        long long packetId = calcPacketId(source, destination);
        if (_timestampPackets.contains(packetId))
            return false;
        _packets.emplace(source, destination, timestamp);
        _timestampPackets.insert(packetId);
        _destinationPacketData[destination].emplace_back(timestamp);
        if (_packets.size() > _memoryLimit)
            removeFirstPacket();
        return true;
    }

    std::vector<int> forwardPacket()
    {
        if (_packets.empty())
            return {};
        Packet firstPacket(_packets.front());
        removeFirstPacket();
        return {firstPacket.Source, firstPacket.Destination, firstPacket.Timestamp};
    }

    int getCount(int destination, int startTime, int endTime)
    {
        auto leftBound = std::ranges::upper_bound(_destinationPacketData[destination], startTime - 1);
        auto rightBound = std::ranges::upper_bound(_destinationPacketData[destination], endTime);
        return static_cast<int>(std::distance(leftBound, rightBound));
    }

private:
    struct Packet
    {
        Packet(int source, int destination, int timestamp)
            : Source(source)
            , Destination(destination)
            , Timestamp(timestamp)
        {
        }

        int Source;
        int Destination;
        int Timestamp;
    };

    [[nodiscard]] long long calcPacketId(int source, int destination) const
    {
        return 1LL * source * INT_MAX + destination;
    }

    void removeFirstPacket()
    {
        Packet firstPacket(_packets.front());
        if (firstPacket.Timestamp == _lastTimestamp)
        {
            long long firstPacketId = calcPacketId(firstPacket.Source, firstPacket.Destination);
            _timestampPackets.erase(firstPacketId);
        }
        _destinationPacketData[firstPacket.Destination].pop_front();
        _packets.pop();
    }

    size_t _memoryLimit;
    int _lastTimestamp = 0;
    std::queue<Packet> _packets;
    std::unordered_set<long long> _timestampPackets;
    std::unordered_map<int, std::deque<int>> _destinationPacketData;
};

}

namespace
{

struct AddPacketCall
{
    AddPacketCall(int source, int destination, int timestamp, bool expectedValue)
        : Source(source)
        , Destination(destination)
        , Timestamp(timestamp)
        , ExpectedValue(expectedValue)
    {
    }

    int Source;
    int Destination;
    int Timestamp;
    bool ExpectedValue;
};

struct ForwardPacketCall
{
    explicit ForwardPacketCall(std::vector<int> const &expectedValue) : ExpectedValue(expectedValue)
    {
    }

    std::vector<int> ExpectedValue;
};

struct GetCountCall
{
    GetCountCall(int destination, int startTime, int endTime, int expectedValue)
        : Destination(destination)
        , StartTime(startTime)
        , EndTime(endTime)
        , ExpectedValue(expectedValue)
    {
    }

    int Destination;
    int StartTime;
    int EndTime;
    int ExpectedValue;
};

typedef std::variant<AddPacketCall, ForwardPacketCall, GetCountCall> TCallVariant;

void checkRouter(int memoryLimit, std::vector<TCallVariant> const &calls)
{
    Router router(memoryLimit);
    for (TCallVariant const &call : calls)
    {
        if (const AddPacketCall* addPacketCall = std::get_if<AddPacketCall>(&call))
            ASSERT_EQ(addPacketCall->ExpectedValue, router.addPacket(addPacketCall->Source, addPacketCall->Destination, addPacketCall->Timestamp));
        if (const ForwardPacketCall* forwardPacketCall = std::get_if<ForwardPacketCall>(&call))
            ASSERT_EQ(forwardPacketCall->ExpectedValue, router.forwardPacket());
        if (const GetCountCall* getCountCall = std::get_if<GetCountCall>(&call))
            ASSERT_EQ(getCountCall->ExpectedValue, router.getCount(getCountCall->Destination, getCountCall->StartTime, getCountCall->EndTime));
    }
}

}

namespace ImplementRouterTask
{

TEST(ImplementRouterTaskTests, Examples)
{
    checkRouter(3, {AddPacketCall(1, 4, 90, true),
                    AddPacketCall(2, 5, 90, true),
                    AddPacketCall(1, 4, 90, false),
                    AddPacketCall(3, 5, 95, true),
                    AddPacketCall(4, 5, 105, true),
                    ForwardPacketCall({2, 5, 90}),
                    AddPacketCall(5, 2, 110, true),
                    GetCountCall(5, 100, 110, 1)});
    checkRouter(2, {AddPacketCall(7, 4, 90, true), ForwardPacketCall({7, 4, 90}), ForwardPacketCall({})});
}

}