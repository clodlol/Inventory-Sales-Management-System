#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <math.h>

using namespace std;

// Helper Functions
int runMenu(string msg, int rangeStart, int rangeEnd);
int loadProducts(long int ids[], string names[], float prices[], int quantities[], int n); // n is the number of attributes
void clearConsole();

int main()
{
    long int productIds[1000];
    string productNames[1000];
    float productPrices[1000];
    int productQuantities[1000];

    int menuChoice = runMenu("Welcome to Inventory Sales Management System!\n1. Product Management\n2. Inventory Tracking\n3. Sales Management\n4. Reports & Statistics\n5. Exit", 1, 5);

    if (menuChoice == 1)
    {
        // load product management
    }
    else if (menuChoice == 2)
    {
        // load inventory tracking
    }
    else if (menuChoice == 3)
    {
        // load sales management
    }
    else if (menuChoice == 4)
    {
        // load reports & stats
    }
    else if (menuChoice == 5)
    {
        exit(0);
    }
}

int loadProducts(long int ids[], string names[], float prices[], int quantities[], int n)
{
    ifstream file("products.txt");
    if (!file.is_open())
    {
        return -30; // Error code for file not found
    }

    string line;
    int lineNumber = 0;
    while (getline(file, line))
    {
        int columnCounter = 0;
        string columnString;
        for (int i = 0; i < line.size(); i++)
        {
            int currentAttributeString;
            char ch = line[i];
            if (ch == ';')
                columnCounter++;

            if (columnCounter == 0)
            {
                //string currentAttributeString += ch;
                if (!isdigit(ch))
                    return -21; // Error code for invalid data format in file
                //ids[lineNumber] += ('0' - ch) * ((int)pow(10, productIdLength - i));
            } else if(columnCounter == 1)
            {

            }
        }
        lineNumber++;
    }
}

int runMenu(string msg, int rangeStart, int rangeEnd)
{
    int choice;
    while (true)
    {
        cout << msg
             << endl
             << endl
             << endl
             << "Enter your choice: ";

        if (cin >> choice)
        {
            if (choice >= rangeStart && choice <= rangeEnd)
            {
                return choice;
            }
            else
            {
                clearConsole();
                continue;
            }
        }
        else
        {
            cin.clear();                                         // ignores error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores invalid input
            clearConsole();
            continue;
        }
    }
}

void clearConsole()
{
    system("cls"); // Only works on windows
}