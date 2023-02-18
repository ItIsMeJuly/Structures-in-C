#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node
{
  void* data;
  struct node* next;
}Node;

typedef struct 
{
    Node* head;
    size_t size;
    size_t count;
}List;


List* InitializeList(size_t size);
int DestroyList(List* lsit);

void* GetDataAtIndex(List* list, size_t index);

int ListAdd(List** list, void* data);
int ListAddAtIndex(List** list, size_t index, void* data);

int ListRemove(List** list);
int ListRemoveAtIndex(List** list, size_t index);

int ClearList(List* list);

size_t GetSize(List* list);
Node* GetHead(List* list);
bool IsEmpty(List* list);

#endif