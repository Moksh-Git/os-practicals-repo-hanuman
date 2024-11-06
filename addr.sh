#!/bin/bash

# Prompt user to input the address book file name
read -p "Enter the name of the address book file (e.g., address_book.txt): " ADDRESS_BOOK

# Function to create an address book (a new file)
create_address_book() {
    touch "$ADDRESS_BOOK"
    echo "Address book '$ADDRESS_BOOK' created."
}

# Function to view the address book
view_address_book() {
    if [[ -f "$ADDRESS_BOOK" && -s "$ADDRESS_BOOK" ]]; then
        echo "Address Book Contents:"
        cat "$ADDRESS_BOOK"
    else
        echo "Address book is empty or doesn't exist."
    fi
}

# Function to insert a record into the address book
insert_record() {
    read -p "Enter Name: " name
    read -p "Enter Phone: " phone
    read -p "Enter Email: " email
    echo "$name, $phone, $email" >> "$ADDRESS_BOOK"
    echo "Record added."
}

# Function to delete a record from the address book
delete_record() {
    read -p "Enter the Name of the record to delete: " del_name
    if grep -q "^$del_name," "$ADDRESS_BOOK"; then
        grep -v "^$del_name," "$ADDRESS_BOOK" > temp && mv temp "$ADDRESS_BOOK"
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}

# Function to modify a record in the address book
modify_record() {
    read -p "Enter the Name of the record to modify: " mod_name
    if grep -q "^$mod_name," "$ADDRESS_BOOK"; then
        grep -v "^$mod_name," "$ADDRESS_BOOK" > temp && mv temp "$ADDRESS_BOOK"
        echo "Enter new details."
        read -p "Enter New Name: " name
        read -p "Enter New Phone: " phone
        read -p "Enter New Email: " email
        echo "$name, $phone, $email" >> "$ADDRESS_BOOK"
        echo "Record modified."
    else
        echo "Record not found."
    fi
}

# Main menu loop
while true; do
    echo ""
    echo "Address Book Menu:"
    echo "a) Create Address Book"
    echo "b) View Address Book"
    echo "c) Insert Record"
    echo "d) Delete Record"
    echo "e) Modify Record"
    echo "f) Exit"
    read -p "Choose an option: " choice

    case $choice in
        a) create_address_book ;;
        b) view_address_book ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) echo "Exiting..."; break ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done
