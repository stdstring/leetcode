class Solution
{
public:
    void rotate(std::vector<std::vector<int>>& matrix)
    {
        int n = matrix.size();
        int minIndex = 0;
        int maxIndex = n - 1;
        while (minIndex < maxIndex)
        {
            for (int shift = 0; shift < maxIndex - minIndex; ++shift)
            {
                int value1 = matrix[minIndex][minIndex + shift];
                int value2 = matrix[minIndex + shift][maxIndex];
                int value3 = matrix[maxIndex][maxIndex - shift];
                int value4 = matrix[maxIndex - shift][minIndex];
                matrix[minIndex + shift][maxIndex] = value1;
                matrix[maxIndex][maxIndex - shift] = value2;
                matrix[maxIndex - shift][minIndex] = value3;
                matrix[minIndex][minIndex + shift] = value4;
            }
            ++minIndex;
            --maxIndex;
        }
    }
};