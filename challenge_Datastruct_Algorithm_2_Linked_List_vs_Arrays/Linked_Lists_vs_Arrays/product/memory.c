#include "memory.h"
#include "linked_list.h"
#include <stdbool.h>

#define FREE_MEM_ADDRS  100

static const int StartAddress = 1000;


struct memory
{
    int address;
    int size;
};

typedef struct memory Memory;





List *allocList = NULL;
List *freeList = NULL;


/* function: ConstructMemory
 * pre: -
 * post: memory administration is constructed 
 */
void ConstructMemory(int size)
{
    freeList = InitializeList(sizeof(Memory));
    allocList = InitializeList(sizeof(Memory));

    Memory *element = (Memory *)malloc(freeList->size);
    element->address = StartAddress;
    element->size = size;

    ListAdd(&freeList, element);
}

/* function: DestructMemory
 * pre: -
 * post: memory administration is destructed
 */
void DestructMemory()
{
    DestroyList(allocList);
    DestroyList(freeList);
}

/* function: PrintList
 * pre: -
 * post: if stream is valid, list information is printed to stream and 0 is returned
 *       if stream is NULL, -1 is returned
 */
int PrintList(FILE *stream)
{
    if (stream == NULL)
    {
        return -1;
    }
    printf("FreeList:\n---------\n");

    if (IsEmpty(freeList))
    {
        printf(" <empty> \n");
    }
    else
    {
        for (size_t i = 0; i < GetSize(freeList); i++)
        {
            Memory *element = GetDataAtIndex(freeList, i);
            fprintf(stream, "%3ld: addr:%d  size: %3d\n", i, element->address, element->size);
        }
    }

    printf("AllocList:\n----------\n");
    if (IsEmpty(allocList))
    {
        printf(" <empty> \n");
    }
    else
    {
        for (size_t i = 0; i < GetSize(allocList); i++)
        {
            Memory *element = GetDataAtIndex(allocList, i);
            fprintf(stream, "%3ld: addr:%d  size: %3d\n", i, element->address, element->size);
        }
    }

    return 0;
}

/* function: ClaimMemory
 * pre: nrofBytes > 0
 * post: if no memory block of nrofBytes available return -1
 *       otherwise the first block that is large enough is claimed and the start address is returned
 */
int ClaimMemory(int nrofBytes)
{
    int addr = 0;

    if (nrofBytes > 100)
    {
        return -1;
    }

    if (GetHead(allocList) == NULL)
    {
        Memory *element = (Memory *)malloc(sizeof(Memory));
        element->address = StartAddress;
        element->size = nrofBytes;

        ListAdd(&allocList, element);

        addr = StartAddress;
    }
    else
    {
        Memory *element = (Memory *)malloc(sizeof(Memory));
        element->size = nrofBytes;

        Memory *headMemory = GetDataAtIndex(allocList, 0);
        if (element->size + StartAddress <= headMemory->address)
        {
            element->address = StartAddress;
            ListAdd(&allocList, element);
        }
        else
        {

            for (size_t i = 0; i < GetSize(allocList); i++)
            {
                Memory *first = GetDataAtIndex(allocList, i);
                Memory *second = GetDataAtIndex(allocList, i + 1);

                if (second == NULL)
                {
                    if (first->address + first->size + element->size <= (int)(StartAddress + FREE_MEM_ADDRS))
                    {
                        element->address = first->address + first->size;
                        ListAddAtIndex(&allocList, i + 1, element);
                        break;
                    }
                    return -1;
                }

                if (second->address >= first->address + first->size + element->size)
                {
                    element->address = first->address + first->size;
                    ListAddAtIndex(&allocList, i + 1, element);
                    break;
                }
            }
        }

        addr = element->address;
    }



    for (size_t i = 0; i < GetSize(freeList); i++)
    {
        Memory *first = GetDataAtIndex(freeList, i);

        if (first->address == addr)
        {
            if (first->size > nrofBytes)
            {
                first->size -= nrofBytes;
                first->address += nrofBytes;
            }
            else if (first->size == nrofBytes)
            {
                ListRemoveAtIndex(&freeList, i);
            }
            break;
        }
    }
    return addr;
}

/* function: FreeMemory
 * pre: Parameter addr must match the start of an allocatd memory block. Otherwhise return -1.
 * post: Memory is freed and the number of freed bytes is returned
 *
 */
int FreeMemory(int addr)
{
    size_t index = 0;
    if (allocList == NULL)
    {
        return -1;
    }

    if (CheckValidAddress(allocList, addr, &index) != 0)
    {
        return -1;
    }

    Memory *elem = GetDataAtIndex(allocList, index);
    int sizeOfBlock = elem->size;
    ListRemoveAtIndex(&allocList, index);


    if (freeList != NULL)
    {
        Memory *element = (Memory *)malloc(sizeof(Memory));
        element->size = sizeOfBlock;
        element->address = addr;

        if (GetHead(freeList) == NULL)
        {
            ListAdd(&freeList, element);
            return sizeOfBlock;
        }
        Memory *first = GetDataAtIndex(freeList, 0);

        if (addr + sizeOfBlock <= first->address)
        {
            ListAdd(&freeList, element);
        }
        else
        {
            for (size_t i = 0; i < GetSize(freeList); i++)
            {
                Memory *first = GetDataAtIndex(freeList, i);
                Memory *second = GetDataAtIndex(freeList, i + 1);

                if (second == NULL)
                {
                    ListAddAtIndex(&freeList, i + 1, element);
                    break;
                }

                if (first->address < addr && addr < second->address)
                {
                    ListAddAtIndex(&freeList, i + 1, element);
                    break;
                }
            }
        }
    }

    MergeBlocks(&freeList);

    return sizeOfBlock;
}

int CheckValidAddress(List *list, int addr, size_t *index)
{
    if (list == NULL || GetHead(list) == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < GetSize(list); i++)
    {
        Memory *element = GetDataAtIndex(list, i);
        if (element->address == addr)
        {
            *index = i;
            return 0;
        }
    }
    return -1;
}

void MergeBlocks(List **list)
{

    if (list == NULL || *list == NULL || GetHead(*list) == NULL)
    {
        return;
    }

    List *ref = *list;

    for (size_t i = 0; i < GetSize(ref); i++)
    {
        Memory *first = GetDataAtIndex(ref, i);
        Memory *second = GetDataAtIndex(ref, i + 1);

        if (second == NULL)
        {
            return;
        }

        if (first->address + first->size == second->address)
        {
            first->size += second->size;
            ListRemoveAtIndex(list, i + 1);
            MergeBlocks(list);
        }
    }
}