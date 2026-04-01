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