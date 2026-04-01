#include <stdio.h> // for debugging purposes, can be removed later
#include <stdlib.h> // for malloc and free
#include <string.h> // 
// #include "hashtable.h" // for the hashtable struct and function prototypes  

// Use C struct to implement a hash table. The program should include the following:
//  1. Define {key, value} structure. (Define key and value as char datatype)
typedef struct  { // Define a structure called KeyValuePair. This structure will represent a key-value pair in the hash table.
    char *key; // key is a pointer to a char, which means it can hold a string. This will be used to store the key in the key-value pair.
    char *value; // value is also a pointer to a char, which means it can hold a string. This will be used to store the value in the key-value pair.
} KeyValuePair; // This structure will be used to store key-value pairs in the hash table.
// this code above is defining a type definition for structure called KeyValuePair with two members. when i need to use KeyValuePairs, i can simply declare a variable of type KeyValuePair instead of writing struct KeyValuePair every time.
// example usage of KeyValuePair structure
// KeyValuePair pair; // declare a variable of type KeyValuePair
// pair.key = "name"; // assign a string to the key member of the pair variable
// pair.value = "John"; // assign a string to the value member of the pair variable


//  2. Define hash table structure

typedef struct { // Define a structure called HashTable. This structure will represent the hash table itself and will contain an array of key-value pairs and the size of the table.
    KeyValuePair **table; // Array of key-value pairs. KeyValuePair** means that table is a pointer to a pointer to a KeyValuePair. this allows us to create a dynamic array of pointers to KeyValuePair structures. Each element in the table will point to a KeyValuePair structure that contains a key and a value.
    int size; // Number of table entries. 
}HashTable;
// example usage of HashTable structure
// HashTable hashTable = malloc(sizeof(HashTable)); // allocate memory for a HashTable structure. malloc returns a pointer to the allocated memory, which is stored in the variable hashTable.


//  3. Create {key, value} pair. [Hint: you need to allocate memory for the key and value and return a pointer to the {key, value} pair]
KeyValuePair *createKeyValuePair(const char* key, const char* value){
    KeyValuePair *pair = malloc(sizeof(KeyValuePair)); // allocate memory for a KeyValuePair structure. malloc returns a pointer to the allocated memory, which is stored in the variable pair. sizeof(KeyvaluePair) calculates the size of the KeyValuePair strcture, which is needed to know how much memory to allocate.
    if(pair == NULL){ // checking if malloc was sucessful. if malloc returns NULL, it means that the memory allocation failed
        printf("memory allocation failed for KeyValuePair\n"); // print error message
        return NULL;
    }
    pair->key = strdup(key); // strdup is a function that duplicates a string. it allocates memory for the new string and copies the content of the original string (key) into it. this is necessary because we want to store a copy of the key in the KeyValuePair structure, rather than just a pointer to the original string.
    pair->value = strdup(value); // similarly, this line duplicates the value string and stores it in the value member of the KeyValuePair structure.
    // -> is used to access members of a structure through a pointer. since pair is a pointer to a KeyValuePair structure, we use -> to access its members (key and value).
    return pair;
}
// one line example usage of createKeyValuePair function
// KeyValuePair *pair = createKeyValuePair("name", "John");

// 4. Create the Hash Table. [Hint: you need to allocate memory for the Hash Table, and set all {key, value} pairs to NULL since they are not used) 

HashTable *createHashTable( int size){
    HashTable *ht = malloc(sizeof(HashTable)); // allocate memory for a HashTable structure. malloc returns a pointer to the allocated memory, which is stored in the variable hs. sizeof(HashTable) calculates the size of the HashTable structure, which is needed to know how much memory to allocate.
    if(ht == NULL){
        printf("memory allocation failed for HashTable\n"); // print error message if malloc fails
        return NULL;
    }
    ht->size = size; // set the size member to the given size parameter. this will determine how many key-value pairs the hash table can hold.
    ht->table = malloc(sizeof(KeyValuePair *) * size); // allocate memory for an array of pointers to KeyValuePair structures. the size of the array is determined by the size parameter. sizeof(keyValuePair *) calculates the size of a pointer to a KeyValuePair structure, and multiplying it by size gives us the total amount of memry needed for the array of pointers.
    if(ht->table == NULL){
        printf("memory allocation failed for HashTable table\n"); // print error message if malloc fails
        free(ht); // free the previously allocated memory for the HashTable structure to prevent memory leaks.
        return NULL;
    }
    // Initialize all entries in the table to NULL.
    for (int i = 0; i < size; i++){
        ht->table[i] = NULL; // set each element in the table array to NULL.
    }
    return ht; // return the pointer to the newly created HashTable structure.
}
// one line example usage of createHashTable function
// HashTable *hashTable = createHashTable(10); // creates a hash table with a size of 10, meaning it can hold up to 10 key-value pairs.

// 5. Define a function to free up the memory of a {key, value} pair
void freeKeyValuePair(KeyValuePair *pair){
    if(pair == NULL){
        return; // nothing to free if the pair is NULL
    }else{
        free(pair->key);
        free(pair->value);
        free(pair); // free the memory allocated for the KeyValuePair structure itself after freeing the key and value strings.
    }
}
// one line example usage of freeKeyValuePair function
// freeKeyValuePair(pair); // frees the memory allocated for the key-value pair pointed to by pair.


// 6. Define a function to free up the memory of the Hash Table.

void freeHashTable(HashTable *ht){
    if(ht == NULL){
        return; // nothing to free if the hash table is null
    }else{
        for (int i = 0; i < ht->size; i++){
            if(ht->table[i] != NULL){
                freeKeyValuePair(ht->table[i]); // free each key value pair in the table using the freeKeyValuePair function defined earlier.
            }
        }
        free(ht->table); // free the memory allocated for the array of pointers to KeyValuePair structures.
        free(ht); // free the memrory allocated for the HashTable structure itself after freeing the table array.
    }
}
// one line example usage of freeHashTable function
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
// one line example usage of hashFunction
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

void insert (HashTable *ht, char *key, char *value){
    if(ht == NULL){
        return; // if the hash table is null, just return
    }
    int index = hashFunction(key) % ht->size; // compute the index for the given key

    // case 1: if the index is not occupied
    if(ht->table[index] == NULL){
        ht->table[index] = createKeyValuePair(key, value); // if the index is not occupied, create a new key-value pair and insert it into the hash table at the computed index.
        return; // return after inserting the new key-value pair
    }
    // case 2: if the index is occupied
    if(strcmp(ht->table[index]->key, key) == 0){ // check if the key at the occupied index matches the given key using strcmp
        free(ht->table[index]->value); // free the memory allocated for the old value to prevent memory leaks
        ht->table[index]->value = strdup(value); // update the value for the existing key by duplicating the new value string and assigning it to the value member of the KeyValuePair structure at that index
        return; // return after updating the value
    }

    // case 3: if there is a collision
    printf("Collision occurred at index %d\n", index); // print an error message that a collisionn occured at the computed index. this means that there is already a different key-value pair stored at that index, and we cannot insert the new key-value pair without overwriting the existing one.
    return; // return after handling the collision 
}


