# Inventory Management System

This C++ program provides a simple inventory management system for tracking computer hardware items such as GPUs and CPUs. It allows users to add, remove, search for, and display hardware items in the inventory.

## Features

- Add new hardware items to the inventory with details such as type, model, quantity, and price.
- Remove existing hardware items from the inventory.
- Search for hardware items by model name, with case-insensitive matching.
- Display the current inventory with details of all hardware items.

## How to Use

1. Clone or download the repository to your local machine.
2. Compile the `inventory_manager.cpp` file using a C++ compiler.
3. Run the compiled executable.
4. Follow the prompts to add, remove, search for, or display hardware items in the inventory.

### Usage Example

```cpp
#include <iostream>
#include "Inventory.h"

int main() {
    // Initialize the inventory
    Inventory inventory("hardware_inventory.txt");

    // Add hardware items to the inventory
    inventory.addHardware(/* hardware details */);

    // Remove hardware items from the inventory
    inventory.removeHardware(/* hardware model */);

    // Search for a specific hardware item
    inventory.searchHardware(/* hardware model */);

    // Display the current inventory
    inventory.displayInventory();

    return 0;
}
```
## File Structure

- `inventory_manager.cpp`: Contains the program.
- `hardware_inventory.txt`: Text file used to store inventory data.

## Requirements

- C++ compiler
- Standard Template Library (STL)

## Contributing

Contributions are welcome! Feel free to submit bug reports, feature requests, or pull requests.

