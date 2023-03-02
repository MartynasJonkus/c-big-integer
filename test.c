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

int TestingCompare(){

}

int TestingRemoveLeadingZeros(){


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

    assert(TestingToString("41234") == TRUE);
    assert(TestingToString("-2333") == TRUE);
    assert(TestingToString("442---11") == FALSE);
    assert(TestingToString("44,2+-11") == FALSE);

    assert(TestingAdd("-23", "10", "-13") == TRUE);
    assert(TestingAdd("-10", "-15", "-25") == TRUE);
    assert(TestingAdd("150", "200", "350") == TRUE);

    assert(TestingSub("-23", "10", "-33") == TRUE);
    assert(TestingSub("-30", "-15", "-15") == TRUE);
    assert(TestingSub("150", "200", "-50") == TRUE);
    assert(TestingSub("1500", "200", "1300") == TRUE);




    
}