#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct MenuItem {
    int itemCode;
    string itemName;
    double price;
    int quantityAvailable;
};


void loadMenu(vector<MenuItem>& menu, const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Error opening file for reading or file does not exist.\n";
        return;
    }

    size_t menuSize;
    inFile.read(reinterpret_cast<char*>(&menuSize), sizeof(menuSize));

    menu.clear();  

    for (size_t i = 0; i < menuSize; ++i) {
        MenuItem item;
        inFile.read(reinterpret_cast<char*>(&item), sizeof(MenuItem));
        menu.push_back(item);
    }

    inFile.close();
    cout << "Menu loaded successfully from file.\n";
}


void saveMenu(const vector<MenuItem>& menu, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    size_t menuSize = menu.size();
    outFile.write(reinterpret_cast<const char*>(&menuSize), sizeof(menuSize));

    for (const auto& item : menu) {
        outFile.write(reinterpret_cast<const char*>(&item), sizeof(MenuItem));
    }

    outFile.close();
    cout << "Menu saved successfully to file.\n";
}


void displayMenu(const vector<MenuItem>& menu) {
    cout << "\nRestaurant Menu:\n";
    cout << "Item Code\tItem Name\tPrice\tQuantity Available\n";
    for (const auto& item : menu) {
        cout << item.itemCode << "\t\t" << item.itemName << "\t" << item.price << "\t" << item.quantityAvailable << endl;
    }
}


double placeOrder(vector<MenuItem>& menu) {
    int itemCode, quantity;
    double totalBill = 0;

    cout << "Enter the Item Code to order: ";
    cin >> itemCode;

    bool itemFound = false;
    for (auto& item : menu) {
        if (item.itemCode == itemCode) {
            itemFound = true;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity > item.quantityAvailable) {
                cout << "Sorry, only " << item.quantityAvailable << " items are available.\n";
                return totalBill;
            }

            item.quantityAvailable -= quantity;
            totalBill += item.price * quantity;
            cout << "Order placed: " << item.itemName << " x" << quantity << " for $" << item.price * quantity << endl;
            break;
        }
    }

    if (!itemFound) {
        cout << "Item with code " << itemCode << " not found.\n";
    }

    return totalBill;
}


void displayBill(double totalBill) {
    cout << "\nTotal Bill: $" << totalBill << endl;
    cout << "Thank you for your order!\n";
}

int main() {
    vector<MenuItem> menu;
    string filename = "menu_data.dat";
    double totalBill = 0;

    
    loadMenu(menu, filename);

    while (true) {
        int choice;
        cout << "\nRestaurant Order Management System\n";
        cout << "1. View Menu\n";
        cout << "2. Place an Order\n";
        cout << "3. View Bill\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                totalBill += placeOrder(menu);  
            case 3:
                displayBill(totalBill);
                break;
            case 4:
               
                saveMenu(menu, filename);
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
