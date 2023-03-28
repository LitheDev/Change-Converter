#include "struct.h"

// Reads information from file to struct arrays
void CustomerFileToStruct(FILE *file, int lineCount, Currency *array);

// Deletes element (pos) and shifts elements after up in the array
void DeleteElement(Currency *array, int pos, int arraySize);

// Writes Coin Data to Struct
void CoinsDatatoStruct(Currency *cInput, int lineCount);

// Writes Array Data to File
void ArrayDataToFile(FILE *file, Currency *cInput, int lineCount);