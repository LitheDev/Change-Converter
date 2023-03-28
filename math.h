#include "struct.h"

// Reads information from file to struct arrays
int CalculateCurrency(Currency *cInput, int lineCount);

// Calculates coins, adds quantity to coins pointer, subtracts from totalAmount, returns totalAmount
int CalculateCoins(int *coins, int totalAmount, int denomination);

// Adds up line quantity from file and returns it
int GetLineQty(FILE *file, char *line);