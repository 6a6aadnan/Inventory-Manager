#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

struct ComputerHardware {
    string type;
    string model;
    int quantity;
    float price;

    // Define operator< to facilitate sorting by model
    bool operator<(const ComputerHardware& other) const {
        return model < other.model;
    }
};

class Inventory {
private:
    vector<ComputerHardware> hardwareList;
    string filename;

    void saveInventory() {
        try {
            ofstream file(filename);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for saving.");
            }
            for (const auto& hardware : hardwareList) {
                file << hardware.type << "," << hardware.model << "," << hardware.quantity << "," << hardware.price << endl;
            }
            file.close(); // Close the file after saving
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    bool isModelUnique(const string& model) const {
        auto it = find_if(hardwareList.begin(), hardwareList.end(), [&](const ComputerHardware& hardware) {
            return hardware.model == model;
        });
        return it == hardwareList.end();
    }

public:
    Inventory(const string& filename) : filename(filename) {
        loadInventory();
    }

    void addHardware(const ComputerHardware& newHardware) {
        if (newHardware.quantity < 0 || newHardware.price < 0) {
            cerr << "Error: Quantity and price must be non-negative." << endl;
            return;
        }

        if (!isModelUnique(newHardware.model)) {
            cerr << "Error: Hardware with model " << newHardware.model << " already exists in the inventory." << endl;
            return;
        }

        hardwareList.push_back(newHardware);
        // Sort hardwareList after adding
        sort(hardwareList.begin(), hardwareList.end());
        saveInventory();
    }

    void removeHardware(const string& model) {
        auto it = find_if(hardwareList.begin(), hardwareList.end(), [&](const ComputerHardware& hardware) {
            return hardware.model == model;
        });
        if (it != hardwareList.end()) {
            hardwareList.erase(it);
            cout << "Hardware " << model << " removed from inventory." << endl;
            saveInventory();
        } else {
            cout << "Hardware not found in inventory." << endl;
        }
    }

    void searchHardware(const string& model) {
        string lowercaseModel = model;
        transform(lowercaseModel.begin(), lowercaseModel.end(), lowercaseModel.begin(), ::tolower);
        auto it = find_if(hardwareList.begin(), hardwareList.end(), [&](const ComputerHardware& hardware) {
            string lowercaseHardwareModel = hardware.model;
            transform(lowercaseHardwareModel.begin(), lowercaseHardwareModel.end(), lowercaseHardwareModel.begin(), ::tolower);
            return lowercaseHardwareModel == lowercaseModel;
        });
        if (it != hardwareList.end()) {
            cout << "Hardware found in inventory:" << endl;
            cout << "Type: " << it->type << ", Model: " << it->model << ", Quantity: " << it->quantity << ", Price: $" << it->price << endl;
        } else {
            cout << "Hardware not found in inventory." << endl;
        }
    }

    void displayInventory() {
        cout << "Inventory:" << endl;
        // Sort hardwareList by model before displaying
        sort(hardwareList.begin(), hardwareList.end());
        for (const auto& hardware : hardwareList) {
            cout << "Type: " << hardware.type << ", Model: " << hardware.model << ", Quantity: " << hardware.quantity << ", Price: $" << hardware.price << endl;
        }
    }

    void loadInventory() {
      try {
          ifstream file(filename);
          if (!file.is_open()) {
          }
          hardwareList.clear();
          string line;
          while (getline(file, line)) {
              cout << "DEBUG: Reading line: " << line << endl;  // Debug print to check file reading
              stringstream ss(line);
              string type, model;
              int quantity;
              float price;
              if (getline(ss, type, ',') && getline(ss, model, ',') && ss >> quantity >> price) {
                  hardwareList.push_back({type, model, quantity, price});
              } 
              ss.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining characters in the line
          }
          file.close(); // Close the file after reading
      } catch (const exception& e) {
          cerr << "Error: " << e.what() << endl;
      }
  }

};

void showMenu() {
    cout << "1. Add Hardware" << endl;
    cout << "2. Remove Hardware" << endl;
    cout << "3. Search Hardware" << endl;
    cout << "4. Display Inventory" << endl;
    cout << "5. Exit" << endl;
}

void handleAddHardware(Inventory& inventory) {
    ComputerHardware newHardware;
    cout << "Enter hardware type: ";
    cin >> newHardware.type;

    // Read hardware model (allowing spaces)
    cin.ignore();  // Ignore the newline character left in the input stream
    cout << "Enter hardware model: ";
    getline(cin, newHardware.model);

    cout << "Enter quantity: ";
    while (!(cin >> newHardware.quantity) || newHardware.quantity < 0) {
        cout << "Invalid input. Enter a non-negative integer for quantity: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter price: ";
    while (!(cin >> newHardware.price) || newHardware.price < 0) {
        cout << "Invalid input. Enter a non-negative value for price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    inventory.addHardware(newHardware);
}

void handleRemoveHardware(Inventory& inventory) {
    string model;
    cout << "Enter model to remove: ";
    cin.ignore(); // Clear any newline characters left in the input buffer
    getline(cin, model);
    inventory.removeHardware(model);
}

void handleSearchHardware(Inventory& inventory) {
    string model;
    cout << "Enter model to search: ";
    cin.ignore(); // Clear any newline characters left in the input buffer
    getline(cin, model);
    inventory.searchHardware(model);
}

int main() {
    Inventory inventory("hardware_inventory.txt");
    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (choice) {
            case 1:
                handleAddHardware(inventory);
                break;
            case 2:
                handleRemoveHardware(inventory);
                break;
            case 3:
                handleSearchHardware(inventory);
                break;
            case 4:
                inventory.displayInventory();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
