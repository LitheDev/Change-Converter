#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "searchmenu.h"

// Prompts user to Options 1 (Enter name) or 2 (Exit)
void NameSearchMenu(char *name, Currency *cInput, int lineCount)
{

    int c = 0;
    // Program will continue to prompt for option until 2 is elected
    do
    {
        // Program will report input as invalid if 1 or 2 is not selected
        do
        {
            // Prompts for user choice
            printf("\n1. Enter name\n");
            printf("2. Exit\n");
            scanf("%d", &c);

            if ((c != 1) && (c != 2))
            {
                printf("Invalid Input!\n");
            }
        } while ((c != 1) && (c != 2));

        // Program will read in name and print currency data if 1 is selected
        if (c == 1)
        {
            printf("\nEnter a name to search for: ");
            ReadString(name, 128);
            FormatName(name, strlen(name));
            PrintCurrencyData(name, cInput, lineCount);
        }

    } while (c != 2);

    // Program will close if 2 is selected
    return;
}

// Prompts user for String
void ReadString(char *String, int ArraySize)
{
    fflush(stdin);
    fgets(String, ArraySize, stdin);
    String[strlen(String) - 1] = '\0';
    return;
}

// Prints Customer and Coin Data
void PrintCurrencyData(char *name, Currency *cInput, int lineCount)
{
    int found = 0;

    for (int i = 0; i < lineCount; i++)
    {
        // If name Input matches [i].name element, print information
        if (strcmp(name, cInput[i].name) == 0)
        {
            found = 1;

            printf("\nCustomer:\n");
            printf("%s %d %s\n", cInput[i]);
            printf("\nChange:\n");

            // If [i].cType is "Cents in AU", print quantity of relevant denominations
            if (strcmp(cInput[i].currencyType, "cents in AU$") == 0)
            {
                int v[4] = {50, 20, 10, 5};
                for (int j = 0; j < 4; j++)
                {
                    if (cInput[i].coins[j] > 0)
                    {
                        printf("%d cents: %d\n", v[j], cInput[i].coins[j]);
                    }
                }
            }
            // If [i].cType is "Cents in US", print quantity of relevant denominations
            if (strcmp(cInput[i].currencyType, "cents in US$") == 0)
            {
                int v[4] = {50, 25, 10, 1};
                for (int j = 0; j < 4; j++)
                {
                    if (cInput[i].coins[j] > 0)
                    {
                        printf("%d cents: %d\n", v[j], cInput[i].coins[j]);
                    }
                }
            }

            // If [i].cType is "Cents in EUR", print quantity of relevant denominations
            if (strcmp(cInput[i].currencyType, "cents in EUR") == 0)
            {
                int v[4] = {20, 10, 5, 1};
                for (int j = 0; j < 4; j++)
                {
                    if (cInput[i].coins[j] > 0)
                    {
                        printf("%d cents: %d\n", v[j], cInput[i].coins[j]);
                    }
                }
            }
        }
    }
    // If name input is not found in array, print error and return to menu
    if (found == 0)
    {

        printf("\nName: %s\n", name);
        printf("Not found\n");
    }
    return;
}

// Formats name (e.g jANE = Jane)
void FormatName(char *name, int nameLength)
{
    int i = 0;

    // Capitalize first letter
    if ((name[i] >= 'a') && (name[i] <= 'z'))
    {
        name[i] = name[i] - 32;
    }

    i++;

    // Decapitalize remaining letters
    for (i; i < nameLength; i++)
    {
        if ((name[i] >= 'A') && (name[i] <= 'Z'))
        {

            name[i] = name[i] + 32;
        }
    }

    return;
}
