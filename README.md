# Inventory Management System

## Overview

Inventory Manager is a C++ application designed for managing a collection of computer hardware items. It allows users to add new items, remove existing ones, search by model, and display the current inventory. Data persistence is now achieved using PostgreSQL hosted on Amazon RDS, replacing the previous text file storage.

## Features

- **Add Hardware:** Add new hardware items to the inventory, specifying type, model, quantity, and price.
- **Remove Hardware:** Remove hardware items from the inventory by specifying their model.
- **Search Hardware:** Search for hardware items by their model name (case-insensitive).
- **Display Inventory:** View the entire inventory sorted by hardware model.

## Requirements

- C++ compiler
- postgresql-devel 
- libpqxx-devel
- Python 3
- psycopg2 

## Linux Setup

### Amazon EC2 Instance

1. **Create EC2 Instance:**
   - **Launch an Amazon Linux instance on AWS EC2.**
   - **Configure security groups to allow inbound traffic on ports 22 (SSH) and 5432 (PostgreSQL).**
2. **SSH into EC2 Instance:**    
   ```bash
   ssh -i your-key-pair.pem ec2-user@your-instance-public-dns
   ```
3. Install Dependencies:
   
   ```bash
   sudo yum update -y
   ```
   ```bash
   sudo yum install gcc-c++
   ```
   ```bash
   sudo yum install postgresql-devel
   ```
   ```bash
   sudo yum install libpqxx-devel
   ```
   ```bash
   sudo yum install python3
   ```
   ```bash
   sudo yum install python3-pip
   ```
   ```bash
   sudo pip3 install psycopg2
   ```
     
## PostgreSQL Setup

### Amazon RDS Instance

1. **Set up an Amazon RDS PostgreSQL instance** or use an existing one.

2. **Note down the following details** from your Amazon RDS PostgreSQL instance:
   - **Database endpoint**
   - **Database name**
   - **Username**
   - **Password**
   - **Port number**
     
## Python Script for Data Migration
To migrate data from a text file to PostgreSQL, use text_to_postgresql.py
### Instructions for Running the Python Script
1. **Save the Python script text_to_postgresql.py to your local directory.**
2. **Replace placeholders in the script:**
   
   - **Update connection_string with your actual PostgreSQL connection details (database name, username, password, host, and port).**
     
3. **Run the Python script:**
   
   - **Open a terminal or command prompt.**
   - **Navigate to the directory containing text_to_postgresql.py.**
   - **Execute the script using Python:**
     
     ```bash
     python text_to_postgresql.py
     ```
## Usage

1. **Clone the repository:**

   ```bash
   git clone https://github.com/6a6aadnan/Inventory-Manager.git
   cd Inventory-Manager
   ```
2. **Compile the code:**

   ```bash
   g++ -std=c++11 -I/usr/include/postgresql inventory_manager.cpp -o inventory_manager -lpqxx -lpq
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

7. **PostgreSQL Integration:**

   - The program now connects to PostgreSQL using libpqxx for database operations.
   - Ensure your PostgreSQL connection string (dbname=mydatabase user=myuser password=mypassword host=myendpoint.rds.amazonaws.com port=5432) is correctly configured in the Inventory class constructor 
     (Inventory(const std::string& connectionString)).

## Example

Here's an example of how to use the program:

1. Add a new hardware item:
   - Type: GPU
   - Model: RTX 3060
   - Quantity: 10
   - Price: $299.99

2. Display the current inventory to verify the addition.

3. Remove the hardware item by specifying its model (`RTX 3060`).

4. Search for the hardware item by model (`RTX 3060`).

5. Exit the program.

## Notes

- Ensure all input values are valid as per the program's requirements to avoid errors.
- For any issues or improvements, please feel free to open an issue or submit a pull request.

    
