#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <conio.h>
#include <ctime>

using namespace std;

const int CACHE_SIZE = 20;
const string productFilePath = "products.txt";
const int idDigitCount = 2;

int addProduct(int id, string name, float price, int quantity);
int updateProduct(int id, string name, float price, int quantity);
int deleteProduct(int id);
int updateProductsCache(int ids[], string names[], float prices[], int quantities[], int attributeCount); // Attribute count is kinda useless we'll rmeove it later

// Helper Functions
void handleError(int code);
void clearConsole();
void getString(string &s);
bool getFloat(float &input, int rangeStart, int rangeEnd, int precisionPoints);
bool getInt(int &input, int rangeStart, int rangeEnd);
int getRandomInt(int min, int max);

int main()
{
    srand(time(0)); // Helpful for random number gen

    int productIds[CACHE_SIZE] = {0};
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

                    if (productName.size() <= 3)
                    {
                        handleError(-20);
                        continue;
                    }

                    cout << "Price: ";
                    if (!getFloat(productPrice, 0, INT_MAX, 2))
                    {
                        handleError(-20);
                        continue;
                    }

                    cout << "Quantity: ";
                    if (!getInt(productQuantity, 0, INT_MAX))
                    {
                        handleError(-20);
                        continue;
                    }

                    productId = getRandomInt(1, (int)pow(10.0, idDigitCount));

                    int newProductState = addProduct(productId, productName, productPrice, productQuantity);

                    if (newProductState == -30)
                    {
                        handleError(-30);
                        continue;
                    }
                    else if (newProductState == 0)
                    {
                        updateProductsCache(productIds, productNames, productPrices, productQuantities, 4);
                        cout << endl
                             << "A new product has been entered into the system." << endl
                             << "ID: " << productId << endl
                             << "Name: " << productName << endl
                             << "Price: " << productPrice << "$" << endl
                             << "Quantity: " << productQuantity << endl
                             << endl;

                        cout << "Press any key to go back...";
                        getch();
                        continue;
                    }
                }
                else if (productMenuChoice == 2)
                {
                    int productId, oldQuantity;
                    string oldName;
                    float oldPrice;
                    clearConsole();

                    cout << "Enter Product Details" << endl
                         << "ID: ";
                    if (!getInt(productId, 1, INT_MAX))
                    {
                        handleError(-20);
                        continue;
                    }

                    bool found = false;
                    for (int i = 0; i < CACHE_SIZE; i++)
                    {
                        if (productIds[i] == productId)
                        {
                            oldName = productNames[i];
                            oldQuantity = productQuantities[i];
                            oldPrice = productPrices[i];
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        handleError(-10);
                        continue;
                    }

                    string newProductName;
                    int newProductQuantity;
                    float newProductPrice;

                    cout << endl
                         << endl
                         << "Enter updated details for product " << productId << " (leave empty to retain)" << endl
                         << "Name: ";
                    getString(newProductName);

                    if (newProductName.size() == 0)
                    {
                        newProductName = oldName;
                    }

                    if (newProductName.size() >= 1 && newProductName.size() <= 3)
                    {
                        handleError(-20);
                        continue;
                    }

                    cout << "Price: ";
                    if (!getFloat(newProductPrice, 0, INT_MAX, 2))
                    {
                        handleError(-20);
                        continue;
                    }

                    cout << "Quantity: ";
                    if (!getInt(newProductQuantity, 0, INT_MAX))
                    {
                        handleError(-20);
                        continue;
                    }

                    int updateProductState = updateProduct(productId, newProductName, newProductPrice, newProductQuantity);
                    if (updateProductState == 0)
                    {
                        updateProductsCache(productIds, productNames, productPrices, productQuantities, 4);
                        cout << endl
                             << "The specified product has been edited." << endl
                             << "ID: " << productId << endl
                             << "Name: " << oldName << " -> " << newProductName << endl
                             << "Price: " << oldPrice << "$" << " -> " << newProductPrice << "$" << endl
                             << "Quantity: " << oldQuantity << " -> " << newProductQuantity << endl
                             << endl;

                        cout << "Press any key to go back...";
                        getch();
                        continue;
                    }
                    else
                    {
                        handleError(updateProductState);
                        continue;
                    }
                }
                else if (productMenuChoice == 3)
                {
                    int productId, oldQuantity;
                    string oldName;
                    float oldPrice;
                    clearConsole();

                    cout << "Enter Product Details" << endl
                         << "ID: ";
                    if (!getInt(productId, 1, INT_MAX))
                    {
                        handleError(-20);
                        continue;
                    }

                    bool found = false;
                    for (int i = 0; i < CACHE_SIZE; i++)
                    {
                        if (productIds[i] == productId)
                        {
                            oldName = productNames[i];
                            oldQuantity = productQuantities[i];
                            oldPrice = productPrices[i];
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        handleError(-10);
                        continue;
                    }

                    int deleteProductState = deleteProduct(productId);
                    if (deleteProductState == 0)
                    {
                        updateProductsCache(productIds, productNames, productPrices, productQuantities, 4);
                        cout << endl
                             << "The specified product has been deleted." << endl
                             << "ID: " << productId << endl
                             << "Name: " << oldName << endl
                             << "Price: " << oldPrice << "$" << endl
                             << "Quantity: " << oldQuantity << endl
                             << endl;

                        cout << "Press any key to go back...";
                        getch();
                        continue;
                    }
                    else
                    {
                        handleError(deleteProductState);
                        continue;
                    }
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

int deleteProduct(int id)
{
    ifstream originalFile(productFilePath);
    if (!originalFile.is_open())
    {
        return -30;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open())
    {
        originalFile.close();
        return -30;
    }

    bool lineIsHeader = true;
    string line;
    while (getline(originalFile, line))
    {
        if (lineIsHeader)
        {
            tempFile << line << endl;
            lineIsHeader = false;
            continue;
        }
        string attributeString;
        for (int i = 0; i < line.size(); i++)
        {
            char ch = line[i];
            if (ch != ';') // We break on the first semicolon, attributeString atp consists of our id
            {
                attributeString += ch;
            }
            else
            {
                break;
            }
        }

        try
        {
            int currentId = stoi(attributeString);
            if (currentId != id)
            {
                tempFile << line << endl;
            }
        }
        catch (const invalid_argument &e)
        {
            return -21; // Error code for invalid data type in file
        }
        catch (const out_of_range &e)
        {
            return -50; // Error code for range overflow
        }
    }

    originalFile.close();
    tempFile.close();

    remove(productFilePath.c_str());
    rename("temp.txt", productFilePath.c_str());

    return 0;
}

int updateProduct(int id, string name, float price, int quantity)
{
    ifstream originalFile(productFilePath);
    if (!originalFile.is_open())
    {
        return -30;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open())
    {
        originalFile.close();
        return -30;
    }

    bool lineIsHeader = true;
    string line;
    while (getline(originalFile, line))
    {
        if (lineIsHeader)
        {
            tempFile << line << endl;
            lineIsHeader = false;
            continue;
        }
        string attributeString;
        for (int i = 0; i < line.size(); i++)
        {
            char ch = line[i];
            if (ch != ';') // We break on the first semicolon, attributeString atp consists of our id
            {
                attributeString += ch;
            }
            else
            {
                break;
            }
        }

        try
        {
            int currentId = stoi(attributeString);
            if (currentId == id)
            {
                tempFile << id << ";" << name << ";" << price << ";" << quantity << ";" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }
        catch (const invalid_argument &e)
        {
            return -21; // Error code for invalid data type in file
        }
        catch (const out_of_range &e)
        {
            return -50; // Error code for range overflow
        }
    }

    originalFile.close();
    tempFile.close();

    remove(productFilePath.c_str());
    rename("temp.txt", productFilePath.c_str());

    return 0;
}

int addProduct(int id, string name, float price, int quantity)
{
    ofstream file(productFilePath, ios::app);
    if (!file.is_open())
    {
        return -30;
    }

    file << id << ";" << name << ";" << price << ";" << quantity << ";" << endl;
    file.close();

    return 0;
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
    if (code == -10)
    {
        clearConsole();
        cout << "The product with the specified ID does not exist." << endl;
        getch();
    }
    else if (code == -20)
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
            input = round(input * scale) / scale;
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

int getRandomInt(int min, int max)
{
    if (min > max)
        return -1;

    return min + rand() % (max - min + 1);
}

void clearConsole()
{
    system("cls"); // Only works on windows
}