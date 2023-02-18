#include "linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


List *InitializeList(size_t size)
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->size = size;
    list->count = 0;

    return list;
}

int DestroyList(List *list)
{
    if (list == NULL || list->head == NULL)
    {
        return -1;
    }

    ClearList(list);

    free(list);
    list = NULL;

    return 0;
}

int ListAdd(List **list, void *data)
{
    if (list == NULL || *list == NULL || data == NULL)
    {
        return -1;
    }

    Node *element = (Node *)malloc(sizeof(Node));
    element->data = data;
    element->next = NULL;

    if ((*list)->head != NULL)
    {
        element->next = (*list)->head;
        (*list)->head = element;
    }
    else if ((*list)->head == NULL)
    {
        (*list)->head = element;
    }

    (*list)->count += 1;
    return 0;
}

int ListAddAtIndex(List **list, size_t index, void *data)
{
    if (list == NULL || *list == NULL || (*list)->head == NULL || data == NULL)
    {
        return -1;
    }

    Node *element = (Node *)malloc(sizeof(Node));
    element->data = data;
    element->next = NULL;

    Node *insertBefore = (*list)->head;
    Node *prev = NULL;

    // get to the correct element
    for (size_t i = 0; i < index; i++)
    {
        prev = insertBefore;
        insertBefore = insertBefore->next;
        if (prev == NULL)
        {
            return -1;
        }
    }

    if (insertBefore == prev)
    {
        ListAdd(list, data);
    }
    else if (insertBefore == NULL && prev != NULL)
    {
        prev->next = element;
    }
    else
    {
        prev->next = element;
        element->next = insertBefore;
    }

    (*list)->count += 1;
    return 0;
}

int ListRemove(List **list)
{
    if (list == NULL || *list == NULL || (*list)->head == NULL)
    {
        return -1;
    }

    Node *delete = (*list)->head;
    (*list)->head = delete->next;


    free(delete);
    delete = NULL;

    (*list)->count -= 1;
    return 0;
}


int ListRemoveAtIndex(List** list, size_t index)
{
    if (list == NULL || *list == NULL || (*list)->head == NULL)
    {
        return -1;
    }

    if(index == 0)
    {
        int res = ListRemove(list);
        return res;
    }

    Node *trav = (*list)->head;
    Node *prev = NULL;

    for (size_t i = 0; i < index; i++)
    {
        prev = trav;
        trav = trav->next;
        if (trav == NULL)
        {
            return -1;
        }
    }

    Node* delete = trav;
    prev->next = trav->next;

    free(delete);
    delete = NULL;

    (*list)->count -= 1;
    return 0;
}


void* GetDataAtIndex(List* list, size_t index)
{
    if (list == NULL || list->head == NULL)
    {
        return NULL;
    }

    Node* trav = list->head;

    for(size_t i = 0 ; i < index ; i++)
    {
        trav = trav->next;
        if(trav == NULL)
        {
            return NULL;
        }
    }

    return trav->data;
}

int ClearList(List* list)
{
    if (list == NULL || list->head == NULL)
    {
        return -1;
    }

    Node *head = list->head;
    Node *toDelete = head;

    while (head != NULL)
    {
        head = head->next;
        free(toDelete);
        toDelete = head;
    }

    return 0;
}

size_t GetSize(List* list)
{
    if (list == NULL || list->head == NULL)
    {
        return -1;
    }

    return list->count;
}

bool IsEmpty(List* list)
{
    if(list->head != NULL)
    {
        return false;
    }
    return true;
}


Node* GetHead(List* list)
{
    return list->head;
}
