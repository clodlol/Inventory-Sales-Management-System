#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

const int CACHE_SIZE = 100; // number of products/sales stored in arrays
const int NAME_LIMIT = 32;
const string productFilePath = "products.txt";
const string salesFilePath = "sales.txt";

const double DOUBLE_MAX = numeric_limits<double>::max();

struct Product
{
    string name;
    int id;
    double price;
    int quantity;
};

struct Sale
{
    string productName;
    int productId;
    double price;
    int quantitySold;
    int saleId;
};

// Product Management Functions
int handleAddProduct(Product products[], int productsCount);
int handleUpdateProduct(Product products[], int productsCount);
int handleDeleteProduct(Product products[], int productsCount);

int handleViewProducts(Product products[], int productsCount);
int handleSearchById(Product products[], int productsCount);
int handleSearchByName(Product products[], int productsCount);

int handleRecordSale(Product products[], int &productsCount, Sale sales[], int &salesCount);
int handleViewSales(Sale sales[], int salesCount);
int handleSearchSaleById(Sale sales[], int salesCount);

int handleDisplayAllSales(Sale sales[], int salesCount);

int handleTotalRevenue(Sale sales[], int salesCount);
int handleTopSellingProducts(Sale sales[], int salesCount);

int addProduct(Product products[], int &productsCount, Product newProduct);
int updateProduct(Product products[], int productsCount, int searchId, double price, int quantity);
int deleteProduct(Product products[], int &productsCount, int searchId);

int saveProductsData(Product products[], int productsCount);
int loadProductsData(Product products[], int &productsCount);

int recordSale(Product products[], int &productsCount, Sale sales[], int &salesCount, int productId, int quantitySold);

int saveSalesData(Sale sales[], int salesCount);
int loadSalesData(Sale sales[], int &salesCount);

// Utility Functions
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

    Sale sales[CACHE_SIZE];
    int salesCount = 0;

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
            while (true)
            {
                loadProductsData(products, productsCount);
                loadSalesData(sales, salesCount);
                clearConsole();
                int salesMenuChoice = 0;

                cout << "1. Record a Sale" << endl
                     << "2. View All Sales" << endl
                     << "3. Search Sale by ID" << endl
                     << "4. Go Back" << endl
                     << endl;

                cout << "Enter your choice: ";
                if (!getInt(salesMenuChoice, 1, 4))
                    continue;

                if (salesMenuChoice == 1)
                {
                    int recordSaleState = handleRecordSale(products, productsCount, sales, salesCount);
                    if (recordSaleState != 0)
                    {
                        handleError(recordSaleState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (salesMenuChoice == 2)
                {
                    int viewSalesState = handleViewSales(sales, salesCount);
                    if (viewSalesState != 0)
                    {
                        handleError(viewSalesState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (salesMenuChoice == 3)
                {
                    int searchSaleState = handleSearchSaleById(sales, salesCount);
                    if (searchSaleState != 0)
                    {
                        handleError(searchSaleState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (salesMenuChoice == 4)
                {
                    break;
                }
            }
        }
        else if (menuChoice == 4)
        {
            while (true)
            {
                loadSalesData(sales, salesCount);
                clearConsole();
                
                int reportsMenuChoice = 0;

                cout << "Reports & Statistics" << endl
                     << "1. Display All Sales" << endl
                     << "2. Show Top-Selling Products" << endl
                     << "3. Display Total Revenue Generated" << endl
                     << "4. Go Back" << endl
                     << endl;

                cout << "Enter your choice: ";
                if (!getInt(reportsMenuChoice, 1, 4))
                    continue;

                if (reportsMenuChoice == 1)
                {
                    int displaySalesState = handleDisplayAllSales(sales, salesCount);
                    if (displaySalesState != 0)
                    {
                        handleError(displaySalesState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (reportsMenuChoice == 2)
                {
                    int topSellingState = handleTopSellingProducts(sales, salesCount);
                    if (topSellingState != 0)
                    {
                        handleError(topSellingState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (reportsMenuChoice == 3)
                {
                    int revenueState = handleTotalRevenue(sales, salesCount);
                    if (revenueState != 0)
                    {
                        handleError(revenueState);
                    }
                    else
                    {
                        cout << "Press any key to go back...";
                        getch();
                    }
                }
                else if (reportsMenuChoice == 4)
                {
                    break;
                }
            }
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
    if (!getInt(newProduct.quantity, 0, 9999999))
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
    if (!getInt(newProductQuantity, 0, 9999999))
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
        return -10; //Product not found
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
        return -30; //File handling error
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
        return -30; //File handling error
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

        char attrStr[1000];
        int attrStrCounter = 0, attrCount = 0;
        for (int i = 0; i < line.size(); i++)
        {

            if (line[i] == ';')
            {
                attrStr[attrStrCounter] = '\0';
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

int handleRecordSale(Product products[], int &productsCount, Sale sales[], int &salesCount)
{
    int productId, quantitySold;
    clearConsole();

    cout << "Record a Sale" << endl
         << endl;

    cout << left << setw(20) << "Product ID: ";
    if (!getInt(productId, 99999, 999999))
    {
        return -20;
    }

    int productIndex = -1;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id == productId)
        {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1)
    {
        return -10; // Product not found
    }

    cout << endl
         << "Product Found:" << endl;
    cout << left << setw(20) << "Name: " << products[productIndex].name << endl;
    cout << left << setw(20) << "Price($): " << fixed << setprecision(2) << products[productIndex].price << endl;
    cout << left << setw(20) << "Available Stock: " << products[productIndex].quantity << endl;
    cout << endl;

    cout << left << setw(20) << "Quantity to Sell: ";
    if (!getInt(quantitySold, 1, 9999999))
    {
        return -20; //Invalid Input
    }

    if (quantitySold > products[productIndex].quantity)
    {
        return -40; // Insufficient stock
    }

    int recordSaleState = recordSale(products, productsCount, sales, salesCount, productId, quantitySold);

    if (recordSaleState == 0)
    {
        double totalBill = products[productIndex].price * quantitySold;

        cout << endl
             << "Sale Recorded Successfully!" << endl
             << endl;
        cout << left << setw(20) << "Sale ID: " << sales[salesCount - 1].saleId << endl;
        cout << left << setw(20) << "Product: " << sales[salesCount - 1].productName << endl;
        cout << left << setw(20) << "Quantity Sold: " << quantitySold << endl;
        cout << left << setw(20) << "Unit Price($): " << fixed << setprecision(2) << sales[salesCount - 1].price << endl;
        cout << left << setw(20) << "Total Bill($): " << fixed << setprecision(2) << totalBill << endl;
        cout << left << setw(20) << "Remaining Stock: " << products[productIndex].quantity << endl;
        cout << endl;
    }

    return recordSaleState;
}

int handleViewSales(Sale sales[], int salesCount)
{
    clearConsole();

    if (salesCount <= 0)
    {
        return -10;
    }

    cout << "All Recorded Sales:" << endl
         << endl;

    cout << left << setw(8) << "No.";
    cout << left << setw(10) << "Sale ID";
    cout << left << setw(10) << "Prod. ID";
    cout << left << setw(30) << "Product Name";
    cout << left << setw(12) << "Price($)";
    cout << left << setw(10) << "Qty Sold";
    cout << left << setw(12) << "Total($)";
    cout << endl;

    double grandTotal = 0.0;

    for (int i = 0; i < salesCount; i++)
    {
        double saleTotal = sales[i].price * sales[i].quantitySold;
        grandTotal += saleTotal;

        cout << left << setw(4) << "[" << (i + 1) << "]. ";
        cout << left << setw(10) << sales[i].saleId;
        cout << left << setw(10) << sales[i].productId;
        cout << left << setw(30) << sales[i].productName;
        cout << left << fixed << setprecision(2) << setw(12) << sales[i].price;
        cout << left << setw(10) << sales[i].quantitySold;
        cout << left << fixed << setprecision(2) << setw(12) << saleTotal;
        cout << endl;
    }

    cout << endl;
    cout << left << setw(70) << "Grand Total: ";
    cout << "$" << fixed << setprecision(2) << grandTotal << endl;
    cout << endl;

    return 0;
}

int handleSearchSaleById(Sale sales[], int salesCount)
{
    clearConsole();

    int searchSaleId;
    cout << "Search Sale by ID" << endl
         << endl;

    cout << left << setw(12) << "Sale ID: ";
    if (!getInt(searchSaleId, 99999, 999999))
    {
        return -20; //Invalid input
    }

    int index = -1;
    for (int i = 0; i < salesCount; i++)
    {
        if (sales[i].saleId == searchSaleId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return -10; //Specified product not found.
    }

    double totalBill = sales[index].price * sales[index].quantitySold;

    cout << endl
         << "Sale Found:" << endl
         << endl;

    cout << left << setw(20) << "Sale ID: " << sales[index].saleId << endl;
    cout << left << setw(20) << "Product ID: " << sales[index].productId << endl;
    cout << left << setw(20) << "Product Name: " << sales[index].productName << endl;
    cout << left << setw(20) << "Price($): " << fixed << setprecision(2) << sales[index].price << endl;
    cout << left << setw(20) << "Quantity Sold: " << sales[index].quantitySold << endl;
    cout << left << setw(20) << "Total Bill($): " << fixed << setprecision(2) << totalBill << endl;
    cout << endl;

    return 0;
}

int recordSale(Product products[], int &productsCount, Sale sales[], int &salesCount, int productId, int quantitySold)
{
    int productIndex = -1;
    for (int i = 0; i < productsCount; i++)
    {
        if (products[i].id == productId)
        {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1)
    {
        return -10; // Product not found
    }

    if (quantitySold > products[productIndex].quantity)
    {
        return -40; // Insufficient stock
    }

    Sale newSale;
    newSale.saleId = getRandomInt(99999, 999999);
    newSale.productId = productId;
    newSale.productName = products[productIndex].name;
    newSale.price = products[productIndex].price;
    newSale.quantitySold = quantitySold;

    sales[salesCount] = newSale;
    salesCount++;

    products[productIndex].quantity -= quantitySold;

    saveProductsData(products, productsCount);
    saveSalesData(sales, salesCount);

    return 0;
}

int saveSalesData(Sale sales[], int salesCount)
{
    ofstream salesFile(salesFilePath, ios::out);
    if (!salesFile.is_open())
    {
        return -30; // File handling error
    }

    salesFile << "SaleID;ProductID;ProductName;Price;QuantitySold;" << endl;
    for (int i = 0; i < salesCount; i++)
    {
        salesFile << sales[i].saleId << ";"
                  << sales[i].productId << ";"
                  << sales[i].productName << ";"
                  << sales[i].price << ";"
                  << sales[i].quantitySold << ";" << endl;
    }

    salesFile.close();

    return 0;
}

int loadSalesData(Sale sales[], int &salesCount)
{
    ifstream salesFile(salesFilePath, ios::in);
    if (!salesFile.is_open())
    {
        return -30;
    }

    bool isHeader = true;
    string line;
    int saleCounter = 0;

    while (getline(salesFile, line))
    {
        if (isHeader)
        {
            isHeader = false;
            continue;
        }

        char attrStr[1000];
        int attrStrCounter = 0, attrCount = 0;

        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ';')
            {
                attrStr[attrStrCounter] = '\0';
                if (attrCount == 0)
                {
                    sales[saleCounter].saleId = atoi(attrStr);
                }
                else if (attrCount == 1)
                {
                    sales[saleCounter].productId = atoi(attrStr);
                }
                else if (attrCount == 2)
                {
                    sales[saleCounter].productName = attrStr;
                }
                else if (attrCount == 3)
                {
                    sales[saleCounter].price = atof(attrStr);
                }
                else if (attrCount == 4)
                {
                    sales[saleCounter].quantitySold = atoi(attrStr);
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

        saleCounter++;
    }

    salesCount = saleCounter;
    salesFile.close();

    return 0;
}

int handleDisplayAllSales(Sale sales[], int salesCount)
{
    clearConsole();

    if (salesCount <= 0)
    {
        return -10; //No sales found
    }

    cout << "SALES REPORT" << endl
         << endl;

    cout << left << setw(8) << "No.";
    cout << left << setw(10) << "Sale ID";
    cout << left << setw(10) << "Prod. ID";
    cout << left << setw(30) << "Product Name";
    cout << left << setw(12) << "Price($)";
    cout << left << setw(10) << "Qty Sold";
    cout << left << setw(12) << "Total($)";
    cout << endl;
    cout << endl;

    double grandTotal = 0.0;
    int totalQuantitySold = 0;

    for (int i = 0; i < salesCount; i++)
    {
        double saleTotal = sales[i].price * sales[i].quantitySold;
        grandTotal += saleTotal;
        totalQuantitySold += sales[i].quantitySold;

        cout << left << setw(4) << "[" << (i + 1) << "]. ";
        cout << left << setw(10) << sales[i].saleId;
        cout << left << setw(10) << sales[i].productId;
        cout << left << setw(30) << sales[i].productName;
        cout << left << fixed << setprecision(2) << setw(12) << sales[i].price;
        cout << left << setw(10) << sales[i].quantitySold;
        cout << left << fixed << setprecision(2) << setw(12) << saleTotal;
        cout << endl;
    }

    cout << endl;
    cout << left << setw(60) << "Total Sales Count: " << salesCount << endl;
    cout << left << setw(60) << "Total Items Sold: " << totalQuantitySold << endl;
    cout << left << setw(60) << "Grand Total Revenue: ";
    cout << "$" << fixed << setprecision(2) << grandTotal << endl;
    cout << endl;

    return 0;
}

int handleTopSellingProducts(Sale sales[], int salesCount)
{
    clearConsole();

    if (salesCount <= 0)
    {
        return -10; //Not found
    }

    struct ProductSummary
    {
        string productName;
        int productId;
        int totalQuantitySold;
        double totalRevenue;
    };

    ProductSummary summary[CACHE_SIZE];
    int summaryCount = 0;

    for (int i = 0; i < salesCount; i++)
    {
        bool found = false;
        for (int j = 0; j < summaryCount; j++)
        {
            if (summary[j].productId == sales[i].productId)
            {
                summary[j].totalQuantitySold += sales[i].quantitySold;
                summary[j].totalRevenue += (sales[i].price * sales[i].quantitySold);
                found = true;
                break;
            }
        }

        if (!found)
        {
            summary[summaryCount].productId = sales[i].productId;
            summary[summaryCount].productName = sales[i].productName;
            summary[summaryCount].totalQuantitySold = sales[i].quantitySold;
            summary[summaryCount].totalRevenue = sales[i].price * sales[i].quantitySold;
            summaryCount++;
        }
    }

    for (int i = 0; i < summaryCount - 1; i++)
    {
        for (int j = 0; j < summaryCount - i - 1; j++)
        {
            if (summary[j].totalQuantitySold < summary[j + 1].totalQuantitySold)
            {
                ProductSummary temp = summary[j];
                summary[j] = summary[j + 1];
                summary[j + 1] = temp;
            }
        }
    }

    cout << "TOP-SELLING PRODUCTS" << endl
         << endl;

    cout << left << setw(6) << "Rank";
    cout << left << setw(10) << "Prod. ID";
    cout << left << setw(35) << "Product Name";
    cout << left << setw(15) << "Qty Sold";
    cout << left << setw(15) << "Revenue($)";
    cout << endl;
    cout << endl;

    for (int i = 0; i < summaryCount; i++)
    {
        cout << left << setw(6) << (i + 1);
        cout << left << setw(10) << summary[i].productId;
        cout << left << setw(35) << summary[i].productName;
        cout << left << setw(15) << summary[i].totalQuantitySold;
        cout << left << fixed << setprecision(2) << setw(15) << summary[i].totalRevenue;
        cout << endl;
    }

    cout << endl;

    if (summaryCount > 0)
    {
        cout << "TOP SELLER: " << summary[0].productName 
             << " (Sold: " << summary[0].totalQuantitySold << " units)" << endl;
    }

    cout << endl;

    return 0;
}

int handleTotalRevenue(Sale sales[], int salesCount)
{
    clearConsole();

    if (salesCount <= 0)
    {
        return -10; //Not found
    }

    cout << "REVENUE REPORT" << endl
         << endl;

    double totalRevenue = 0.0;
    int totalItemsSold = 0;
    int totalTransactions = salesCount;

    for (int i = 0; i < salesCount; i++)
    {
        totalRevenue += (sales[i].price * sales[i].quantitySold);
        totalItemsSold += sales[i].quantitySold;
    }

    double averageTransactionValue = totalRevenue / totalTransactions;
    double averageItemPrice = totalRevenue / totalItemsSold;

    cout << left << setw(35) << "Total Transactions: " << totalTransactions << endl;
    cout << left << setw(35) << "Total Items Sold: " << totalItemsSold << endl;
    cout << left << setw(35) << "Total Revenue Generated: " 
         << "$" << fixed << setprecision(2) << totalRevenue << endl;
    cout << endl;
    cout << left << setw(35) << "Average Transaction Value: " 
         << "$" << fixed << setprecision(2) << averageTransactionValue << endl;
    cout << left << setw(35) << "Average Item Price: " 
         << "$" << fixed << setprecision(2) << averageItemPrice << endl;
    cout << endl;

    double highestRevenue = 0.0;
    double lowestRevenue = DOUBLE_MAX;
    int highestIndex = 0;
    int lowestIndex = 0;

    for (int i = 0; i < salesCount; i++)
    {
        double saleRevenue = sales[i].price * sales[i].quantitySold;
        if (saleRevenue > highestRevenue)
        {
            highestRevenue = saleRevenue;
            highestIndex = i;
        }
        if (saleRevenue < lowestRevenue)
        {
            lowestRevenue = saleRevenue;
            lowestIndex = i;
        }
    }

    cout << "TRANSACTION HIGHLIGHTS" << endl
         << endl;
    cout << "Highest Revenue Transaction:" << endl;
    cout << "Sale ID: " << sales[highestIndex].saleId << endl;
    cout << "Product: " << sales[highestIndex].productName << endl;
    cout << "Revenue($): " << fixed << setprecision(2) << highestRevenue << endl;
    cout << endl;

    cout << "Lowest Revenue Transaction:" << endl;
    cout << "Sale ID: " << sales[lowestIndex].saleId << endl;
    cout << "Product: " << sales[lowestIndex].productName << endl;
    cout << "Revenue($): " << fixed << setprecision(2) << lowestRevenue << endl;
    cout << endl;

    return 0;
}

void handleError(int code)
{
    if (code == -10)
    {
        clearConsole();
        cout << "Specified product(s) do not exist." << endl;
        getch();
    }
    else if (code == -20)
    {
        clearConsole();
        cout << "Invalid input given." << endl;
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
        cout << "Error occurred while reading/writing data files." << endl;
        getch();
    }
    else if (code == -40)
    {
        clearConsole();
        cout << "Insufficient stock! Cannot sell more than available quantity." << endl;
        getch();
    }
    else if (code == -50)
    {
        clearConsole();
        cout << "Data written to unallocated memory." << endl;
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
    system("cls");
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