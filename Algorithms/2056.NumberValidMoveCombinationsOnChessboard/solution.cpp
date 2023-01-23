#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countCombinations(std::vector<std::string> const &pieces, std::vector<std::vector<int>> const &positions) const
    {
        std::vector<std::vector<Move>> piecesPossibleMoves;
        for (size_t index = 0; index < pieces.size(); ++index)
            piecesPossibleMoves.emplace_back(generatePossibleMoves(pieces[index], positions[index]));
        std::vector<Move> moveCombination;
        return static_cast<int>(calcMoveCombinations(piecesPossibleMoves, 0, moveCombination));
    }

private:
    static constexpr int BoardSize = 8;

    struct Move
    {
        Move(int row0, int column0, int rowDelta, int columnDelta, int length) : Row0(row0), Column0(column0), RowDelta(rowDelta), ColumnDelta(columnDelta), Length(length)
        {
        }

        int Row0;
        int Column0;
        int RowDelta;
        int ColumnDelta;
        int Length;
    };

    [[nodiscard]] std::vector<Move> generatePossibleMoves(std::string const &piece, std::vector<int> const &position) const
    {
        std::vector<Move> possibleMoves;
        if (piece == "rook")
            generateHVMoves(position[0], position[1], possibleMoves, true);
        if (piece == "queen")
        {
            generateHVMoves(position[0], position[1], possibleMoves, true);
            generateDiagonalMoves(position[0], position[1], possibleMoves, false);
        }
        if (piece == "bishop")
            generateDiagonalMoves(position[0], position[1], possibleMoves, true);
        return possibleMoves;
    }

    void generateHVMoves(int row0, int column0, std::vector<Move> &dest, bool includeCurrent) const
    {
        if (includeCurrent)
            dest.emplace_back(row0, column0, 0, 0, 0);
        int length = 0;
        for (int row = row0 - 1; row > 0; --row)
            dest.emplace_back(row0, column0, -1, 0, ++length);
        length = 0;
        for (int row = row0 + 1; row <= BoardSize; ++row)
            dest.emplace_back(row0, column0, 1, 0, ++length);
        length = 0;
        for (int column = column0 - 1; column > 0; --column)
            dest.emplace_back(row0, column0, 0, -1, ++length);
        length = 0;
        for (int column = column0 + 1; column <= BoardSize; ++column)
            dest.emplace_back(row0, column0, 0, 1, ++length);
    }

    void generateDiagonalMoves(int row0, int column0, std::vector<Move> &dest, bool includeCurrent) const
    {
        if (includeCurrent)
            dest.emplace_back(row0, column0, 0, 0, 0);
        int length = 0;
        for (int row = row0 - 1, column = column0 - 1; (row > 0) && (column > 0); --row, --column)
            dest.emplace_back(row0, column0, -1, -1, ++length);
        length = 0;
        for (int row = row0 + 1, column = column0 + 1; (row <= BoardSize) && (column <= BoardSize); ++row, ++column)
            dest.emplace_back(row0, column0, 1, 1, ++length);
        length = 0;
        for (int row = row0 - 1, column = column0 + 1; (row > 0) && (column <= BoardSize); --row, ++column)
            dest.emplace_back(row0, column0, -1, 1, ++length);
        length = 0;
        for (int row = row0 + 1, column = column0 - 1; (row <= BoardSize) && (column > 0); ++row, --column)
            dest.emplace_back(row0, column0, 1, -1, ++length);
    }

    [[nodiscard]] size_t calcMoveCombinations(std::vector<std::vector<Move>> const &piecesPossibleMoves, size_t index, std::vector<Move> &moveCombination) const
    {
        const size_t maxIndex = piecesPossibleMoves.size() - 1;
        size_t result = 0;
        for (Move const &move : piecesPossibleMoves[index])
        {
            moveCombination.push_back(move);
            if (index == maxIndex)
                result += (isMoveCombinationValid(moveCombination) ? 1 : 0);
            else
                result += calcMoveCombinations(piecesPossibleMoves, index + 1, moveCombination);
            moveCombination.pop_back();
        }
        return result;
    }

    [[nodiscard]] bool isMoveCombinationValid(std::vector<Move> const &moveCombination) const
    {
        std::vector<int> board(1LL * BoardSize * BoardSize, 0);
        for (Move const &move : moveCombination)
        {
            int row = move.Row0;
            int column = move.Column0;
            for (int length = 0; length < move.Length; ++length)
            {
                const int cell = (row - 1) * BoardSize + (column - 1);
                const int moveMask = 1 << length;
                if ((board[cell] & moveMask) > 0)
                    return false;
                board[cell] |= moveMask;
                row += move.RowDelta;
                column += move.ColumnDelta;
            }
            const int stopMoveMask = calcStopMoveMask(move.Length);
            const int cell = (row - 1) * BoardSize + (column - 1);
            if ((board[cell] & stopMoveMask) > 0)
                return false;
            board[cell] |= stopMoveMask;
        }
        return true;
    }

    [[nodiscard]] int calcStopMoveMask(size_t length) const
    {
        int cellValue = 0;
        for (; length < BoardSize; ++length)
            cellValue |= (1 << length);
        return cellValue;
    }
};

}

namespace NumberValidMoveCombinationsOnChessboardTask
{

TEST(NumberValidMoveCombinationsOnChessboardTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.countCombinations({"rook"}, {{1, 1}}));
    ASSERT_EQ(22, solution.countCombinations({"queen"}, {{1, 1}}));
    ASSERT_EQ(12, solution.countCombinations({"bishop"}, {{4, 3}}));
}

TEST(NumberValidMoveCombinationsOnChessboardTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(196, solution.countCombinations({"rook", "rook"}, {{1, 1}, {1, 2}}));
    ASSERT_EQ(281, solution.countCombinations({"queen", "bishop"}, {{5, 7}, {3, 4}}));
    ASSERT_EQ(96, solution.countCombinations({"bishop", "rook"}, {{8, 5}, {7, 7}}));
}

}
