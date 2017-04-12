#ifndef HEADER_HASH
#define HEADER_HASH

#include "stdlib.h"

typedef struct hash *ST;
ST symbolTable;
int eleCount = 0;

long long hashkey(char* string, int size);
struct node* findInScope(char* string, int scope, long long index);
struct node* findInGlobal(char* string, int* scopes, long long index);
void insertToHash(char *string, int scope, long long hashIndex);
void display(int size);
void setSize(int size);

struct node
{
    char* string;
    int scope;
    struct node* next;

};

struct hash
{
    struct node **head;
    int count;
    void (*insertToHash)(char*, int, long long);
    void (*display)(int);
    void (*setSize)(int);
    long long (*hashkey)(char*, int);
    struct node* (*findInScope)(char*, int, long long);
    struct node* (*findInGlobal)(char* string, int* scopes, long long index);
};

 struct node * createNode(char *s, int scope)
 {
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->scope = scope;
    newnode->string = malloc(256);
    strcpy(newnode->string, s);
    newnode->next = NULL;
    return newnode;
  };

long long hashkey(char* string, int size)
{
    long long key;

	for (key = 1; *string;)
	{
		key = (key*(long long)(*string++)) % size;
	}
	return (key < 0 ? -key : key);
}

void setSize(int size)
{
   symbolTable = malloc(sizeof(*symbolTable));
   symbolTable->head = malloc(sizeof(struct node *)*size);
    for(size-1; size >= 0; size--)
        symbolTable->head[size] = NULL;
}

struct node* findInScope(char* string, int scope, long long index)
{
    struct node *myNode = NULL;
    if (symbolTable->head[index] == NULL)
    {
        return myNode;
    }
    myNode = symbolTable->head[index];
    while(myNode != NULL)
    {
        if((strcmp(myNode->string, string) == 0) && (myNode->scope == scope))
        {
            return myNode;
        }
        myNode = myNode->next;
    }
    return myNode;
}

struct node* findInGlobal(char* string, int* scopes, long long index)
{
    if (scopes == NULL)
    {
        return NULL;
    }
    struct node *myNode = NULL;
    int size = sizeof(scopes)/sizeof(*scopes);
    int i;
    for (i = 0; i < size; i++)
    {
        int scope = scopes[i];
        if ((myNode = findInScope(string, scope, index)) != NULL)
        {
            return myNode;
        }
    }
    return myNode;
}

 void insertToHash(char *string, int scope, long long hashIndex)
{
    struct node *newnode;
    newnode =  createNode(string, scope);

    if (!symbolTable->head[hashIndex])
        {
            symbolTable->head[hashIndex] = newnode;
            symbolTable->count = 1;
            return;
        }
    newnode->next = (symbolTable->head[hashIndex]);
    symbolTable->head[hashIndex] = newnode;
    symbolTable->count++;
    eleCount++;
  }

void display(int size)
{
    struct node *myNode;
    int i;
    for (i = 0; i < size; i++)
    {

        if (symbolTable->head[i])
        {
            myNode = symbolTable->head[i];
             printf("\nData at index %d in Symbol Table:\n", i,symbolTable->count);
            printf("String                 Scope\n");
            printf("-----------------------------\n");
            while (myNode != NULL)
            {
                printf("%-25s", myNode->string);
                printf("%i\n", myNode->scope);
                myNode = myNode->next;
            }
        }

    }
    return;
  }

#endif
