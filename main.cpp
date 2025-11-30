#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <conio.h>
#include <ctime>
#include <iomanip>

using namespace std;

const int CACHE_SIZE = 100; // number of products/sales stored in arrays
const int NAME_LIMIT = 32;
const string productFilePath = "products.txt";

const double DOUBLE_MAX = numeric_limits<double>::max();

struct Product
{
    string name;
    int id;
    double price;
    int quantity;
};

int handleAddProduct(Product products[], int productsCount);
int handleUpdateProduct(Product products[], int productsCount);
int handleDeleteProduct(Product products[], int productsCount);

int handleViewProducts(Product products[], int productsCount);
int handleSearchById(Product products[], int productsCount);
int handleSearchByName(Product products[], int productsCount);

int addProduct(Product products[], int &productsCount, Product newProduct);
int updateProduct(Product products[], int productsCount, int searchId, double price, int quantity);
int deleteProduct(Product products[], int &productsCount, int searchId);

int saveProductsData(Product products[], int productsCount);
int loadProductsData(Product products[], int &productsCount);

void handleError(int code);
void clearConsole();
void getString(string &s);
bool getDouble(double &input, double rangeStart, double rangeEnd);
bool getInt(int &input, int rangeStart, int rangeEnd);

int getRandomInt(int min, int max);
string toLowerString(string s);

int main()
{
    srand(time(0)); // Helpful for random number gen

    Product products[CACHE_SIZE];
    int productsCount = 0;

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
            while (true)
            {
                loadProductsData(products, productsCount);
                clearConsole();
                int productMenuChoice = 0;

                cout << "1. Add Product" << endl
                     << "2. Edit Product" << endl
                     << "3. Delete Product" << endl
                     << "4. Go Back" << endl
                     << endl;

                cout << "Enter your choice: ";
                if (!getInt(productMenuChoice, 1, 5))
                    continue;

                if (productMenuChoice == 1)
                {
                    int addProductState = handleAddProduct(products, productsCount);
                    if (addProductState != 0)
                    {
                        handleError(addProductState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (productMenuChoice == 2)
                {
                    int updateProductState = handleUpdateProduct(products, productsCount);
                    if (updateProductState != 0)
                    {
                        handleError(updateProductState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (productMenuChoice == 3)
                {
                    int deleteProductState = handleDeleteProduct(products, productsCount);
                    if (deleteProductState != 0)
                    {
                        handleError(deleteProductState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
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
            while (true)
            {
                loadProductsData(products, productsCount);
                clearConsole();
                int inventoryMenuChoice = 0;

                cout << "1. View Available Stock" << endl
                     << "2. Search by ID" << endl
                     << "3. Search by Name" << endl
                     << "4. Go Back" << endl
                     << endl;

                cout << "Enter your choice: ";
                if (!getInt(inventoryMenuChoice, 1, 4))
                    continue;

                if (inventoryMenuChoice == 1)
                {
                    int viewProductsState = handleViewProducts(products, productsCount);
                    if (viewProductsState != 0)
                    {
                        handleError(viewProductsState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (inventoryMenuChoice == 2)
                {
                    int searchIdState = handleSearchById(products, productsCount);
                    if (searchIdState != 0)
                    {
                        handleError(searchIdState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (inventoryMenuChoice == 3)
                {
                    int searchNameState = handleSearchByName(products, productsCount);
                    if (searchNameState != 0)
                    {
                        handleError(searchNameState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (inventoryMenuChoice == 4)
                {
                    break;
                }
            }
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

int handleAddProduct(Product products[], int productsCount)
{
    Product newProduct;
    clearConsole();

    cout << "Enter Product Details" << endl;

    cout << left << setw(12) << "Name: ";
    getString(newProduct.name);

    if (newProduct.name.size() <= 3 || newProduct.name.size() > 32)
    {
        return -20;
    }

    cout << left << setw(12) << "Price($): ";
    if (!getDouble(newProduct.price, 0.00, DOUBLE_MAX))
    {
        return -20;
    }

    cout << left << setw(12) << "Qnty.: ";
    if (!getInt(newProduct.quantity, 0, INT_MAX))
    {
        return -20;
    }

    newProduct.id = getRandomInt(99999, 999999);

    int newProductState = addProduct(products, productsCount, newProduct);
    if (newProductState == 0)
    {
        saveProductsData(products, productsCount);
        cout << endl
             << "A new product has been entered into the system." << endl;

        cout << left << setw(12) << "ID: ";
        cout << newProduct.id << endl;

        cout << left << setw(12) << "Name: ";
        cout << newProduct.name << endl;

        cout << left << setw(12) << "Price($): ";
        cout << newProduct.price << endl;

        cout << left << setw(12) << "Qnty.: ";
        cout << newProduct.quantity << endl;
    }
    cout << endl;

    return newProductState;
}

int handleUpdateProduct(Product products[], int productsCount)
{
    Product oldProduct;
    int searchId;
    clearConsole();

    cout << "Enter Product Details" << endl;
    cout << left << setw(12) << "ID: ";

    if (!getInt(searchId, 99999, 999999))
    {
        return -20;
    }

    bool found = false;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id == searchId)
        {
            oldProduct.id = products[i].id;
            oldProduct.name = products[i].name;
            oldProduct.quantity = products[i].quantity;
            oldProduct.price = products[i].price;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return -10;
    }

    int newProductQuantity;
    double newProductPrice;

    cout << endl
         << endl
         << "Enter Updated Details for Product " << searchId << endl;

    cout << left << setw(12) << "Price($): ";
    if (!getDouble(newProductPrice, 0.00, DOUBLE_MAX))
    {
        return -20;
    }

    cout << left << setw(12) << "Qnty.: ";
    if (!getInt(newProductQuantity, 0, INT_MAX))
    {
        return -20;
    }

    int updateProductState = updateProduct(products, productsCount, searchId, newProductPrice, newProductQuantity);
    if (updateProductState == 0)
    {
        saveProductsData(products, productsCount);

        cout << endl
             << "The following product has been updated." << endl;

        cout << left << setw(12) << "ID: ";
        cout << oldProduct.id << endl;

        cout << left << setw(12) << "Name: ";
        cout << oldProduct.name << endl;

        cout << left << setw(12) << "Price($): ";
        cout << fixed << setprecision(2) << oldProduct.price << " -> " << newProductPrice << endl;

        cout << left << setw(12) << "Qnty.: ";
        cout << oldProduct.quantity << " -> " << newProductQuantity << endl;
    }

    return updateProductState;
}

int handleDeleteProduct(Product products[], int productsCount)
{
    int productId, oldQuantity;
    string oldName;
    double oldPrice;
    clearConsole();

    cout << "Enter Product Details" << endl;

    cout << left << setw(12) << "ID: ";
    if (!getInt(productId, 99999, 999999))
    {
        return -20;
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
        return -10;
    }

    int deleteProductState = deleteProduct(products, productsCount, productId);
    if (deleteProductState == 0)
    {
        saveProductsData(products, productsCount);

        cout << endl
             << "The following product has been removed from the system." << endl;

        cout << left << setw(12) << "ID: ";
        cout << productId << endl;

        cout << left << setw(12) << "Name: ";
        cout << oldName << endl;

        cout << left << setw(12) << "Price($): ";
        cout << fixed << setprecision(2) << oldPrice << endl;

        cout << left << setw(12) << "Qnty.: ";
        cout << oldQuantity << endl;
    }

    return deleteProductState;
}

int handleViewProducts(Product products[], int productsCount)
{
    clearConsole();

    if (productsCount <= 0)
    {
        return -10;
    }

    cout << "Here are all the stored products: " << endl
         << endl;

    cout << left << setw(8) << "No.";
    cout << left << setw(8) << "ID";
    cout << left << setw(40) << "Name";
    cout << left << fixed << setprecision(2) << setw(12) << "Price($)";
    cout << left << setw(6) << "Qnty.";
    cout << left << fixed << setprecision(2) << setw(12) << "Value($)";
    cout << endl;

    for (int i = 0; i < productsCount; i++)
    {
        cout << left << setw(4) << "[" << (i + 1) << "]. ";
        cout << left << setw(8) << products[i].id;
        cout << left << setw(40) << products[i].name;
        cout << left << fixed << setprecision(2) << setw(12) << products[i].price;
        cout << left << setw(6) << products[i].quantity;
        cout << left << fixed << setprecision(2) << setw(12) << (products[i].price * products[i].quantity);
        cout << endl;
    }
    cout << endl;

    return 0;
}

int handleSearchById(Product products[], int productsCount)
{
    clearConsole();

    int searchId;
    cout << "Enter Product Details" << endl;

    cout << left << setw(12) << "ID: ";
    if (!getInt(searchId, 99999, 999999))
    {
        return -20;
    }

    int index = -1;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id == searchId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return -10;
    }

    cout << "Search Result: " << endl
         << endl;

    cout << left << setw(12) << "ID: ";
    cout << products[index].id << endl;

    cout << left << setw(12) << "Name: ";
    cout << products[index].name << endl;

    cout << left << setw(12) << "Price($): ";
    cout << fixed << setprecision(2) << products[index].price << endl;

    cout << left << setw(12) << "Qnty.: ";
    cout << products[index].quantity << endl;

    return 0;
}

int handleSearchByName(Product products[], int productsCount)
{
    clearConsole();

    string searchName;
    cout << "Enter Product Details" << endl;

    cout << left << setw(12) << "Name: ";
    getString(searchName);

    if (searchName.size() <= 3 || searchName.size() > 32)
    {
        return -20;
    }

    int index = -1;
    for (int i = 0; i < productsCount; i++)
    {
        if (toLowerString(products[i].name) == toLowerString(searchName))
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return -10;
    }

    cout << "Search Result: " << endl
         << endl;

    cout << left << setw(12) << "ID: ";
    cout << products[index].id << endl;

    cout << left << setw(12) << "Name: ";
    cout << products[index].name << endl;

    cout << left << setw(12) << "Price($): ";
    cout << fixed << setprecision(2) << products[index].price << endl;

    cout << left << setw(12) << "Qnty.: ";
    cout << products[index].quantity << endl;

    return 0;
}

int deleteProduct(Product products[], int &productsCount, int searchId)
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

    for (int i = 0; i < productsCount; i++)
    {
        products[i] = temp[i];
    }

    return 0;
}

int updateProduct(Product products[], int productsCount, int searchId, double price, int quantity)
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
        return -10;
    }

    products[index].price = (price < 0) ? oldPrice : price;
    products[index].quantity = (quantity < 0) ? oldQty : quantity;

    return 0;
}

int addProduct(Product products[], int &productsCount, Product newProduct)
{
    deleteProduct(products, productsCount, newProduct.id); // overwrite existing products if the id is same

    products[productsCount] = newProduct;
    productsCount++;

    return 0;
}

int saveProductsData(Product products[], int productsCount)
{
    ofstream productFile(productFilePath, ios::out); // overwrites all data, prevents corruption
    if (!productFile.is_open())
    {
        return -30;
    }

    productFile << "ID;Name;Price;Quantity;" << endl;
    for (int i = 0; i < productsCount; i++)
    {
        productFile << products[i].id << ";" << products[i].name << ";" << products[i].price << ";" << products[i].quantity << ";" << endl;
    }

    productFile.close();

    return 0;
}

int loadProductsData(Product products[], int &productsCount)
{
    ifstream productFile(productFilePath, ios::in);
    if (!productFile.is_open())
    {
        return -30;
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

        char attrStr[100];
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

    productFile.close();

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return (input >= rangeStart && input <= rangeEnd);
    }
    else
    {
        cin.clear();                                         // ignores error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores invalid input
        return false;
    }
}

bool getDouble(double &input, double rangeStart, double rangeEnd)
{
    if (cin >> input)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return (input >= rangeStart && input <= rangeEnd);
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

string toLowerString(string s)
{
    string lowered = s;
    for (int i = 0; i < s.size(); i++)
    {
        lowered[i] = tolower(s[i]);
    }

    return lowered;
}