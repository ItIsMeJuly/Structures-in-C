#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "mystack.h"
#include "linked_list.h"

List* list;



void calculate(int numHandle, int operHandle)
{
    //double res = 0;
    float a, b;
    char operator;
    while(MystackNofElem(numHandle) != 0 && MystackNofElem(operHandle) != 0)
    {
        MystackPop(operHandle, &operator);
        switch (operator)
        {
        case '+':
            if(MystackNofElem(numHandle) == 1)
            {
                exit(EXIT_FAILURE);
            }
            MystackPop(numHandle, &a);
            MystackPop(numHandle, &b);
            float add = b + a;
            MystackPush(numHandle, &add);
            break;
        
        case '-':
            if(MystackNofElem(numHandle) == 1)
            {
                exit(EXIT_FAILURE);
            }
            MystackPop(numHandle, &a);
            MystackPop(numHandle, &b);
            float sub = b - a;
            MystackPush(numHandle, &sub);
            break;

        case '*':
            if(MystackNofElem(numHandle) == 1)
            {
                exit(EXIT_FAILURE);
            }
            MystackPop(numHandle, &a);
            MystackPop(numHandle, &b);
            float mul = a * b;
            MystackPush(numHandle, &mul);
            break;

        case '/':
            if(MystackNofElem(numHandle) == 1)
            {
                exit(EXIT_FAILURE);
            }
            MystackPop(numHandle, &a);
            MystackPop(numHandle, &b);
            float div = b / a;
            MystackPush(numHandle, &div);
            break;
        
        case 'S':
            MystackPop(numHandle, &a);
            float sq = a * a;
            MystackPush(numHandle, &sq);
            break;
        
        case 'R':
            MystackPop(numHandle, &a);
            float sqrt = sqrtf(a);
            MystackPush(numHandle, &sqrt);
            break;

        default:
            break;
        }
    }
}

#define FIRST 0

int main (/*int argc, char * argv[]*/)
{
    #if FIRST == 1
    int stack = MystackCreate(sizeof(int));

    list = InitializeList(sizeof(int));

    // add to list
    for(int i = 0 ; i < 2000 ; i++)
    {
        ListAdd(&list, &i);
    }

    // print
    for(int i = 0 ; i < GetSize(list) ; i++)
    {
        int* num = GetDataAtIndex(list, i);
        printf("%d", *num);
    }

    // push data to stack
    for(int i = GetSize(list) - 1 ; i >= 0 ; i--)
    {
        MystackPush(stack, GetDataAtIndex(list, i));
    }

    // clear list
    ClearList(list);

    int* num = malloc(sizeof(int));
    printf("\n");

    // pop out data
    int count = MystackNofElem(stack);
    for(int i = 0 ; i < count ; i++)
    {
        MystackPop(stack, num);
        ListAdd(&list, num);
    }

    // print list
    for(int i = 0 ; i < GetSize(list) ; i++)
    {
        int* num = GetDataAtIndex(list, 0);
        printf("%d", *num);
        ListRemove(&list);
    }
    MystackDestroy(stack);

    #else

    int numbers = MystackCreate(sizeof(float));
    int operators = MystackCreate(sizeof(char));

    char *buffer = malloc(50 * sizeof(char));

    printf("Enter expression: ");
    fgets(buffer, 50, stdin);
    
    char *token;

    char op;
    float num;

    token = strtok(buffer, " ");

    /* walk through other tokens */
    while (token != NULL)
    {
        int res = sscanf(token, "%f", &num);
        if (res == 0 || res == -1)
        {
            sscanf(token, "%c", &op);
            MystackPush(operators, &op);
        }
        else
        {
            MystackPush(numbers, &num);
        }

        token = strtok(NULL, " ");
    }

    calculate(numbers, operators);

    float res;
    MystackPop(numbers, &res);
    printf("%f", res);

    MystackDestroy(numbers);
    MystackDestroy(operators);

    #endif

    return 0;
}
