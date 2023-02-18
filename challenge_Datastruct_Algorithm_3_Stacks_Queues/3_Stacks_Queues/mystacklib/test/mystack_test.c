#include <string.h>
#include <stdio.h>

#include "mystack.h"
#include "unity.h"

#include <stdlib.h>

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp()
{
}

void tearDown()
{
    // This is run after EACH test
}

// TODO:
//  - Rename and change this test to something usefull
//  - Add more tests
//  - Remove this comment :)
// Should you need a list of all TEST_ASSERT macros: take a look
// at unity.h
void test_EmptyTest()
{
    TEST_ASSERT_EQUAL(1, 1);
}

void test_MystackCreate1()
{
    int handle = MystackCreate(20);

    TEST_ASSERT_EQUAL(1, handle);

    MystackDestroy(handle);
}

void test_MystackCreate2()
{
    int handle = MystackCreate(20);
    int handle1 = MystackCreate(20);
    int handle2 = MystackCreate(20);

    TEST_ASSERT_EQUAL(2, handle);
    TEST_ASSERT_EQUAL(3, handle1);
    TEST_ASSERT_EQUAL(4, handle2);

    MystackDestroy(handle);
    MystackDestroy(handle1);
    MystackDestroy(handle2);
}



void test_push_pop1()
{
    int handle = MystackCreate(sizeof(int));

    int a = 10, b = 12;
    int* pa = &a, *pb = &b;

    MystackPush(handle, pa);
    MystackPush(handle, pb);

    int res = 0;
    MystackPop(handle, &res);

    TEST_ASSERT_EQUAL(12, res);

    MystackDestroy(handle);
}

void test_push_pop2()
{
    int handle = MystackCreate(sizeof(int));

    int a = 10, b = 12;
    int* pa = &a, *pb = &b;

    MystackPush(handle, pa);
    MystackPush(handle, pb);

    int res = 0;
    MystackPop(handle, &res);
    MystackPop(handle, &res);

    TEST_ASSERT_EQUAL(10, res);

    MystackPush(handle, pa);
    MystackPop(handle, &res);

    TEST_ASSERT_EQUAL(10, res);

    MystackDestroy(handle);
}

void test_MystackNofElem()
{
    int handle = MystackCreate(4);
    int a = 4, b = 2, c = 7;

    MystackPush(handle, &a);
    MystackPush(handle, &b);
    MystackPush(handle, &c);

    int count = MystackNofElem(handle);

    TEST_ASSERT_EQUAL(3, count);

    MystackDestroy(handle);
}

int main()
{
    UnityBegin();

    MY_RUN_TEST(test_EmptyTest);
    MY_RUN_TEST(test_MystackCreate1);
    MY_RUN_TEST(test_MystackCreate2);
    MY_RUN_TEST(test_push_pop1);
    MY_RUN_TEST(test_push_pop2);
    MY_RUN_TEST(test_MystackNofElem);

    return UnityEnd();
}
