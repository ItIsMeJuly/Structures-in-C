#include "unity.h"
#include "linked_list.h"
#include "memory.h"
#include <stdint.h>
#include <stdbool.h>

// I rather dislike keeping line numbers updated, so I made my own
// macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}


// TODO:
//  - Rename and change this test to something usefull
//  - Add more tests
//  - Remove this comment :)
// Should you need a list of all TEST_ASSERT macros: take a look
// at unity.h
void test_EmptyTest(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}


/*************************************************************
 *  Start of Linked List Tests 
 *************************************************************/

void test_InitializeList()
{
    List* elem = InitializeList(8);
    TEST_ASSERT_TRUE(elem->head == NULL);
    TEST_ASSERT_EQUAL(elem->size, 8);

    free(elem);
}


void test_ListAdd()
{
    List* list = InitializeList(8);
    int a = 10;
    ListAdd(&list, &a);
    TEST_ASSERT_TRUE(list->head->data == &a);
    TEST_ASSERT_EQUAL(list->count, 1);

    DestroyList(list);
}

void test_ListAddAtIndex()
{
    List* list = InitializeList(8);
    int a = 10;
    int b = 1;
    ListAdd(&list, &a);
    ListAdd(&list, &a);
    ListAdd(&list, &a);
    ListAdd(&list, &a);

    ListAddAtIndex(&list, 1, &b);

    TEST_ASSERT_TRUE(list->head->next->next->data == &a);
    TEST_ASSERT_TRUE(list->head->next->data == &b);

    DestroyList(list);
}

void test_ListRemove()
{
    List* list = InitializeList(8);
    int a = 10;
    int b = 5;
    int c = 1;
    ListAdd(&list, &a);
    ListAdd(&list, &b);
    ListAdd(&list, &c);
    ListAdd(&list, &a);

    ListRemove(&list);

    TEST_ASSERT_TRUE(list->head->data == &c);

    DestroyList(list);
}

void test_ListRemoveAtIndex()
{
    List* list = InitializeList(8);
    int a = 10;
    int b = 5;
    int c = 1;
    ListAdd(&list, &a);
    ListAdd(&list, &b);
    ListAdd(&list, &c);
    ListAdd(&list, &a);

    ListRemoveAtIndex(&list, 1);

    TEST_ASSERT_TRUE(list->head->next->data == &b);

    DestroyList(list);
}


void test_GetDataAtIndex()
{
    List* list = InitializeList(8);
    int a = 10;
    int b = 5;
    int c = 1;
    ListAdd(&list, &a);
    ListAdd(&list, &b);
    ListAdd(&list, &c);
    ListAdd(&list, &a);

    void* res = GetDataAtIndex(list, 2);

    TEST_ASSERT_TRUE(res == &b);

    DestroyList(list);
}

int main(/*int argc, char* argv[]*/)
{
    UnityBegin();

    MY_RUN_TEST(test_EmptyTest);

    MY_RUN_TEST(test_InitializeList);
    MY_RUN_TEST(test_ListAdd);
    MY_RUN_TEST(test_ListAddAtIndex);
    MY_RUN_TEST(test_ListRemove);
    MY_RUN_TEST(test_ListRemoveAtIndex);
    MY_RUN_TEST(test_GetDataAtIndex);

    return UnityEnd();
}
