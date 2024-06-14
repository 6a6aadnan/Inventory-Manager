#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype> // Include the cctype header for the tolower function

using namespace std;

struct ComputerHardware {
    string type; // Type of hardware (e.g., GPU, CPU)
    string model; // Model name
    int quantity; // Number of items in stock
    float price; // Price per item
};

class Inventory {
private:
    vector<ComputerHardware> hardwareList;
    string filename; 

public:
    Inventory(const string& filename) : filename(filename) {
        loadInventory(); 
    }

    void addHardware(const ComputerHardware& newHardware) {
        if (newHardware.quantity < 0 || newHardware.price < 0) {
            cerr << "Error: Quantity and price must be non-negative." << endl;
            return;
        }
        hardwareList.push_back(newHardware);
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
        string lowercaseModel = model; // Make a copy of the model string
        transform(lowercaseModel.begin(), lowercaseModel.end(), lowercaseModel.begin(), ::tolower); // Convert the model string to lowercase
        auto it = find_if(hardwareList.begin(), hardwareList.end(), [&](const ComputerHardware& hardware) {
            string lowercaseHardwareModel = hardware.model; // Make a copy of the hardware model string
            transform(lowercaseHardwareModel.begin(), lowercaseHardwareModel.end(), lowercaseHardwareModel.begin(), ::tolower); // Convert the hardware model string to lowercase
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
        for (const auto& hardware : hardwareList) {
            cout << "Type: " << hardware.type << ", Model: " << hardware.model << ", Quantity: " << hardware.quantity << ", Price: $" << hardware.price << endl;
        }
    }

    void saveInventory() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& hardware : hardwareList) {
                file << hardware.type << "," << hardware.model << "," << hardware.quantity << "," << hardware.price << endl;
            }
            file.close();
        } else {
            cerr << "Error: Unable to save inventory data to file." << endl;
        }
    }

    void loadInventory() {
        ifstream file(filename);
        if (file.is_open()) {
            hardwareList.clear(); 
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string type, model;
                int quantity;
                float price;
                getline(ss, type, ',');
                getline(ss, model, ',');
                ss >> quantity;
                ss.ignore(); 
                ss >> price;
                hardwareList.push_back({type, model, quantity, price});
            }
            file.close();
        } else {
            cerr << "Error: Unable to load inventory data from file." << endl;
        }
    }
};

int main() {
    Inventory inventory("hardware_inventory.txt");

    // Define existing hardware items
    ComputerHardware rtx3070 = {"GPU", "NVIDIA GeForce RTX 3070", 20, 299.99};
    ComputerHardware rtx3080 = {"GPU", "NVIDIA GeForce RTX 3080", 15, 499.99};
    ComputerHardware rtx3090 = {"GPU", "NVIDIA GeForce RTX 3090", 10, 999.99};
    ComputerHardware ryzen54600g = {"CPU", "AMD Ryzen 5 4600G", 25, 149.99};
    ComputerHardware ryzen74700g = {"CPU", "AMD Ryzen 7 4700G", 20, 249.99};
    ComputerHardware ryzen94800g = {"CPU", "AMD Ryzen 9 4800G", 15, 349.99};
    // Add hardware items to inventory
    inventory.addHardware(rtx3070);
    inventory.addHardware(rtx3080);
    inventory.addHardware(rtx3090);
    inventory.addHardware(ryzen54600g);
    inventory.addHardware(ryzen74700g);
    inventory.addHardware(ryzen94800g);
    
    // Define new hardware items
    ComputerHardware rtx4070 = {"GPU", "NVIDIA GeForce RTX 4070", 20, 799.99};
    ComputerHardware rtx4080 = {"GPU", "NVIDIA GeForce RTX 4080", 15, 999.99};
    ComputerHardware rtx4090 = {"GPU", "NVIDIA GeForce RTX 4090", 10, 1999.99};
    ComputerHardware ryzen56600g = {"CPU", "AMD Ryzen 5 6600G", 25, 299.99};
    ComputerHardware ryzen76700g = {"CPU", "AMD Ryzen 7 6700G", 20, 399.99};
    ComputerHardware ryzen96800g = {"CPU", "AMD Ryzen 9 6800G", 15, 599.99};
    
    // Add new hardware items to inventory
    inventory.addHardware(rtx4070);
    inventory.addHardware(rtx4080);
    inventory.addHardware(rtx4090);
    inventory.addHardware(ryzen56600g);
    inventory.addHardware(ryzen76700g);
    inventory.addHardware(ryzen96800g);
    
    // Remove existing hardware items from inventory
    inventory.removeHardware("NVIDIA GeForce RTX 3070");
    inventory.removeHardware("AMD Ryzen 5 4600G");

    // Search for RTX 4070
    inventory.searchHardware("NVIDIA GeForce RTX 4070");

    // Display inventory after addition and removal
    inventory.displayInventory();

    return 0;
}

