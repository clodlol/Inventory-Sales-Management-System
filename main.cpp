#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <conio.h>
#include <ctime>

using namespace std;

const int CACHE_SIZE = 100; // number of products/sales stored in arrays
const int NAME_LIMIT = 32;
const string productFilePath = "products.txt";

int addProduct(Product allProducts[], Product newProduct);

int updateProduct(Product products[], int searchId, string name, double price, int quantity);
int updateProduct(Product products[], int searchId, double price, int quantity);
int updateProduct(Product products[], string searchName, double price, int quantity);

int deleteProduct(Product products[], int searchId);
int deleteProduct(Product products[], string searchName);

int saveProductsData(Product products[]);
int loadProductsData(Product products[]);

void handleError(int code);
void clearConsole();
void getString(string &s);
bool getFloat(float &input, int rangeStart, int rangeEnd, int precisionPoints);
bool getInt(int &input, int rangeStart, int rangeEnd);
int getRandomInt(int min, int max);

struct Product
{
    string name;
    int id;
    double price;
    int quantity;
};

int productsCount = 0;

int main()
{
    srand(time(0)); // Helpful for random number gen

    Product products[CACHE_SIZE];

    while (true)
    {
        clearConsole();
        int menuChoice = 0;

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
            loadProductsData(products);

            while (true)
            {
                clearConsole();
                int productMenuChoice = 0;

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
                    Product newProduct;
                    clearConsole();

                    cout << "Enter Product Details" << endl
                         << "Name: ";
                    getString(newProduct.name);

                    if (newProduct.name.size() <= 3 || newProduct.name.size() > 32)
                    {
                        handleError(-20);
                        continue;
                    }

                    cout << "Price: ";
                    if (!getFloat(newProduct.price, 0, INT_MAX, 2))
                    {
                        handleError(-20);
                        continue;
                    }

                    cout << "Quantity: ";
                    if (!getInt(newProduct.quantity, 0, INT_MAX))
                    {
                        handleError(-20);
                        continue;
                    }

                    newProduct.id = getRandomInt(99999, 999999);

                    int newProductState = addProduct(products, newProduct);
                    if (newProductState == 0)
                    {
                        saveProductsData(products);
                        cout << endl
                             << "A new product has been entered into the system." << endl
                             << "ID: " << newProduct.id << endl
                             << "Name: " << newProduct.name << endl
                             << "Price: " << newProduct.price << "$" << endl
                             << "Quantity: " << newProduct.quantity << endl
                             << endl;

                        cout << "Press any key to go back...";
                        getch();
                        continue;
                    }
                    else
                    {
                        handleError(newProductState);
                        continue;
                    }
                }
                else if (productMenuChoice == 2)
                {
                    Product oldProduct;
                    int searchId;
                    string searchName;
                    clearConsole();

                    cout << "Enter Product Details" << endl
                         << "ID: ";
                    if (!getInt(searchId, 99999, 999999))
                    {
                        handleError(-20);
                        continue;
                    }

                    bool found = false;
                    for (int i = 0; i < productsCount; i++)
                    {
                        if (products[i].id == searchId)
                        {
                            oldProduct.name = products[i].name;
                            oldProduct.quantity = products[i].quantity;
                            oldProduct.price = products[i].price;
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
                    double newProductPrice;

                    cout << endl
                         << endl
                         << "Enter updated details for product " << searchId << endl;
                    cout << "Name: ";
                    getString(newProductName);

                    if (newProductName.size() < 3 || newProductName.size() > NAME_LIMIT)
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

                    int updateProductState = updateProduct(products, searchId, newProductName, newProductPrice, newProductQuantity);
                    if (updateProductState == 0)
                    {
                        saveProductsData(products);
                        cout << endl
                             << "The specified product has been edited." << endl
                             << "ID: " << searchId << endl
                             << "Name: " << oldProduct.name << " -> " << newProductName << endl
                             << "Price: " << oldProduct.price << "$" << " -> " << newProductPrice << "$" << endl
                             << "Quantity: " << oldProduct.quantity<< " -> " << newProductQuantity << endl
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
                    double oldPrice;
                    clearConsole();

                    cout << "Enter Product Details" << endl
                         << "ID: ";
                    if (!getInt(productId, 99999, 999999))
                    {
                        handleError(-20);
                        continue;
                    }

                    bool found = false;
                    for (int i = 0; i < productsCount; i++)
                    {
                        if (products[i].id == productId)
                        {
                            oldName = products[i].name;
                            oldQuantity = products[i].quantity;
                            oldPrice = products[i].price;
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
                        saveProductsData(products);
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

int deleteProduct(Product products[], int searchId)
{
    Product temp[CACHE_SIZE];
    int tempCounter = 0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id != searchId)
        {
            temp[tempCounter] = products[i];
            tempCounter++;
        }
    }

    productsCount = tempCounter;

    return 0;
}

int deleteProduct(Product products[], string searchName)
{
    Product temp[CACHE_SIZE];
    int tempCounter = 0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].name != searchName)
        {
            temp[tempCounter] = products[i];
            tempCounter++;
        }
    }

    productsCount = tempCounter;

    return 0;
}

int updateProduct(Product products[], int searchId, string name, double price, int quantity)
{
    int index = -1, oldQty = 0;
    double oldPrice = 0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id == searchId)
        {
            index = i;
            oldPrice = products[i].price;
            oldQty = products[i].quantity;
            break;
        }
    }

    if (index == -1)
    {
        // error
    }

    products[index].name = name;
    products[index].price = (price < 0) ? oldPrice : price;
    products[index].quantity = (quantity < 0) ? oldQty : quantity;

    return 0;
}

int updateProduct(Product products[], int searchId, double price, int quantity)
{
    int index = -1, oldQty = 0;
    double oldPrice = 0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id == searchId)
        {
            index = i;
            oldPrice = products[i].price;
            oldQty = products[i].quantity;
            break;
        }
    }

    if (index == -1)
    {
        // error
    }

    products[index].price = (price < 0) ? oldPrice : price;
    products[index].quantity = (quantity < 0) ? oldQty : quantity;

    return 0;
}

int updateProduct(Product products[], string searchName, double price, int quantity)
{
    int index = -1, oldQty = 0;
    double oldPrice = 0;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].name == searchName)
        {
            index = i;
            oldPrice = products[i].price;
            oldQty = products[i].quantity;
            break;
        }
    }

    if (index == -1)
    {
        // error
    }

    products[index].price = (price < 0) ? oldPrice : price;
    products[index].quantity = (quantity < 0) ? oldQty : quantity;

    return 0;
}

int addProduct(Product products[], Product newProduct)
{
    // TODO prevent duplicates, since ids are random this is unlikely
    products[productsCount] = newProduct;
    productsCount++;
}

int saveProductsData(Product products[])
{
    ofstream productFile(productFilePath, ios::out);
    if (!productFile.is_open())
    {
        // error
    }

    productFile << "ID;Name;Price;Quantity;" << endl;
    for (int i = 0; i < productsCount; i++)
    {
        productFile << products[i].id << ";" << products[i].name << ";" << products[i].price << ";" << products[i].quantity << ";" << endl;
    }

    return 0;
}

int loadProductsData(Product products[])
{
    ifstream productFile(productFilePath, ios::in);
    if (!productFile.is_open())
    {
        // error
    }

    bool isHeader = true;
    string line;
    int productCounter = 0;
    while (getline(productFile, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        char attrStr[line.size()];
        int attrStrCounter = 0, attrCount = 0;
        for (int i = 0; i < line.size(); i++)
        {
            attrStr[attrStrCounter] = '\0';

            if (line[i] == ';')
            {
                if (attrCount == 0)
                {
                    products[productCounter].id = atoi(attrStr);
                }
                else if (attrCount == 1)
                {
                    products[productCounter].name = attrStr;
                }
                else if (attrCount == 2)
                {
                    products[productCounter].price = atof(attrStr);
                }
                else if (attrCount == 3)
                {
                    products[productCounter].quantity = atoi(attrStr);
                }

                attrStrCounter = 0;
                attrCount++;
            }
            else
            {
                attrStr[attrStrCounter] = line[i];
                attrStrCounter++;
            }
        }

        productCounter++;
    }

    productsCount = productCounter;
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

bool getFloat(double &input, int rangeStart, int rangeEnd, int precisionPoints)
{
    if (cin >> input)
    {

        if (input >= rangeStart && input <= rangeEnd)
        {
            double scale = pow(10.0, precisionPoints);
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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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