#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "functions.h"

#define TRUE 1
#define FALSE 0


int TestingCreate(char* var)
{
    BigInt* num = create(var);
    int numLength = strlen(var);
    char* numText = (char*) malloc(numLength * sizeof(char));
    Node* temp = num->head;

    if((num->sign == 1 && var[0] == '-') || (num->sign == -1 && var[0] != '-')){
        return FALSE;
    }else{
        int i = 0;
        if(num->sign == -1){
            numText[0] = '-';
        }
        while(temp){
            numText[numLength - i - 1] = temp->data + '0';
            ++i;
            temp = temp->next;
        }
    }

    for(int i = 0; i < numLength; ++i){
        if(var[i] != numText[i]){
            return FALSE;
        }
    }

    freeBigInt(num);
    free(numText);
    free(temp);
    return TRUE;
}

int TestingCount(char* var){
    BigInt* num = create(var);
    int digitCount = count(num);

    freeBigInt(num);

    return digitCount;
}

int TestingToString(char *var)
{
    BigInt* num = create(var);
    char* numText = toString(num);
    if(strlen(var) != strlen(numText)) return FALSE;

    for(int i = 0; i < strlen(var); ++i)
    {
        if(var[i] != numText[i])
        {
            return FALSE;
        }
    }
    freeBigInt(num);
    free(numText);
    return TRUE;
}

int TestingAdd(char* var1, char* var2, char* answ)
{
    BigInt* num1 = create(var1);
    BigInt* num2 = create(var2);
    BigInt* result = add(num1, num2);
    char* resultText = toString(result);

    if(strlen(answ) != strlen(resultText)) return FALSE;

    for(int i = 0; i < strlen(answ); ++i){
        if(answ[i] != resultText[i]){
            return FALSE;
        }
    }

    freeBigInt(num1);
    freeBigInt(num2);
    freeBigInt(result);
    free(resultText);

    return TRUE;
}

int TestingSub(char* var1, char* var2, char* answ)
{
    BigInt* num1 = create(var1);
    BigInt* num2 = create(var2);
    BigInt* result = subtract(num1, num2);
    char* resultText = toString(result);

    if(strlen(answ) != strlen(resultText)) return FALSE;

    for(int i = 0; i < strlen(answ); ++i){
        if(answ[i] != resultText[i]){
            return FALSE;
        }
    }

    freeBigInt(num1);
    freeBigInt(num2);
    freeBigInt(result);
    free(resultText);

    return TRUE;
}

int TestingCompareAbs(char* var1, char* var2){
    BigInt* num1 = create(var1);
    BigInt* num2 = create(var2);
    int res = compareAbsolute(num1, num2);

    freeBigInt(num1);
    freeBigInt(num2);

    return res;
}

int TestingRemoveLeadingZeros(char* var1, char* var2){
    BigInt* num = create(var1);
    removeLeadingZeros(num);
    char* numText = toString(num);

    if(strlen(var2) != strlen(numText)) return FALSE;

    for(int i = 0; i < strlen(var2); ++i){
        if(var2[i] != numText[i]){
            return FALSE;
        }
    }

    freeBigInt(num);
    free(numText);
    return TRUE;
}

int TestingClone(char* var){
    BigInt* num = create(var);
    BigInt* newNum = clone(num);
    char* newNumText = toString(num);
    if(strlen(var) != strlen(newNumText)) return FALSE;

    for(int i = 0; i < strlen(var); ++i){
        if(var[i] != newNumText[i]){
            return FALSE;
        }
    }

    freeBigInt(num);
    freeBigInt(newNum);
    free(newNumText);

    return TRUE;
}

int main()
{

    assert(TestingCreate("12334466") == TRUE);
    assert(TestingCreate("-22212334466") == TRUE);
    assert(TestingCreate("-2sader") == FALSE);
    assert(TestingCreate("0") == TRUE);

    assert(TestingCount("444555") == 6);
    assert(TestingCount("-2244") == 4);
    assert(TestingCount("0") == 1);
    assert(TestingCount(NULL) == 0);

    assert(TestingToString("41234") == TRUE);
    assert(TestingToString("-2333") == TRUE);
    assert(TestingToString("442---11") == FALSE);
    assert(TestingToString("44,2+-11") == FALSE);

    assert(TestingAdd("-23", "10", "-13") == TRUE);
    assert(TestingAdd("-10", "-15", "-25") == TRUE);
    assert(TestingAdd("150", "200", "350") == TRUE);
    assert(TestingAdd("70", "120", "-50") == FALSE);

    assert(TestingSub("-23", "10", "-33") == TRUE);
    assert(TestingSub("-30", "-15", "-15") == TRUE);
    assert(TestingSub("150", "200", "-50") == TRUE);
    assert(TestingSub("1500", "200", "1300") == TRUE);
    assert(TestingSub("340", "100", "440") == FALSE);


    assert(TestingCompareAbs("1333", "1200") == 1);
    assert(TestingCompareAbs("14", "14") == 0);
    assert(TestingCompareAbs("0","100") == -1);

    assert(TestingClone("1111") == TRUE);

    assert(TestingRemoveLeadingZeros("000100234","100234") == TRUE);
    assert(TestingRemoveLeadingZeros("000234","0234") == FALSE);

    FILE *file_ptr = fopen("test.txt", "w"); // open file for writing
    if (file_ptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(file_ptr, "All tests passed!\n"); // print message to file

    fclose(file_ptr); // close file
    return 0;
}