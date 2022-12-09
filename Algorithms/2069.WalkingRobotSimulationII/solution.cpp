#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Robot
{
public:
    Robot(int width, int height) : _width(width), _height(height), _pos(0), _init(true)
    {
    }

    void step(int num)
    {
        const int totalSize = 2 * (_width + _height) - 4;
        _pos = (_pos + num) % totalSize;
        _init = false;
    }

    [[nodiscard]] std::vector<int> getPos() const
    {
        int current = _pos;
        if (current < _width)
            return {current, 0};
        current -= (_width - 1);
        if (current < _height)
            return {_width - 1, current};
        current -= (_height - 1);
        if (current < _width)
            return {_width - 1 - current, _height - 1};
        current -= (_width - 1);
        return {0, _height - 1 - current};
    }

    [[nodiscard]] std::string getDir() const
    {
        if (_pos == 0)
            return _init ? "East" : "South";
        if (_pos < _width)
            return "East";
        if (_pos < (_width + _height - 1))
            return "North";
        if (_pos < (2 * _width + _height - 2))
            return "West";
        return "South";
    }

private:
    int _width;
    int _height;
    int _pos;
    bool _init;
};

}

namespace
{

struct StepCall
{
    StepCall(int number) : Number(number)
    {
    }

    int Number;
};

struct GetPosCall
{
    GetPosCall(int x, int y) : ExpectedResult({x, y})
    {
    }

    std::vector<int> ExpectedResult;
};

struct GetDirCall
{
    GetDirCall(std::string const &expectedResult) : ExpectedResult(expectedResult)
    {
    }

    std::string ExpectedResult;
};

typedef std::variant<StepCall, GetPosCall, GetDirCall> TCall;

void checkRobot(int width, int height, std::vector<TCall> const &calls)
{
    Robot robot(width, height);
    for (TCall const &call : calls)
    {
        if (const StepCall* stepCall = std::get_if<StepCall>(&call))
            ASSERT_NO_THROW(robot.step(stepCall->Number));
        if (const GetPosCall* getPosCall = std::get_if<GetPosCall>(&call))
            ASSERT_EQ(getPosCall->ExpectedResult, robot.getPos());
        if (const GetDirCall* getDirCall = std::get_if<GetDirCall>(&call))
            ASSERT_EQ(getDirCall->ExpectedResult, robot.getDir());
    }
}

}

namespace WalkingRobotSimulationIITask
{

TEST(WalkingRobotSimulationIITaskTests, Examples)
{
    checkRobot(6, 3, {StepCall(2),
                      StepCall(2),
                      GetPosCall(4, 0),
                      GetDirCall("East"),
                      StepCall(2),
                      StepCall(1),
                      StepCall(4),
                      GetPosCall(1, 2),
                      GetDirCall("West")});
}

TEST(WalkingRobotSimulationIITaskTests, FromWrongAnswers)
{
    checkRobot(20, 14, {StepCall(32),
                        StepCall(18),
                        StepCall(18),
                        GetPosCall(4, 0),
                        GetDirCall("East"),
                        StepCall(18),
                        GetPosCall(19, 3),
                        GetDirCall("North"),
                        StepCall(45),
                        StepCall(37),
                        StepCall(39),
                        GetPosCall(15, 0),
                        GetDirCall("East"),
                        StepCall(8),
                        StepCall(11),
                        StepCall(18),
                        GetPosCall(0, 12),
                        GetDirCall("South"),
                        StepCall(3),
                        StepCall(39),
                        StepCall(7),
                        StepCall(31),
                        StepCall(42),
                        GetPosCall(5, 13),
                        GetDirCall("West"),
                        StepCall(35),
                        StepCall(11),
                        StepCall(36),
                        StepCall(29),
                        StepCall(10),
                        GetPosCall(12, 13),
                        GetDirCall("West"),
                        StepCall(49),
                        StepCall(31),
                        GetPosCall(0, 9),
                        GetDirCall("South"),
                        StepCall(31),
                        StepCall(47),
                        GetPosCall(5, 0),
                        GetDirCall("East"),
                        StepCall(29),
                        StepCall(1),
                        GetPosCall(16, 13),
                        GetDirCall("West"),
                        StepCall(5),
                        StepCall(44)});
    checkRobot(8, 2, {StepCall(17),
                      GetPosCall(1, 0),
                      GetDirCall("East"),
                      StepCall(21),
                      GetPosCall(6, 0),
                      GetDirCall("East"),
                      StepCall(22),
                      StepCall(34),
                      GetPosCall(1, 1),
                      GetDirCall("West"),
                      StepCall(1),
                      StepCall(46),
                      StepCall(35),
                      GetPosCall(0, 0),
                      GetDirCall("South"),
                      StepCall(44),
                      StepCall(14),
                      StepCall(31),
                      GetPosCall(6, 1),
                      GetDirCall("West"),
                      StepCall(50)});
}

}
