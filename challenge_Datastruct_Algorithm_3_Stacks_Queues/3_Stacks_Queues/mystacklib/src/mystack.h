#ifndef MYSTACK_H
#define MYSTACK_H

#include <stddef.h>

/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 * 
 * The usera are only allowed to use the stack API
 * that is defined below. 
 */

/* note: library comtains is non-reentrant code */


/* Creates a stack of c objects of sieze objsize and returns
 * a handle (number > 0 ) to the just created stack. On error, 
 * -1 is returned.
 */
int MystackCreate(size_t objsize);
/* Pushes an object to the stack identified by its handle
 * returns 0 on success and -1 on an error
 */
int MystackPush(int handle, void* obj);

int MystackPop(int handle, void* obj);
int MystackDestroy(int handle);
int MystackNofElem(int handle);

#endif /* __MSTACK_H__ */
