#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class SubrectangleQueries
{
public:
    SubrectangleQueries(std::vector<std::vector<int>> const &rectangle) : _rectangle(rectangle)
    {
    }

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue)
    {
        for (int row = row1; row <= row2; ++row)
        {
            for (int column = col1; column <= col2; ++column)
                _rectangle[row][column] = newValue;
        }
    }

    int getValue(int row, int col)
    {
        return _rectangle[row][col];
    }

private:
    std::vector<std::vector<int>> _rectangle;
};

}

namespace
{

struct UpdateCall
{
    UpdateCall(int row1, int col1, int row2, int col2, int newValue) : Row1(row1), Col1(col1), Row2(row2), Col2(col2), NewValue(newValue)
    {
    }

    int Row1;
    int Col1;
    int Row2;
    int Col2;
    int NewValue;
};

struct GetValueCall
{
    GetValueCall(int row, int col, int expectedValue) : Row(row), Col(col), ExpectedValue(expectedValue)
    {
    }

    int Row;
    int Col;
    int ExpectedValue;
};

void checkSubrectangleQueries(std::vector<std::vector<int>> const &sourceRectangle, std::vector<std::variant<UpdateCall, GetValueCall>> const &calls)
{
    SubrectangleQueries subrectangleQueries(sourceRectangle);
    for (std::variant<UpdateCall, GetValueCall> const &call : calls)
    {
        if (const UpdateCall* updateCall = std::get_if<UpdateCall>(&call))
            ASSERT_NO_THROW(subrectangleQueries.updateSubrectangle(updateCall->Row1, updateCall->Col1, updateCall->Row2, updateCall->Col2, updateCall->NewValue));
        if (const GetValueCall* getValueCall = std::get_if<GetValueCall>(&call))
            ASSERT_EQ(getValueCall->ExpectedValue, subrectangleQueries.getValue(getValueCall->Row, getValueCall->Col));
    }
}

}


namespace SubrectangleQueriesTask
{

TEST(SubrectangleQueriesTaskTests, Examples)
{
    // Example1
    checkSubrectangleQueries({{1, 2, 1}, {4, 3, 4}, {3, 2, 1}, {1, 1, 1}},
                             {GetValueCall(0, 2, 1),
                              UpdateCall(0, 0, 3, 2, 5),
                              GetValueCall(0, 2, 5),
                              GetValueCall(3, 1, 5),
                              UpdateCall(3, 0, 3, 2, 10),
                              GetValueCall(3, 1, 10),
                              GetValueCall(0, 2, 5)});
    // Example2
    checkSubrectangleQueries({{1, 1, 1}, {2, 2, 2}, {3, 3, 3}},
                             {GetValueCall(0, 0, 1),
                              UpdateCall(0, 0, 2, 2, 100),
                              GetValueCall(0, 0, 100),
                              GetValueCall(2, 2, 100),
                              UpdateCall(1, 1, 2, 2, 20),
                              GetValueCall(2, 2, 20)});
}

}