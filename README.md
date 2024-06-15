# Inventory Management System

## Overview

Inventory Manager is a C++ application that allows users to manage a collection of computer hardware items. It provides functionality to add new items, remove existing items, search by model, and display the current inventory. Data persistence is achieved using a text file (`hardware_inventory.txt`).

## Features

- **Add Hardware:** Add new hardware items to the inventory, specifying type, model, quantity, and price.
- **Remove Hardware:** Remove hardware items from the inventory by specifying their model.
- **Search Hardware:** Search for hardware items by their model name (case-insensitive).
- **Display Inventory:** View the entire inventory sorted by hardware model.

## Requirements

- C++ compiler with C++11 support
- Standard C++ libraries

## Usage

1. **Clone the repository:**

   ```bash
   git clone https://github.com/6a6aadnan/Inventory-Manager.git
   cd Inventory-Manager
   ```
2. **Compile the code:**

   ```bash
   g++ inventory_manager.cpp -o inventory_manager
   ```
3. **Run the program:**

   ```bash
   ./inventory_manager
   ```
4. **Follow the on-screen menu:**

   - Enter a number (1-5) to perform an action:
     - `1` Add Hardware
     - `2` Remove Hardware
     - `3` Search Hardware
     - `4` Display Inventory
     - `5` Exit

5. **Input instructions:**

   - When adding hardware, ensure to provide valid inputs for quantity (non-negative integer) and price (non-negative float).
   - Use exact model names when removing or searching hardware items.

6. **File Handling:**

   - The program reads and writes data to `hardware_inventory.txt` for data persistence.
   - Ensure the file has appropriate read and write permissions in your environment.

## Example

Here's an example of how to use the program:

1. Add a new hardware item:
   - Type: GPU
   - Model: RTX 3060
   - Quantity: 10
   - Price: $299.99

2. Display the current inventory to verify the addition.

3. Remove the hardware item by specifying its model (`RTX 3060`).

4. Search for the hardware item by model (`rtx 3060`).

5. Exit the program.

## Notes

- Ensure all input values are valid as per the program's requirements to avoid errors.
- For any issues or improvements, please feel free to open an issue or submit a pull request.

    
