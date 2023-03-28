
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "array.h"
#include "searchmenu.h"
#include "math.h"

void PrintArgCheck(int argc, char *argv[], int num)
{
    // If argument quantity matches argument criteria
    if (argc == num)
    {
        printf("The argument supplied is: %s\n", argv[1]);
        return;
    }
    // If argument quantity is greater than criteria
    else if (argc > num)
    {
        printf("Error: Too many arguments!\n");
        printf("Closing Program\n");
        return;
    }
    else
    {
        printf("Error: No command line arguments given\n");
        printf("Closing Program\n");
        return;
    }
}

// Checks file and prints relevant errors
void PrintFileCheck(FILE *File)
{

    if (File == NULL)
    {
        perror("Error: File Opening failed!\n");
        return;
    }

    else
    {
        printf("File opened successfully!\n");
        return;
    }
}

// Validates Line Quantity based on criteria minLines and maxLines
int ValidateLineQty(FILE *file, char *line, int minLines, int maxLines)
{
    // Gets lineQuantity from file
    int lineCount = GetLineQty(file, line);

    // If lineCount is within criteria
    if ((lineCount >= minLines) && (lineCount <= maxLines))
    {
        // If lineCount is 0
        if (lineCount == 0)
        {
            printf("Warning: There are 0 lines in this file (The file appears to be empty)\n");
        }
        return (lineCount);
    }
    else
    {
        printf("Line count of file is: %d\n", lineCount);
        printf("Line count is not within allowable range (%d - %d). Closing Program", minLines, maxLines);
        return (lineCount);
    }
}

// Checks Elements against criteria, prints relevant error and returns -1 if any elements are not within criteria
int ValidateCurrencyInput(Currency *cInput, int lineCount)
{
    //  Used to close program in main
    int valid = 0;

    for (int i = 0; i < lineCount; i++)
    {
        // Ensures name is capitalized properly regardless of how it was input
        FormatName(cInput[i].name, strlen(cInput[i].name));

        // If [i].cType is AU
        if (strcmp(cInput[i].currencyType, "cents in AU$") == 0)
        {
            // Checks if AUD is a multiple of 5
            if (cInput[i].currencyAmount % 5 != 0)
            {
                printf("Index: %d is AUD: %d. Not a multiple of 5\n", i, cInput[i].currencyAmount);
                valid = -1;
            }

            // Checks if element is within range of 5 to 95
            if ((cInput[i].currencyAmount < 5) || (cInput[i].currencyAmount > 95))
            {
                printf("Index: %d is AUD: %d. Not within range of (5-95).\n", i, cInput[i].currencyAmount);
                valid = -1;
            }
        }
        // If [i].cType is US
        if (strcmp(cInput[i].currencyType, "cents in US$") == 0)
        {
            // Checks if element is within range of 1 to 95
            if ((cInput[i].currencyAmount < 1) || (cInput[i].currencyAmount > 95))
            {
                printf("Index: %d is US: %d. Not within range of (1-95).\n", i, cInput[i].currencyAmount);
                valid = -1;
            }
        }
        // If [i].cType is EUR
        if (strcmp(cInput[i].currencyType, "cents in EUR") == 0)
        {
            // Checks if element is within range of 1 to 95
            if ((cInput[i].currencyAmount < 1) || (cInput[i].currencyAmount > 95))
            {
                printf("Index: %d is EUR: %d. Not within range of (1-95).\n", i, cInput[i].currencyAmount);
                valid = -1;
            }
        }
        // If an element has a type that is NOT AU, US, AND EUR, print relevant error and return -1 to main
        if ((strcmp(cInput[i].currencyType, "cents in AU$") != 0) && (strcmp(cInput[i].currencyType, "cents in US$") != 0) && (strcmp(cInput[i].currencyType, "cents in EUR") != 0))
        {
            printf("Index: %d has an invalid currency\n", i, cInput[i].currencyAmount);
            valid = -1;
        }
    }
    if (valid == -1)
    {
        printf("Closing Program\n");
    }
    return (valid);
}

int main(int argc, char *argv[])
{


    // Initialize Variables
    char line[128];
    int minLines = 0;
    int maxLines = 10;
    int lineCount = 0;

    // Initalize File Data Types
    FILE *srcFile, *dstFile;

    // Checks cmd arguments, prints error if invalid
    PrintArgCheck(argc, argv, 2);

    // If Argument = Valid, open file, then check file similarly as above
    if (argc == 2)
    {
        srcFile = fopen(argv[1], "r");
        PrintFileCheck(srcFile);

        // If file is not invalid, write quantity of lines from file to lineCount (Also prints errors if outside range)
        if (srcFile != NULL)
        {
            lineCount = ValidateLineQty(srcFile, line, minLines, maxLines);
        }
    }

    // END PROGRAM IF STATEMENT: If Argument does not match criteria, OR if file equals NULL OR if lines are outside allowable range
    if ((argc != 2) || (srcFile == NULL) || (lineCount < minLines) || (lineCount > maxLines))
    {

        return (-1);
    }

    // Dynamically allocates struct array size based on linequantity in file
    Currency *cInput = (calloc(lineCount, sizeof(Currency)));

    // Writes data from file to struct arrays then validates it
    CustomerFileToStruct(srcFile, lineCount, cInput);
    int ValidInput = ValidateCurrencyInput(cInput, lineCount);

    // END PROGRAM IF STATEMENT: If any of the initial currencies in one element fall outside of allowable range, the program will close.
    if (ValidInput == -1)
    {
        fclose(srcFile);
        free(cInput);
        return (-1);
    }

    // Sums currencyAmount of elements that match name & type, moves sum to top of array, returns new lineCount based on matches.
    lineCount = CalculateCurrency(cInput, lineCount);

    // Close source file
    fclose(srcFile);

    // Calculate coin data and write coin amounts to struct arrays
    CoinsDatatoStruct(cInput, lineCount);

    // Opens name search menu for entering in a name. Then prints that customer, their currency amount and their coin amounts with respect to their currencyType
    NameSearchMenu(line, cInput, lineCount);

    // Opens destination file with write permissions
    printf("Opening Output File\n");
    dstFile = fopen("output.csv", "w");

    // Validates destination file
    PrintFileCheck(dstFile);

    // END PROGRAM IF STATEMENT: If destination file is not valid, program will close
    if (dstFile == NULL)
    {
        free(cInput);
        return (-1);
    }

    // Writes data from arrays to destination file
    ArrayDataToFile(dstFile, cInput, lineCount);

    // End of program
    fclose(dstFile);
    free(cInput);
    return (0);
}
