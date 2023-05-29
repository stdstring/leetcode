#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class ParkingSystem
{
public:
    ParkingSystem(int big, int medium, int small) : _availablePlaces({{BigCar, big}, {MediumCar, medium}, {SmallCar, small}})
    {
    }

    bool addCar(int carType)
    {
        const auto iterator = _availablePlaces.find(carType);
        if ((iterator == _availablePlaces.end()) || (iterator->second == 0))
            return false;
        --iterator->second;
        return true;
    }

private:
    static constexpr int BigCar = 1;
    static constexpr int MediumCar = 2;
    static constexpr int SmallCar = 3;
    std::unordered_map<int, int> _availablePlaces;
};

}

namespace DesignParkingSystemTask
{

TEST(DesignParkingSystemTaskTests, Examples)
{
    ParkingSystem parkingSystem(1, 1, 0);
    ASSERT_EQ(true, parkingSystem.addCar(1));
    ASSERT_EQ(true, parkingSystem.addCar(2));
    ASSERT_EQ(false, parkingSystem.addCar(3));
    ASSERT_EQ(false, parkingSystem.addCar(1));
}

}