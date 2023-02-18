#include "linked_list.h"

#include <stdlib.h>

static Element* head = NULL;

/* function: ListAddTail
 * pre: -
 * post: an element is added to the end of the linked list
 * returns: 0 on success, -1 on fail
 */
int ListAddTail(int address, int size)
{
    Element* lastElement = head;
    while(lastElement != NULL && lastElement->next != NULL)
    {
        lastElement = lastElement->next;
    }
    Element* newElement = (Element*)malloc(sizeof(Element));
    if(newElement == NULL)
    {
        return -1;
    }
    newElement->address = address;
    newElement->size = size;
    newElement->next = NULL; 
    if(head == NULL)
    {
        head = newElement;
    }
    else
    {
        lastElement->next = newElement;
    }
    
    return 0;
}

/* function: ListAddAfter
 * pre: -
 * post: a new element with given data is added after element
 *       in the linked list. If element is NULL, the new element
 *       is added to the front of the list.
 * returns: 0 on success, -1 on fail
 */
int ListAddAfter(int address, int size, Element* element)
{
    Element* toBeFound = head;
    Element* newElement = (Element*)malloc(sizeof(Element));
    if(newElement == NULL)
    {
        return -1;
    }
    newElement->address = address;
    newElement->size = size;
    newElement->next = NULL;
    if(element == NULL)
    {
        newElement->next = head;
        head = newElement;
        return 0;
    }
    if(head == NULL)
    {
        head = newElement;
        return 0;
    }
    
    while(toBeFound->address != element->address)
    {
        toBeFound = toBeFound->next;
    }
    
    Element* afterToBeFound = toBeFound->next;
    toBeFound->next = newElement;
    newElement->next = afterToBeFound;
    
    
    return 0;
}


/* function: ListGetHead
 * pre: -
 * post: first element in linked list is returned
 * returns: first element on success, NULL if list is empty
 */
Element* ListGetHead()
{
    return head;
}


/* function: ListRemoveTail
 * pre: -
 * post: last element is removed from list
 * returns: 0 on success, -1 on fail
 */
int ListRemoveTail()
{
    if(head == NULL)
    {
        return -1;
    }

    Element* lastElement = head;
    Element* prevElement = NULL;

    while(lastElement->next != NULL)
    {
        prevElement = lastElement;
        lastElement = lastElement->next;
    }

    if(lastElement == NULL)
    {
        return -1;
    }

    free(lastElement);
    lastElement = NULL;
    prevElement->next = NULL;
    lastElement = head;

    if(!head)
    {
        head = NULL;
        return 0;
    }

    while(lastElement != NULL && lastElement->next != NULL)
    {
        lastElement = lastElement->next;
    }
    
    lastElement->next = NULL;

    return 0;
}

/* function: ListRemove
 * pre: -
 * post: element is removed from list, pointer from callee is made NULL
 * returns: 0 on success, -1 on fail
 */
int ListRemove(Element** element)
{
    if(head == NULL || element == NULL)
    {
        return -1;
    }

    Element* iterator = head;
    Element* prevElement = NULL;

    while(iterator != *element)
    {
        prevElement = iterator;
        iterator = iterator->next;
    }

    prevElement->next = iterator->next;
    free(*element);
    *element = NULL;
    element = NULL;

    return 0;
}

/* function: ListRemoveAll
 * pre: -
 * post: all existing elements from list are removed
 */
void ListRemoveAll()
{
    Element* toDelete = head;
    while(head)
    {
        toDelete = head;
        head = head->next;

        free(toDelete);
        toDelete->next = NULL;
        toDelete = NULL;
    }
}
