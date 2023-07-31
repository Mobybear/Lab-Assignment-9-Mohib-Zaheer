#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

struct Node
{
    struct RecordType data;
    struct Node* next;
};


// Fill out this structure
struct HashType
{
        struct Node* head;
};

// Compute the hash function
int hash(int x)
{
    int hashSz = 15;
return x % hashSz;
}

// parses input file to an integer array
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
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
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

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    struct Node* current;
    for (int i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        current = pHashArray[i].head;
        while (current != NULL)
        {
            printf("id: %d, name: %c, order: %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("\n");
    }
}


int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
    int hashSz = 15; 
    struct HashType hashTable[15];

   
    for (int i = 0; i < hashSz; i++) {
        hashTable[i].head = NULL;
    }

    
    for (int i = 0; i < recordSz; i++) {
        int index = hash(pRecords[i].order);

       
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed for a new node\n");
            exit(-1);
        }
        newNode->data = pRecords[i];

        
        newNode->next = hashTable[index].head;
        hashTable[index].head = newNode;
    }

  
    displayRecordsInHash(hashTable, hashSz);

    return 0;
}



