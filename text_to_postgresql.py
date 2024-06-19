import psycopg2

# Function to read data from text file
def read_data_from_file(filename):
    data = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                parts = line.split(',')
                if len(parts) == 4:
                    type_, model, quantity, price = parts
                    quantity = int(quantity)
                    price = float(price)
                    data.append((type_, model, quantity, price))
    return data

# Function to migrate data to PostgreSQL
def migrate_to_postgresql(data, connection_string):
    try:
        conn = psycopg2.connect(connection_string)
        cur = conn.cursor()

        # Create table if not exists
        cur.execute("""
            CREATE TABLE IF NOT EXISTS computer_hardware (
                type VARCHAR(255),
                model VARCHAR(255) PRIMARY KEY,
                quantity INT,
                price FLOAT
            )
        """)
        conn.commit()

        # Insert data into the table
        for item in data:
            cur.execute("""
                INSERT INTO computer_hardware (type, model, quantity, price)
                VALUES (%s, %s, %s, %s)
            """, item)
            conn.commit()
        
        print("Data migration to PostgreSQL completed successfully.")

    except psycopg2.Error as e:
        print("Error migrating data to PostgreSQL:", e)

    finally:
        if conn:
            conn.close()

# Main script
if __name__ == "__main__":
    # Replace with your PostgreSQL connection string
    connection_string = "dbname=mydatabase user=myuser password=mypassword host=myendpoint.rds.amazonaws.com port=5432"

    # Replace with your actual text file path
    filename = "hardware_inventory.txt"

    # Read data from text file
    data = read_data_from_file(filename)

    # Migrate data to PostgreSQL
    migrate_to_postgresql(data, connection_string)
