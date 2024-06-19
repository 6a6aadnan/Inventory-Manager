#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

struct ComputerHardware {
    string type;
    string model;
    int quantity;
    float price;

    bool operator<(const ComputerHardware& other) const {
        return model < other.model;
    }
};

class Inventory {
private:
    pqxx::connection conn;

    void createSchema() {
        pqxx::work txn(conn);
        txn.exec("CREATE TABLE IF NOT EXISTS computer_hardware ("
                 "    type VARCHAR(255),"
                 "    model VARCHAR(255) PRIMARY KEY,"
                 "    quantity INT,"
                 "    price FLOAT"
                 ")");
        txn.commit();
    }

public:
    Inventory(const std::string& connectionString)
        : conn(connectionString) {
        createSchema(); // Create table if not exists
    }

    void addHardware(const ComputerHardware& newHardware) {
        try {
            pqxx::work txn(conn);

            // Prepare SQL statement
            std::stringstream sql;
            sql << "INSERT INTO computer_hardware (type, model, quantity, price) "
                   "VALUES ($1, $2, $3, $4)";

            // Create prepared statement
            pqxx::prepare::invocation invoc = txn.prepared("insert_stmt", sql.str());

            // Bind parameters
            invoc(newHardware.type)(newHardware.model)(newHardware.quantity)(newHardware.price).exec();

            txn.commit();
            cout << "Added hardware successfully." << endl;
        } catch (const std::exception& e) {
            cerr << "Error adding hardware: " << e.what() << endl;
        }
    }

    void removeHardware(const string& model) {
        try {
            pqxx::work txn(conn);

            // Prepare SQL statement
            std::stringstream sql;
            sql << "DELETE FROM computer_hardware WHERE model = $1";

            // Execute the SQL statement
            pqxx::prepare::invocation invoc = txn.prepared("delete_stmt", sql.str());
            invoc(model).exec();

            txn.commit();
            cout << "Removed hardware successfully." << endl;
        } catch (const std::exception& e) {
            cerr << "Error removing hardware: " << e.what() << endl;
        }
    }

    void searchHardware(const string& model) {
        try {
            pqxx::work txn(conn);

            // Prepare SQL statement
            std::stringstream sql;
            sql << "SELECT type, model, quantity, price FROM computer_hardware WHERE model = $1";

            // Execute the SQL statement
            pqxx::prepare::invocation invoc = txn.prepared("select_stmt", sql.str());
            pqxx::result result = invoc(model).exec();

            // Process the result
            if (!result.empty()) {
                pqxx::tuple row = result[0];
                cout << "Hardware found in inventory:" << endl;
                cout << "Type: " << row["type"].as<string>() << ", Model: " << row["model"].as<string>()
                     << ", Quantity: " << row["quantity"].as<int>() << ", Price: $" << row["price"].as<float>() << endl;
            } else {
                cout << "Hardware not found in inventory." << endl;
            }
        } catch (const std::exception& e) {
            cerr << "Error searching hardware: " << e.what() << endl;
        }
    }

    void displayInventory() {
        try {
            pqxx::work txn(conn);

            // Execute SQL statement to fetch all hardware items
            pqxx::result result = txn.exec("SELECT type, model, quantity, price FROM computer_hardware ORDER BY model");

            // Display inventory
            cout << "Inventory:" << endl;
            for (const auto& row : result) {
                cout << "Type: " << row["type"].as<string>() << ", Model: " << row["model"].as<string>()
                     << ", Quantity: " << row["quantity"].as<int>() << ", Price: $" << row["price"].as<float>() << endl;
            }
        } catch (const std::exception& e) {
            cerr << "Error displaying inventory: " << e.what() << endl;
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

    cin.ignore();
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
    cin.ignore();
    getline(cin, model);
    inventory.removeHardware(model);
}

void handleSearchHardware(Inventory& inventory) {
    string model;
    cout << "Enter model to search: ";
    cin.ignore();
    getline(cin, model);
    inventory.searchHardware(model);
}

int main() {
    // Replace with your actual RDS PostgreSQL endpoint, database name, username, password
    std::string connectionString = "dbname=mydatabase user=myuser password=mypassword host=myendpoint.rds.amazonaws.com port=5432";

    Inventory inventory(connectionString);

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
