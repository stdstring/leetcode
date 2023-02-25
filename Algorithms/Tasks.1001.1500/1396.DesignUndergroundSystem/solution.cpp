#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class UndergroundSystem
{
public:
    UndergroundSystem()
    {
    }

    void checkIn(int id, std::string const &stationName, int t)
    {
        if (_checkinMap.count(id) != 0)
            throw std::logic_error("Bad customer");
        _checkinMap.emplace(id, std::pair<std::string, int>(stationName, t));
    }

    void checkOut(int id, std::string const &stationName, int t)
    {
        const auto checkinEntry = _checkinMap.find(id);
        if (checkinEntry == _checkinMap.end())
            throw std::logic_error("Bad customer");
        std::string key(checkinEntry->second.first.append(1, Delimiter).append(stationName));
        auto travelEntry = _travelMap.find(key);
        if (travelEntry == _travelMap.end())
            travelEntry = _travelMap.emplace(key, std::pair<int, int>(0, 0)).first;
        travelEntry->second.first += (t - checkinEntry->second.second);
        ++travelEntry->second.second;
        _checkinMap.erase(checkinEntry);
    }

    double getAverageTime(std::string const &startStation, std::string const &endStation)
    {
        const std::string key(std::string(startStation).append(1, Delimiter).append(endStation));
        const auto entry = _travelMap.find(key);
        return entry == _travelMap.end() ? 0 : 1.0 * entry->second.first / entry->second.second;
    }

private:
    static constexpr char Delimiter = '-';
    std::unordered_map<int, std::pair<std::string, int>> _checkinMap;
    std::unordered_map<std::string, std::pair<int, int>> _travelMap;
};

}

namespace
{

struct CheckInCall
{
    CheckInCall(int id, std::string const &stationName, int time) : Id(id), StationName(stationName), Time(time)
    {
    }

    int Id;
    std::string StationName;
    int Time;
};

struct CheckOutCall
{
    CheckOutCall(int id, std::string const &stationName, int time) : Id(id), StationName(stationName), Time(time)
    {
    }

    int Id;
    std::string StationName;
    int Time;
};

struct GetAverageTimeCall
{
    GetAverageTimeCall(std::string const &startStation, std::string const &endStation, double expectedResult) :
        StartStation(startStation),
        EndStation(endStation),
        ExpectedResult(expectedResult)
    {
    }

    std::string StartStation;
    std::string EndStation;
    double ExpectedResult;
};

void checkUndergroundSystem(std::vector<std::variant<CheckInCall, CheckOutCall, GetAverageTimeCall>> const &calls)
{
    UndergroundSystem undergroundSystem;
    for (std::variant<CheckInCall, CheckOutCall, GetAverageTimeCall> const &call : calls)
    {
        if (const CheckInCall* checkInCall = std::get_if<CheckInCall>(&call))
            ASSERT_NO_THROW(undergroundSystem.checkIn(checkInCall->Id, checkInCall->StationName, checkInCall->Time));
        if (const CheckOutCall* checkOutCall = std::get_if<CheckOutCall>(&call))
            ASSERT_NO_THROW(undergroundSystem.checkOut(checkOutCall->Id, checkOutCall->StationName, checkOutCall->Time));
        if (const GetAverageTimeCall* getAverageTimeCall = std::get_if<GetAverageTimeCall>(&call))
            ASSERT_NEAR(getAverageTimeCall->ExpectedResult, undergroundSystem.getAverageTime(getAverageTimeCall->StartStation, getAverageTimeCall->EndStation), 0.00001);
    }
}

}

namespace DesignUndergroundSystemTask
{

TEST(DesignUndergroundSystemTaskTests, Examples)
{
    // Example 1
    checkUndergroundSystem({CheckInCall(45, "Leyton", 3),
                            CheckInCall(32, "Paradise", 8),
                            CheckInCall(27, "Leyton", 10),
                            CheckOutCall(45, "Waterloo", 15),
                            CheckOutCall(27, "Waterloo", 20),
                            CheckOutCall(32, "Cambridge", 22),
                            GetAverageTimeCall("Paradise", "Cambridge", 14.0),
                            GetAverageTimeCall("Leyton", "Waterloo", 11.0),
                            CheckInCall(10, "Leyton", 24),
                            GetAverageTimeCall("Leyton", "Waterloo", 11.0),
                            CheckOutCall(10, "Waterloo", 38),
                            GetAverageTimeCall("Leyton", "Waterloo", 12.0)});
    // Example 2
    checkUndergroundSystem({CheckInCall(10, "Leyton", 3),
                            CheckOutCall(10, "Paradise", 8),
                            GetAverageTimeCall("Leyton", "Paradise", 5.0),
                            CheckInCall(5, "Leyton", 10),
                            CheckOutCall(5, "Paradise", 16),
                            GetAverageTimeCall("Leyton", "Paradise", 5.5),
                            CheckInCall(2, "Leyton", 21),
                            CheckOutCall(2, "Paradise", 30),
                            GetAverageTimeCall("Leyton", "Paradise", 6.66667)});
}

}