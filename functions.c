#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

// Create a new node with the given data
Node* createNode(int data) {
    if (data < 0 || data > 9)
        return NULL;

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Create a new BigInt from the given string
BigInt* create(char* str) {
    if (str == NULL)
       return NULL;

    BigInt* newBigInt = (BigInt*) malloc(sizeof(BigInt));
    newBigInt->head = NULL;
    newBigInt->sign = 1;

    // Check if the number is negative
    if (str[0] == '-') {
        newBigInt->sign = -1;
        str++;
    }

    // Add each digit to the list
    int len = (int)strlen(str);
    Node* prev = NULL;
    for (int i = 0; i < len; i++) {
        Node* newNode = createNode(str[len - 1 - i] - '0');
        if (prev) {
            prev->next = newNode;
        } else {
            newBigInt->head = newNode;
        }
        prev = newNode;
    }

    return newBigInt;
}

// Free the memory used by the BigInt
void freeBigInt(BigInt* bigInt) {
   if (bigInt == NULL)
        return;

    Node* curr = bigInt->head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(bigInt);
}

// Count the number of nodes in the BigInt
int count(BigInt* bigInt) {
    if (bigInt == NULL)
        return 0;

    int count = 0;
    Node* curr = bigInt->head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

// Check if the BigInt is empty
int isEmpty(BigInt* bigInt) {
    return bigInt->head == NULL;
}

// Convert the BigInt to a string
char* toString(BigInt* bigInt) {
    if (bigInt == NULL)
        return NULL;

    int len = count(bigInt);
    char* str = (char*) malloc(len + 1);
    Node* curr = bigInt->head;
    for (int i = 0; i < len; i++) {
        str[len - 1 - i] = (char)(curr->data + '0');
        curr = curr->next;
    }
    str[len] = '\0';
    if (bigInt->sign == -1) {
        char* temp = (char*) malloc(len + 2);
        temp[0] = '-';
        strncpy(&temp[1], str, len + 1);
        free(str);
        return temp;
    }
    return str;
}

// Clone the BigInt
BigInt* clone(BigInt* bigInt) {
    if (bigInt == NULL)
       return NULL;

    BigInt *newBigInt = (BigInt *) malloc(sizeof(BigInt));
    newBigInt->head = NULL;
    newBigInt->sign = bigInt->sign;
    Node *curr = bigInt->head;
    Node *prev = NULL;
    while (curr) {
        Node *newNode = createNode(curr->data);
        if (prev) {
            prev->next = newNode;
        } else {
            newBigInt->head = newNode;
        }
        prev = newNode;
        curr = curr->next;
    }
    return newBigInt;
}

// Make the BigInt empty
void makeEmpty(BigInt* bigInt) {
    if (bigInt == NULL)
        return;

    Node* curr = bigInt->head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    bigInt->head = NULL;
    bigInt->sign = 1;
}

//Add two BigInts and return the result
BigInt* add(BigInt* bigInt1, BigInt* bigInt2) {
    if(bigInt1->head == NULL || bigInt2->head == NULL)
        return NULL;

    // If one of the BigInts is zero, return the other BigInt
    if (isEmpty(bigInt1)) {
        return clone(bigInt2);
    }
    if (isEmpty(bigInt2)) {
        return clone(bigInt1);
    }

    // If the signs of the BigInts are different, subtract the absolute values
    if (bigInt1->sign != bigInt2->sign) {
        BigInt* abs1 = clone(bigInt1);
        BigInt* abs2 = clone(bigInt2);
        abs1->sign = 1;
        abs2->sign = 1;
        BigInt* result = subtract(abs1, abs2);
        if (bigInt1->sign == -1) {
            result->sign = -1;
        }
        freeBigInt(abs1);
        freeBigInt(abs2);
        return result;
    }

    // Add the digits of the BigInts
    Node* curr1 = bigInt1->head;
    Node* curr2 = bigInt2->head;
    Node* prev = NULL;
    BigInt* result = (BigInt*) malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = bigInt1->sign;
    int carry = 0;
    while (curr1 || curr2 || carry) {
        int digit1 = curr1 ? curr1->data : 0;
        int digit2 = curr2 ? curr2->data : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum %= 10;
        Node* newNode = createNode(sum);
        if (prev) {
            prev->next = newNode;
        } else {
            result->head = newNode;
        }
        prev = newNode;
        if (curr1) {
            curr1 = curr1->next;
        }
        if (curr2) {
            curr2 = curr2->next;
        }
    }

    // If the result is zero, set the sign to positive
    if (isEmpty(result)) {
        result->sign = 1;
    }

    return result;
}

// Subtract two BigInts and return the result
BigInt* subtract(BigInt* bigInt1, BigInt* bigInt2) {
    if(bigInt1->head == NULL || bigInt2->head == NULL)
        return NULL;

    // If one of the BigInts is zero, return the negation of the other BigInt
    if (isEmpty(bigInt1)) {
        BigInt* result = clone(bigInt2);
        result->sign = -result->sign;
        return result;
    }
    if (isEmpty(bigInt2)) {
        return clone(bigInt1);
    }

    // If the signs of the BigInts are different, add the absolute values
    if (bigInt1->sign != bigInt2->sign) {
        BigInt* abs1 = clone(bigInt1);
        BigInt* abs2 = clone(bigInt2);
        abs1->sign = 1;
        abs2->sign = 1;
        BigInt* result = add(abs1, abs2);
        if (bigInt1->sign == -1) {
            result->sign = -1;
        }
        freeBigInt(abs1);
        freeBigInt(abs2);
        return result;
    }

    // Subtract the digits of the BigInts
    BigInt* abs1 = clone(bigInt1);
    BigInt* abs2 = clone(bigInt2);
    abs1->sign = 1;
    abs2->sign = 1;

    BigInt* result = (BigInt*) malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = bigInt1->sign;

    Node* curr1;
    Node* curr2;
    if(compareAbsolute(abs1, abs2) == -1){
        curr1 = abs2->head;
        curr2 = abs1->head;
        result->sign = -result->sign;
    }else{
        curr1 = abs1->head;
        curr2 = abs2->head;
    }
    Node* prev = NULL;
    int borrow = 0;

    while (curr1 || curr2) {
        int digit1 = curr1 ? curr1->data : 0;
        int digit2 = curr2 ? curr2->data : 0;
        int diff = digit1 - digit2 - borrow;

        borrow = 0;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        Node* newNode = createNode(diff);
        if (prev) {
            prev->next = newNode;
        } else {
            result->head = newNode;
        }
        prev = newNode;
        if (curr1) {
            curr1 = curr1->next;
        }
        if (curr2) {
            curr2 = curr2->next;
        }
    }

    // Remove leading zeros
    removeLeadingZeros(result);

    // If the result is zero, set the sign to positive
    if (isEmpty(result)) {
        result->sign = 1;
    }

    // Free memory
    freeBigInt(abs1);
    freeBigInt(abs2);

    return result;
}

int compareAbsolute(BigInt *num1, BigInt *num2) {
    if (count(num1) > count(num2))
        return 1;
    if (count(num1) < count(num2))
        return -1;

    Node *curr1 = num1->head;
    Node *curr2 = num2->head;
    int ret = 0;
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data > curr2->data) {
            ret = 1;
        }
        if (curr1->data < curr2->data) {
            ret = -1;
        }

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return ret;
}

// Remove leading zeros from a BigInt
void removeLeadingZeros(BigInt* bigInt) {
    if (bigInt->head == NULL)
        return;

    int indexOfZeros = 0;
    int indexOfNumber = 0;
    int isLeadingZero = 0;
    Node* curr = bigInt->head;
    while (curr) {
        ++indexOfNumber;
        if (curr->data == 0 && isLeadingZero == 0){
            isLeadingZero = 1;
            indexOfZeros = indexOfNumber;
        }
        if(curr->data != 0){
            isLeadingZero = 0;
            indexOfZeros = 0;
        }
        curr = curr->next;
    }

    curr = bigInt->head;
    if(isLeadingZero == 1){
        Node* prev = NULL;
        for (int i = 0; i < indexOfZeros - 2; ++i) {
            curr = curr->next;
        }

        while (curr){
            prev = curr;
            curr = curr->next;
            prev->next = NULL;
            free(prev);
        }
    }

    if (!bigInt->head) {
        bigInt->head = createNode(0);
    }
}