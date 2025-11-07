#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <math.h>
#include <conio.h>

using namespace std;

const int CACHE_SIZE = 1000;
const string productFilePath = "products.txt";

// Helper Functions
int runMenu(string msg, int rangeStart, int rangeEnd);
int updateProductsCache(int ids[], string names[], float prices[], int quantities[], int attributeCount);
void clearConsole();

int main()
{
    int productIds[CACHE_SIZE];
    string productNames[CACHE_SIZE];
    float productPrices[CACHE_SIZE];
    int productQuantities[CACHE_SIZE];

    const int productAttributeCount = 4;

    int menuChoice = runMenu("Welcome to Inventory Sales Management System!\n1. Product Management\n2. Inventory Tracking\n3. Sales Management\n4. Reports & Statistics\n5. Exit", 1, 5);

    if (menuChoice == 1)
    {
        int productCacheState = updateProductsCache(productIds, productNames, productPrices, productQuantities, productAttributeCount);

        if(productCacheState == -21)
        {
            clearConsole();
            cout << "The data in the file seems to be corrupted." << endl;
            getch();
            exit(-21);

        } else if(productCacheState == -30)
        {
            clearConsole();
            cout << "The data file throws an error upon operating." << endl;
            getch();
            exit(-30);
        } else if(productCacheState == -50)
        {
            clearConsole();
            cout << "Data written to unallocated memory. Did an integer overflow?" << endl;
            getch();
            exit(-50);
        } else
        {
            exit(0);
        }
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

int updateProductsCache(int ids[], string names[], float prices[], int quantities[], int attributeCount)
{
    ifstream file(productFilePath);
    if (!file.is_open())
    {
        return -30; // Error code for file not found
    }

    string line;
    int lineNumber = 0;
    while (getline(file, line))
    {
        int entityNumber = lineNumber - 1;
        if (lineNumber == 0)
        {
            lineNumber++;
            continue;
        }

        int attributeCounter = 0;
        string entityString[attributeCount];
        for (int i = 0; i < line.size(); i++)
        {
            char ch = line[i];
            if (ch == ';')
            {
                attributeCounter++;
                if (attributeCounter == attributeCount)
                    break;
            }

            if (ch != ';')
                entityString[attributeCounter] += ch;
        }

        try
        {
            int productId = stoi(entityString[0]);
            string productName = entityString[1];
            float productPrice = stof(entityString[2]);
            int productQuantity = stoi(entityString[3]); // This is repetitive for more attributes, consider using loop here

            ids[entityNumber] = productId;
            names[entityNumber] = productName;
            prices[entityNumber] = productPrice;
            quantities[entityNumber] = productQuantity;
        }
        catch (const invalid_argument &e)
        {
            return -21; // Error code for invalid data type in file
        }
        catch (const out_of_range &e)
        {
            return -50; // Error code for range overflow
        }
        lineNumber++;
    }

    return 0;
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