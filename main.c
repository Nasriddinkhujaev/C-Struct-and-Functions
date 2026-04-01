// main.c
// sample main function for testing your hash table implementation.
//
// you have two options:
// option 1: implement all hash table functions directly in this file.

// option 2: create a separate "hashtable.h" / "hashtable.c" library,
//            then uncomment the line below and compile with:
//            gcc -o task1 hashtable.c main.c

// #include "hashtable.h"

#include <stdio.h>

#define TABLE_SIZE 10

int main(void)
{
    HashTable *table = create_table(TABLE_SIZE);

    // insert
    printf("=== Inserting items ===\n");
    insert(table, "name", "Alice");
    insert(table, "city", "Philadelphia");
    insert(table, "course", "CIS-2107");
    insert(table, "grade", "A");
    insert(table, "year", "2026");

    display_table(table);

    // search
    printf("=== Searching ===\n");
    display_search(table, "name");
    display_search(table, "city");
    display_search(table, "missing");
    printf("\n");

    // update existing key
    printf("=== Updating existing key ===\n");
    insert(table, "grade", "A+");
    display_table(table);

    // delete
    printf("=== Deleting 'city' ===\n");
    delete(table, "city");
    display_table(table);

    // delete a key that doesnt exist
    printf("=== Deleting 'city' again (should fail) ===\n");
    delete(table, "city");
    printf("\n");

    free_table(table);
    printf("Hash table memory freed.\n");

    return 0;
}