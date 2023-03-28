# Change-Converter
A currency converter (and name searcher) I created for an Assignment when learning C programming.
It takes input from a txt file and prints the resultant change of that currency.

How to Run

The program is run in command line and takes an input, in this case coins.txt (e.g main.exe coins.txt).
Coins.txt will contain a name, denomination and amount of currency.
If coins.txt contains invalid input, or is not found the program will give an appropriate error and close.
If coins.txt is empty, the program will give an error message, however it will still continue.

Searching for Names and printing change

The program will then prompt for an option, to enter a name, or to exit.
Entering names is not case sensitive.
If the name is not found, the program will return an error, if the name is found, it will print the persons currency and the change it would receive in that 
currency type (EUR, US, AUD)
If the name is found twice (for example, two people having the same name) it will print both persons information.
