#include "mystack.h"
#include "logging.h"

#include <stdlib.h>
#include <string.h>

/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

typedef struct stackObject
{
	void* obj;
	struct stackObject* next;
} StackObject_t;

typedef struct stackMeta
{
	StackObject_t* stack;
	size_t objsize;
	int numelem;
	int handle;
	struct stackMeta* next;
} StackMeta_t;

StackMeta_t* gStackList = NULL;


/*
 * Function creates a new Node with an empty stack (NULL)
 */
int MystackCreate(size_t objsize)
{
    /* Hint: use gStackList */
    static int handle = 0;
    handle += 1;
    DBG_PRINTF("Created stack with handle: %d and objsize %zu bytes\n", handle, objsize);

    StackMeta_t* obj = malloc(sizeof(StackMeta_t));
    obj->handle = handle;
    obj->numelem = 0;
    obj->objsize = objsize;
    obj->next = NULL;
    obj->stack = NULL;

    if(gStackList == NULL)
    {
        gStackList = obj;
    }
    else
    {
        obj->next = gStackList;
        gStackList = obj;
    }
    
    return handle;
}

int MystackPush(int handle, void* obj)
{
    DBG_PRINTF("handle push: %d\n, obj: %p\n", handle, obj); 	

    StackMeta_t* traverse = gStackList;

    // traversal
    {
        while (traverse != NULL && handle != traverse->handle)
        {
            traverse = traverse->next;
        }

        // no such handle
        if (traverse == NULL)
        {
            return -1;
        }
    }

    StackObject_t* newObj = malloc(sizeof(StackObject_t));
    newObj->next = NULL;
    newObj->obj = malloc(sizeof(traverse->objsize));

    memcpy(newObj->obj, obj, traverse->objsize);

    if(traverse->stack == NULL)
    {
        traverse->stack = newObj;
    }
    else
    {
        newObj->next = traverse->stack;
        traverse->stack = newObj;
    }
    

    return 0;
}

int MystackPop(int handle, void* obj)
{
    DBG_PRINTF("handle pop: %d\n, obj: %p\n", handle, obj); 

    StackMeta_t* traverse = gStackList;

    // traversal
    {
        while (traverse != NULL && handle != traverse->handle)
        {
            traverse = traverse->next;
        }

        // no such handle
        if (traverse == NULL)
        {
            return -1;
        }
    }

    StackObject_t* delete = traverse->stack;

    memcpy(obj, traverse->stack->obj, traverse->objsize);
    traverse->stack = traverse->stack->next;

    free(delete->obj);
    free(delete);

    return 0;
}

int MystackDestroy(int handle)
{
    DBG_PRINTF("handle: %d\n", handle); 	

    StackMeta_t* traverse = gStackList;
    StackMeta_t* prev = NULL;

    // traversal
    {
        while (traverse != NULL)
        {
            if(handle == traverse->handle)
            {
                break;
            }

            traverse = traverse->next;
            prev = traverse;
        }

        // no such handle
        if (traverse == NULL)
        {
            return -1;
        }
    }


    // destroy stack
    {
        StackObject_t *head = traverse->stack;
        StackObject_t *delete = NULL;

        while (head != NULL)
        {
            delete = head;
            head = head->next;
            free(delete->obj);
            free(delete);
        }

        delete = NULL;
        traverse->stack = NULL;
    }

    // destroy list node
    {
        StackMeta_t* delete = traverse;

        if(MystackNofElem(handle) == 0)
        {
            traverse = traverse->next;
        }
        else
        {
            prev->next = traverse->next;
        }

        delete->next = NULL;
        free(delete);
        delete = NULL;
    }   

    return 0;
}

int MystackNofElem(int handle)
{
    DBG_PRINTF("handle: %d\n", handle);

    StackMeta_t* traverse = gStackList;

    while (traverse != NULL)
    {
        if (handle == traverse->handle)
        {
            break;
        }

        traverse = traverse->next;
    }

    // no such handle
    if (traverse == NULL)
    {
        return -1;
    }

    StackObject_t* head = traverse->stack;
    int count = 0;

    while(head != NULL)
    {
        count += 1;
        head = head->next;
    }

    return count;
}
