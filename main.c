#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order; 
};

// Node for chaining
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// Hash table structure
struct HashType
{
    struct Node* head;
};

// Size of the hash table
#define HASH_SIZE 10

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Insert a record into the hash table
void insertRecord(struct HashType hashTable[], struct RecordType record)
{
    int index = hash(record.id);

    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = record;
    newNode->next = NULL;

    // If the index is empty, create a new head
    if (hashTable[index].head == NULL)
    {
        hashTable[index].head = newNode; // Changed line: Handle case when head is NULL
    }
    else // Collision occurred, add to the end of the chain
    {
        struct Node* temp = hashTable[index].head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}



// Display records in the hash table
void displayRecordsInHash(struct HashType hashTable[], int hashSize)
{
    printf("Records in Hash Table:\n");
    for (int i = 0; i < hashSize; ++i)
    {
        printf("Index %d: ", i);
        struct Node* temp = hashTable[i].head;
        while (temp != NULL)
        {
            printf("%d %c %d -> ", temp->data.id, temp->data.name, temp->data.order);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Parses input file to an array of RecordType
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }
    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    // Parse data from input file
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize hash table
    struct HashType hashTable[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        hashTable[i].head = NULL;
    }

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records stored in the hash table
    displayRecordsInHash(hashTable, HASH_SIZE);

    return 0;
}
