#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "array.h"
#include "math.h"

// Reads information from file to struct arrays
void CustomerFileToStruct(FILE *file, int lineCount, Currency *cInput)
{

    for (int i = 0; i < lineCount; i++)
    {
        // Buffer for temporarily storing words
        char buffer[128];

        // Allocates size for name array
        cInput[i].name = (char *)malloc(lineCount * sizeof(Currency));

        // Allocates size for currencyType array
        cInput[i].currencyType = (char *)malloc(lineCount * sizeof(Currency));

        // Reads name and currency amount from file to relevant arrays
        fscanf(file, "%s %d %s\n", cInput[i].name, &cInput[i].currencyAmount, cInput[i].currencyType);

        // Adds remaining words from line to currencyType
        for (int j = 0; j < 2; j++)
        {
            fscanf(file, "%s \n", buffer);          // Scans third (and fourth) word to buffer (in AU/EUR/US)
            strcat(cInput[i].currencyType, " ");    // Adds space to cInput[i].currencyType
            strcat(cInput[i].currencyType, buffer); // Adds word stored in buffer to cInput[i].currencyType
        }
    }
}

// Uses pos as indicator for element to be deleted, shifts all elements up in array
void DeleteElement(Currency *array, int pos, int arraySize)
{
    int k;
    for (k = pos; k < arraySize - 1; k++)
    {
        array[k] = array[k + 1];
    }

    return;
}

// Calculates coin data depending on currency type
void CoinsDatatoStruct(Currency *cInput, int lineCount)
{
    for (int i = 0; i < lineCount; i++)
    {
    
        int tempCurrency = cInput[i].currencyAmount;

        // If CurrencyType equals Cents in AU$
        if (strcmp(cInput[i].currencyType, "cents in AU$") == 0)
        {
            int v[4] = {50, 20, 10, 5};
            for (int j = 0; j < 4; j++)
            {
                tempCurrency = CalculateCoins(&cInput[i].coins[j], tempCurrency, v[j]);
            }
        }
        
        // If CurrencyType equals Cents in US
        if (strcmp(cInput[i].currencyType, "cents in US$") == 0)
        {
            int v[4] = {50, 25, 10, 1};

            for (int j = 0; j < 4; j++)
            {
                tempCurrency = CalculateCoins(&cInput[i].coins[j], tempCurrency, v[j]);
            }
        }

        // If CurrencyType equals Cents in EUR
        if (strcmp(cInput[i].currencyType, "cents in EUR") == 0)
        {
            int v[4] = {20, 10, 5, 1};
            for (int j = 0; j < 4; j++)
            {
                tempCurrency = CalculateCoins(&cInput[i].coins[j], tempCurrency, v[j]);
            }
        }
    }
    return;
}

// Writes array data to output file
void ArrayDataToFile(FILE *file, Currency *cInput, int lineCount)
{
    int i;

    for (i = 0; i < lineCount; i++)
    {
        fprintf(file, "%s, the change for %d %s is %d, %d, %d, %d\n", cInput[i]);
    }
}
