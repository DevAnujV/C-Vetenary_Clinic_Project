/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Anuj Verma
Student ID#: 180483216
Email      : averma100@myseneca.ca
Section    : NLL
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
int inputInt(void)
{
    int loop = 0;
    int value;
    char newLine = 'x';
    do
    {
        scanf("%d%c", &value, &newLine);
        if (newLine == '\n')
        {
            loop++;
            return value;
        }
        else
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
    } while (loop == 0);
    return value;
}
int inputIntPositive(void)
{
    int value1, loop1 = 0;
    do
    {
        scanf("%d", &value1);
        if (value1 > 0)
        {
            loop1++;
            return value1;
        }
        else
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (loop1 == 0);

    return value1;
}
int inputIntRange(int lowerRange, int higherRange)
{
    int record2, value2;
    do
    {
        record2 = scanf("%d", &value2);
        if (record2 == 0)
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else if (value2 < lowerRange || value2 > higherRange)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerRange, higherRange);
        }

    } while (value2 < lowerRange || value2 > higherRange);
    return value2;
}
char inputCharOption(const char cStringArray[])
{
    char inputChar;
    int flag = 0;
    int k;
    for (k = 0; k < 6 && flag == 0; k++)
    {
        int flag1 = 0;

        clearInputBuffer();
        scanf("%c", &inputChar);
        int i;
        for (i = 0; i < 6 && flag1 == 0; i++)
        {
            if (inputChar == cStringArray[i])
            {
                flag++;
                flag1++;
                return inputChar;
            }
        }

        if (flag1 == 0)
        {
            printf("ERROR: Character must be one of [qwErty]: ");
        }
    }
    return inputChar;
}
void inputCString(char* cString, int minchar, int maxchar)
{
    int count = 0, p = 0, j = 0, flag3 = 0;
    char newchar[20 + 1]; // check plz...................................................................
    clearInputBuffer();

    do
    {
        count = 0;
        scanf("%[^\n]", newchar);

        for (p = 0; newchar[p] != 0; p++)
        {
            count++;
        }
        p = 0;

        if (count >= minchar && count <= maxchar)
        {
            for (j = 0; j <= count; j++) 
            {
                cString[j] = newchar[j];
            }
            int n;
            for (n = 1; cString[count + n] != '\0'; n++)
            {
                cString[count + n] = '\0';
            }
            flag3++;
        }
        else
        {
            if (minchar == maxchar)
            {
                printf("ERROR: String length must be exactly %d chars: ", minchar);
            }
            else if (count > maxchar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxchar);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", minchar, maxchar);
            }
        }

        clearInputBuffer();

    } while (flag3 == 0);
}
void displayFormattedPhone(const char* arrayPh)
{
    int count = 0;
    int isNumber = 1;
    char* samplePhone = { "(___)___-____" };
    if (arrayPh == NULL)
    {
        printf("%s", samplePhone);
        return;
    }
    int j;
    for (j = 0; arrayPh[j] != '\0'; j++)
    {
        // 1. length 10
        count++;
        // 2. All should be numbers
        if (arrayPh[j] < '0' || arrayPh[j] > '9')  // it is not a number
        {
            isNumber = 0;
        }
    }
    if (count == 10 && isNumber == 1) {
        //Valid 10 length
        printf("(%c%c%c)%c%c%c-%c%c%c%c", arrayPh[0], arrayPh[1], arrayPh[2], arrayPh[3], arrayPh[4], arrayPh[5], arrayPh[6], arrayPh[7], arrayPh[8], arrayPh[9]);
    }
    else {
        printf("%s", samplePhone);
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
