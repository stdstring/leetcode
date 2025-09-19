#include <cctype>
#include <string>
#include <variant>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Spreadsheet
{
public:
    Spreadsheet(int rows) : _storage(std::vector<int>(rows * ColumnCount, 0))
    {
    }

    void setCell(std::string const &cell, int value)
    {
        _storage[getCellIndex(cell)] = value;
    }

    void resetCell(std::string const &cell)
    {
        _storage[getCellIndex(cell)] = 0;
    }

    int getValue(std::string const &formula)
    {
        // formula: "=X+Y"
        size_t operatorIndex = formula.find('+');
        std::string leftOperandStr(formula.substr(1, operatorIndex - 1));
        std::string rightOperandStr(formula.substr(operatorIndex + 1));
        int leftOperand = getOperandValue(leftOperandStr);
        int rightOperand = getOperandValue(rightOperandStr);
        return leftOperand + rightOperand;
    }

private:
    static constexpr size_t ColumnCount = 26;
    static constexpr size_t ColumnStart = 'A';
    std::vector<int> _storage;

    size_t getCellIndex(std::string const &cell)
    {
        size_t column = cell[0] - ColumnStart;
        std::string rowPart(cell.substr(1));
        size_t row = std::stoi(rowPart) - 1;
        return row * ColumnCount + column;
    }

    int getOperandValue(std::string const &operandStr)
    {
        if (std::isdigit(operandStr[0]))
            return std::stoi(operandStr);
        return _storage[getCellIndex(operandStr)];
    }
};

}

namespace
{

struct SetCellCall
{
    SetCellCall(std::string const &cell, int value) : Cell(cell), Value(value)
    {
    }

    std::string Cell;
    int Value;
};

struct ResetCellCall
{
    explicit ResetCellCall(std::string const &cell) : Cell(cell)
    {
    }

    std::string Cell;
};

struct GetValueCall
{
    GetValueCall(std::string const &formula, int expectedValue) : Formula(formula), ExpectedValue(expectedValue)
    {
    }

    std::string Formula;
    int ExpectedValue;
};

typedef std::variant<SetCellCall, ResetCellCall, GetValueCall> TCallVariant;

void checkSpreadsheet(int rows, std::vector<TCallVariant> const &calls)
{
    Spreadsheet spreadsheet(rows);
    for (TCallVariant const &call : calls)
    {
        if (const SetCellCall* setCellCall = std::get_if<SetCellCall>(&call))
            ASSERT_NO_THROW(spreadsheet.setCell(setCellCall->Cell, setCellCall->Value));
        if (const ResetCellCall* resetCellCall = std::get_if<ResetCellCall>(&call))
            ASSERT_NO_THROW(spreadsheet.resetCell(resetCellCall->Cell));
        if (const GetValueCall* getValueCall = std::get_if<GetValueCall>(&call))
            ASSERT_EQ(getValueCall->ExpectedValue, spreadsheet.getValue(getValueCall->Formula));
    }
}

}

namespace DesignSpreadsheetTask
{

TEST(DesignSpreadsheetTaskTests, Examples)
{
    checkSpreadsheet(3, {GetValueCall("=5+7", 12),
                         SetCellCall("A1", 10),
                         GetValueCall("=A1+6", 16),
                         SetCellCall("B2", 15),
                         GetValueCall("=A1+B2", 25),
                         ResetCellCall("A1"),
                         GetValueCall("=A1+B2", 15)});
}

TEST(DesignSpreadsheetTaskTests, FromWrongAnswers)
{
    checkSpreadsheet(24, {SetCellCall("B24", 66688), ResetCellCall("O15")});
}

}