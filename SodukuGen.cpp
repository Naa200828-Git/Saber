int main()
{
    // Basic
    // Could Use bit-m for id save, += 9 instead of * 9
    // Function instead of restate function 

    unsigned char Board[81],
        ValidNums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
        ValidNumsAmount = 0;

    for (unsigned char i = 0; i < 81; i++)
    {
        for (unsigned char z = 0; z < 9; z++)
            if ((i / 9) + z)
                ValidNums[((i / 9) + z) - 1] = 0;
        for (unsigned char x = 0; x < 9; x++)
            if ((81 / i) + x)
                ValidNums[((81 / i) + x) - 1] = 0;
        for (unsigned char y = 0; y < 9; y++)
            if ((81 / i) + y * 9)
                ValidNums[((81 / i) + y) - 1] = 0;
    
        for (unsigned char j = 0; j < 9; j++)
            if (ValidNums[9])
                ValidNumsAmount++;
        Board[i] = 
    }
}