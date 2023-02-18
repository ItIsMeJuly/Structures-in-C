#include "linked_list.h"

#include <stdio.h>

/* function: PrintAllElements
 * pre: -
 * post: all elements in the linked list are printed to stdout
 * output if list empty:
 *   <empty>
 * output if list contains elements is one line for each element:
 * nnn:  addr:xxxx  size:yyyy
 * where: nnn: 3 digit element number, starting at 0, xxxx is a 4 digit
 *        address and yyyy is a 4 digit size. All numbers are
 *        aligned to the right:
 *          8:  addr:  20  size:   1
 *          9:  addr: 100  size: 140
 *         10:  addr:1010  size:  80
 */
static void PrintAllElements()
{
    Element* head = ListGetHead();
    int index = 0;
    while(head != NULL){
        printf("%d: addr: %d size: %d\n", index, head->address, head->size);
        head = head->next;
        index++;
    }
}

int main()
{
    printf("At start of program, the list is:\n");
    PrintAllElements();

    // Adding first element should be possible in both ways:
    // Test them both, but not together!
    // ListAddTail(100, 5);
    // or:
    // ListAddAfter(100, 5, NULL);
    ListAddTail(100, 5);
    
    ListAddTail(200, 10);
    ListAddTail(300, 8);
    printf("\nAfter adding 3 elements:\n");
    PrintAllElements();

    Element* temp = ListGetHead()->next;
    ListAddAfter(250, 50, temp);
    printf("\nAfter adding 4th element just after the one on address 200:\n");
    PrintAllElements();

    ListAddAfter(99, 1, NULL);
    printf("\nAfter adding 5th element before 100:\n");
    PrintAllElements();

    ListRemoveTail();
    printf("\nAfter removing tail (address 300):\n");
    PrintAllElements();

    temp = ListGetHead()->next;
    ListRemove(&temp);
    printf("\nAfter removing 2nd element (address 100):\n");
    PrintAllElements();
    printf("Temp is now: %p. Temp should be NULL, printed as (nil)\n", temp);

    ListRemoveAll();
    printf("\nAfter removing all:\n");
    PrintAllElements();

    printf("\n");
    return 0;
}
