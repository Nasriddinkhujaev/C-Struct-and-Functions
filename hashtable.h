#ifndef HASHTABLE_H
#define HASHTABLE_H

// structures are defined in the .c file, and we use them in main.c, so we need to declare them here in the .h file. this is called a forward declaration. it allows us to use pointers to these structures in the function prototypes without needing to know the details of the structures at this point.
//  1. Define {key, value} structure. (Define key and value as char datatype)
typedef struct
{                // Define a structure called KeyValuePair. This structure will represent a key-value pair in the hash table.
    char *key;   // key is a pointer to a char, which means it can hold a string. This will be used to store the key in the key-value pair.
    char *value; // value is also a pointer to a char, which means it can hold a string. This will be used to store the value in the key-value pair.
} KeyValuePair;  // This structure will be used to store key-value pairs in the hash table.
// this code above is defining a type definition for structure called KeyValuePair with two members. when i need to use KeyValuePairs, i can simply declare a variable of type KeyValuePair instead of writing struct KeyValuePair every time.
//   example   usage of KeyValuePair structure
// KeyValuePair pair; // declare a variable of type KeyValuePair
// pair.key = "name"; // assign a string to the key member of the pair variable
// pair.value = "John"; // assign a string to the value member of the pair variable

//  2. Define hash table structure

typedef struct
{                         // Define a structure called HashTable. This structure will represent the hash table itself and will contain an array of key-value pairs and the size of the table.
    KeyValuePair **table; // Array of key-value pairs. KeyValuePair** means that table is a pointer to a pointer to a KeyValuePair. this allows us to create a dynamic array of pointers to KeyValuePair structures. Each element in the table will point to a KeyValuePair structure that contains a key and a value.
    int size;             // Number of table entries.
} HashTable;
//   example   usage of HashTable structure
// HashTable hashTable = malloc(sizeof(HashTable)); // allocate memory for a HashTable structure. malloc returns a pointer to the allocated memory, which is stored in the variable hashTable.



// Function prototypes
HashTable *createHashTable(int size);
void freeHashTable(HashTable *ht);

KeyValuePair *createKeyValuePair(const char *key, const char *value);
void freeKeyValuePair(KeyValuePair *pair);

int hashFunction(char *key);

void insert(HashTable *ht, char *key, char *value);
void delete (HashTable *ht, char *key);
char *search(HashTable *ht, char *key);

void displayHashTable(HashTable *ht);
void displaySearchResult(HashTable *ht, char *key);

#endif

