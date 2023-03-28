#include <stdio.h>

#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct Currency
{
    char *name;
    int currencyAmount;
    char *currencyType;
    int coins[4];

} Currency;

#endif
