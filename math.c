#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "math.h"
#include "array.h"

// Reads information from file to struct arrays
int CalculateCurrency(Currency *cInput, int lineCount)
{
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < lineCount; j++)
        {
            // If [i] element is 0, overwrite [i] and shift all elements in the array. (Reduces arraysize for next array)
            if ((cInput[i].currencyAmount == 0) && (i < lineCount))
            {

                DeleteElement(cInput, i, lineCount);
                lineCount--;
            }

            // If [i] element is not 0 check if name and type match
            if (cInput[i].currencyAmount != 0)
            {
                // if name and type match AND [i] does not match [j], sum [i], zero [j]
                if ((strcmp(cInput[i].currencyType, cInput[j].currencyType) == 0) && (strcmp(cInput[i].name, cInput[j].name) == 0) && (i != j))
                {
                    cInput[i].currencyAmount = (cInput[i].currencyAmount + cInput[j].currencyAmount);
                    cInput[j].currencyAmount = 0;
                }
            }
        }

    }

    return (lineCount);
}

// Adds up line quantity from file and returns it
int GetLineQty(FILE *file, char *line)
{

    int lineCount = 0;

    // While fGets reads to 128 and doesnt reach end of file
    while (fgets(line, 128, file))
    {
        lineCount++; // Increment linecount by 1
    }
    rewind(file); // Rewind file for future 'f' function uses
    return (lineCount);
}

// Calculates coins, adds quantity to coins pointer, subtracts from totalAmount, returns totalAmount
int CalculateCoins(int *coins, int totalAmount, int denomination)
{
    int coinQty = 0;

    // While TotalAmount is greater than denomination
    while (totalAmount >= denomination)
    {
        totalAmount = totalAmount - denomination;
        coinQty++;
    }

    *coins = coinQty;
    return (totalAmount);
}