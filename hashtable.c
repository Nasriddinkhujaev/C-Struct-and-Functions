#include <stdio.h>     // for debugging purposes, can be removed later
#include <stdlib.h>    // for malloc and free
#include <string.h>    //
#include "hashtable.h" // for the hashtable struct and function prototypes
// #include "hashtable.h" // for the hashtable struct and function prototypes

static char *duplicateString(const char *source)
{
    size_t len = strlen(source) + 1;
    char *copy = malloc(len);
    if (copy != NULL)
    {
        memcpy(copy, source, len);
    }
    return copy;
}

// Use C struct to implement a hash table. The program should include the following:

//  3. Create {key, value} pair. [Hint: you need to allocate memory for the key and value and return a pointer to the {key, value} pair]
KeyValuePair *createKeyValuePair(const char *key, const char *value)
{
    KeyValuePair *pair = malloc(sizeof(KeyValuePair)); // allocate memory for a KeyValuePair structure. malloc returns a pointer to the allocated memory, which is stored in the variable pair. sizeof(KeyvaluePair) calculates the size of the KeyValuePair strcture, which is needed to know how much memory to allocate.
    if (pair == NULL)
    {                                                          // checking if malloc was sucessful. if malloc returns NULL, it means that the memory allocation failed
        printf("memory allocation failed for KeyValuePair\n"); // print error message
        return NULL;
    }
    pair->key = duplicateString(key);     // duplicate key string
    pair->value = duplicateString(value); // duplicate value string
    if (pair->key == NULL || pair->value == NULL)
    {
        free(pair->key);
        free(pair->value);
        free(pair);
        printf("memory allocation failed for key/value strings\n");
        return NULL;
    }
    // -> is used to access members of a structure through a pointer. since pair is a pointer to a KeyValuePair structure, we use -> to access its members (key and value).
    return pair;
}
//     example  usage of createKeyValuePair function
// KeyValuePair *pair = createKeyValuePair("name", "John");

// 4. Create the Hash Table. [Hint: you need to allocate memory for the Hash Table, and set all {key, value} pairs to NULL since they are not used)

HashTable *createHashTable(int size)
{
    HashTable *ht = malloc(sizeof(HashTable)); // allocate memory for a HashTable structure. malloc returns a pointer to the allocated memory, which is stored in the variable hs. sizeof(HashTable) calculates the size of the HashTable structure, which is needed to know how much memory to allocate.
    if (ht == NULL)
    {
        printf("memory allocation failed for HashTable\n"); // print error message if malloc fails
        return NULL;
    }
    ht->size = size;                                   // set the size member to the given size parameter. this will determine how many key-value pairs the hash table can hold.
    ht->table = malloc(sizeof(KeyValuePair *) * size); // allocate memory for an array of pointers to KeyValuePair structures. the size of the array is determined by the size parameter. sizeof(keyValuePair *) calculates the size of a pointer to a KeyValuePair structure, and multiplying it by size gives us the total amount of memry needed for the array of pointers.
    if (ht->table == NULL)
    {
        printf("memory allocation failed for HashTable table\n"); // print error message if malloc fails
        free(ht);                                                 // free the previously allocated memory for the HashTable structure to prevent memory leaks.
        return NULL;
    }
    // Initialize all entries in the table to NULL.
    for (int i = 0; i < size; i++)
    {
        ht->table[i] = NULL; // set each element in the table array to NULL.
    }
    return ht; // return the pointer to the newly created HashTable structure.
}
//     example  usage of createHashTable function
// HashTable *hashTable = createHashTable(10); // creates a hash table with a size of 10, meaning it can hold up to 10 key-value pairs.

// 5. Define a function to free up the memory of a {key, value} pair
void freeKeyValuePair(KeyValuePair *pair)
{
    if (pair == NULL)
    {
        return; // nothing to free if the pair is NULL
    }
    else
    {
        free(pair->key);
        free(pair->value);
        free(pair); // free the memory allocated for the KeyValuePair structure itself after freeing the key and value strings.
    }
}
//    example  usage of freeKeyValuePair function
// freeKeyValuePair(pair); // frees the memory allocated for the key-value pair pointed to by pair.

// 6. Define a function to free up the memory of the Hash Table.

void freeHashTable(HashTable *ht)
{
    if (ht == NULL)
    {
        return; // nothing to free if the hash table is null
    }
    else
    {
        for (int i = 0; i < ht->size; i++)
        {
            if (ht->table[i] != NULL)
            {
                freeKeyValuePair(ht->table[i]); // free each key value pair in the table using the freeKeyValuePair function defined earlier.
            }
        }
        free(ht->table); // free the memory allocated for the array of pointers to KeyValuePair structures.
        free(ht);        // free the memrory allocated for the HashTable structure itself after freeing the table array.
    }
}
//    example  usage of freeHashTable function
// freeHashTable(hashTable); // frees the memory allocated for the hash table pointed to by hashTable, including all key-value pairs contained within it.

// 7. Define a Hash function to get the index for a {key, value} pair in the Hash Table. [Hint: hash function only takes the key to compute the index]

int hashFunction(char *key)
{
    int hash = 0; // Initialize a variable called hash to 0. This variable will be used to store the computed hash value for the given key.

    for (int i = 0; key[i] != '\0'; i++) // loop through each character in the key string untill hit the null terminator '\0'
    {
        hash += key[i]; // add the ASCII value of the current character to the hash variable
    }

    return hash; // return the computed hash value. this value will be used to determine the index in the hash table where the key-value pair should be stored.
}
//    example  usage of hashFunction
// int index = hashFunction("name"); // computes the hash value for the key "name" and stores it in the variable index. this hash value can then be used to determine where to store the key-value pair in the hash table.

// 8. Define an Insert function to insert a {key, value} pair into the Hash Table(15 points)
//      1. Create a {key, value} pair
//      2. Compute the index based on the hash function
//      3. Check if the index is already occupied or not by comparing the key
//      4. If it is not occupied, we can directly insert it into the index
//      5. Otherwise, it is a collision, and we need to:
//      5.1 update the item value only to the new one if {key, value} pair already exists (i.e., the
//      same item pair was already inserted before)
//      5.2 return an error message due to overflow
// [Hint: the function header for insert is: void insert (HashTable* hashtable, char* key, char* value);]

void insert(HashTable *ht, char *key, char *value)
{
    if (ht == NULL || key == NULL || value == NULL)
    {
        return; // invalid input
    }
    int index = hashFunction(key) % ht->size;

    if (ht->table[index] == NULL)
    {
        ht->table[index] = createKeyValuePair(key, value);
        if (ht->table[index] != NULL)
        {
            printf("Inserted: (%s, %s) at index %d\n", key, value, index);
        }
        return;
    }

    if (strcmp(ht->table[index]->key, key) == 0)
    {
        char *new_value = duplicateString(value);
        if (new_value == NULL)
        {
            printf("memory allocation failed for value update\n");
            return;
        }
        free(ht->table[index]->value);
        ht->table[index]->value = new_value;
        printf("Updated: key '%s' -> new value '%s' at index %d\n", key, value, index);
        return;
    }

    printf("Error: collision at index %d. Cannot insert key '%s' (slot occupied by key '%s').\n",
           index, key, ht->table[index]->key);
}
//    example   usage of insert function
// insert(hashTable, "name", "John"); // inserts the key-value pair {"name, "John"} into the hash table pointed to by hashTable. if the key "name" already exists in the hash table, it will update the value to "John". if there is a collision at the computed index, it will print an error message indicating that a collision occurred.

// 9. Define a function to delete a {key, value} pair from the Hash Table.

void delete(HashTable *ht, char *key)
{
    if (ht == NULL || key == NULL)
    {
        return;
    }

    int index = hashFunction(key) % ht->size;

    if (ht->table[index] == NULL || strcmp(ht->table[index]->key, key) != 0)
    {
        printf("Delete failed: key '%s' not found.\n", key);
        return;
    }

    freeKeyValuePair(ht->table[index]);
    ht->table[index] = NULL;
    printf("Deleted: key '%s' from index %d\n", key, index);
}
//     example  usage of delete function
// delete(hashTable, "name"); // deletes the key-value pair with the key "name" from the hash table pointed to by hashTable. if the key is not found in the hash table, it will print an error message indicating that the key was not found. if the key is found, it will free the memory allocated for the key-value pair and set the corresponding index in the hash table to NULL.

// 10. define a function to search for a value based on the key in the hash table

char *search(HashTable *ht, char *key)
{
    if (ht == NULL || key == NULL) // check if the hash table or key is null. if either is null, we cannot perform a search, so we return NULL to indicate that the search was unsuccessful.
    {
        return NULL;
    }

    int index = hashFunction(key) % ht->size;
    if (ht->table[index] != NULL && strcmp(ht->table[index]->key, key) == 0)
    {
        return ht->table[index]->value;
    }
    return NULL;
}
//   example   usage of search function
// char *value = search(hashTable, "name"); // searches for the value associated with the key "name" in the hash table pointed to by hashTable. if the key is found, it returns the corresponding value. if the key is not found or if the hash table is null, it returns NULL to indicate that the search was unsuccessful.

// 11. define a function to display all the {key, value} pairs in the hash table

void displaySearchResult(HashTable *ht, char *key)
{
    char *value = search(ht, key); // call the search function to find the value associated with the given key in the hash table. the result is stored in the variable value.

    if (value != NULL) // check if the value is not NULL
    {
        printf("Search '%s' → found, value = '%s'\n", key, value);
    }
    else // if the value is NULL
    {
        printf("Search '%s' → not found\n", key); // print an error message
    }
}
//  example   usage of displaySearchResult function
// displaySearchResult(hashTable, "name"); // displays the search result for the key "name" in the hash table pointed to by hashTable. if the key is found, it will print the key and its corresponding value. if the key is not found, it will print an error message indicating that the key was not found.

// 12. define a function to display all the {key, value} pairs in the hash table

void displayHashTable(HashTable *ht)
{
    if (ht == NULL) // check if the hash table is null
    {
        return;
    }

    printf("--- Hash Table (size = %d) ---\n", ht->size);

    for (int i = 0; i < ht->size; i++) // loop through each index in the hash table from 0 to size-1
    {
        if (ht->table[i] != NULL) // check if the slot at index i is not empty (i.e., it contains a key-value pair). if it is not empty, we print the key and value stored at that index. if it is empty, we print that the index is NULL.
        {
            printf("[%d] key = '%s ' value = '%s'\n",
                   i,
                   ht->table[i]->key,
                   ht->table[i]->value);
        }
        else // if the slot is empty, we print that the index is NULL
        {
            printf("[%d] (empty)\n", i);
        }
    }
    printf("------------------------------\n");
}
//   example   usage of displayHashTable function
// displayHashTable(hashTable); // displays all the key-value pairs in the hash table pointed to by hashTable.
