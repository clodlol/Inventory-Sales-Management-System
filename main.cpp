#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <conio.h>

using namespace std;

const int CACHE_SIZE = 1000;
const string productFilePath = "products.txt";

int addProduct(int id, int name, float price, int quantity);
int updateProductsCache(int ids[], string names[], float prices[], int quantities[], int attributeCount);

// Helper Functions
void handleError(int code);
void clearConsole();
void getString(string &s);
bool getFloat(float &input, int rangeStart, int rangeEnd, int precisionPoints);
bool getInt(int &input, int rangeStart, int rangeEnd );

int main()
{
    int productIds[CACHE_SIZE];
    string productNames[CACHE_SIZE];
    float productPrices[CACHE_SIZE];
    int productQuantities[CACHE_SIZE];

    const int productAttributeCount = 4;

    while (true)
    {
        clearConsole();

        int menuChoice;

        cout << "Welcome to Inventory Sales Management System!" << endl
             << "1. Product Management" << endl
             << "2. Inventory Tracking" << endl
             << "3. Sales Management" << endl
             << "4. Reports & Statistics" << endl
             << "5. Exit" << endl
             << endl;

        cout << "Enter your choice: ";
        if (!getInt(menuChoice, 1, 5))
            continue;

        if (menuChoice == 1)
        {
            int productCacheState = updateProductsCache(productIds, productNames, productPrices, productQuantities, productAttributeCount);

            if (productCacheState == -21)
            {
                handleError(-21);
                exit(-21);
            }
            else if (productCacheState == -30)
            {
                handleError(-30);
                exit(-30);
            }
            else if (productCacheState == -50)
            {
                handleError(-50);
                exit(-50);
            }

            while (true)
            {
                clearConsole();

                int productMenuChoice;

                cout << "1. Add Product" << endl
                     << "2. Edit Product" << endl
                     << "3. Delete Product" << endl
                     << "4. Go Back" << endl
                     << endl;

                cout << "Enter your choice: ";
                if (!getInt(productMenuChoice, 1, 4))
                    continue;

                if (productMenuChoice == 1)
                {
                    int productId, productQuantity;
                    string productName;
                    float productPrice;

                    clearConsole();

                    cout << "Enter Product Details" << endl
                         << "Name: ";
                    getString(productName);

                    cout << "Price: ";
                    if(!getFloat(productPrice, 0, INT_MAX, 2))
                    {
                        handleError(-20);
                        continue;
                    }
                    
                    cout << "Quantity: ";
                    if(!getInt(productQuantity, 0, INT_MAX))
                    {
                        handleError(-20);
                        continue;
                    }

                    
                }
                else if (productMenuChoice == 2)
                {
                }
                else if (productMenuChoice == 3)
                {
                }
                else if (productMenuChoice == 4)
                {
                    break;
                }
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
            break;
        }
    }

    exit(0);
}

int addProduct(int id, int name, float price, int quantity)
{
    
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

void handleError(int code)
{   
    if(code == -20)
    {
        clearConsole();
        cout << "Invalid data given. Did you make sure prices and quantities are positive?" << endl;
        getch();
    }
    else if (code == -21)
    {
        clearConsole();
        cout << "The data in the file seems to be corrupted." << endl;
        getch();
    }
    else if (code == -30)
    {
        clearConsole();
        cout << "The data file throws an error upon operating." << endl;
        getch();
    }
    else if (code == -50)
    {
        clearConsole();
        cout << "Data written to unallocated memory. Did an integer overflow?" << endl;
        getch();
    }
}

void getString(string &s)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, s);

    string cleanString = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ';')
            break;
        cleanString += s[i];
    }

    s = cleanString;
}

bool getInt(int &input, int rangeStart, int rangeEnd)
{
    if (cin >> input)
    {
        return (input >= rangeStart && input <= rangeEnd);
    }
    else
    {
        cin.clear();                                         // ignores error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores invalid input
        return false;
    }
}

bool getFloat(float &input, int rangeStart, int rangeEnd, int precisionPoints)
{
    if (cin >> input)
    {

        if (input >= rangeStart && input <= rangeEnd)
        {
            float scale = pow(10.0, precisionPoints);
            input =  round(input * scale) / scale;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cin.clear();                                         // ignores error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores invalid input
        return false;
    }
}

void clearConsole()
{
    system("cls"); // Only works on windows
}