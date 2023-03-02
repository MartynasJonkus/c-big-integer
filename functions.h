#ifndef INC_1_ADS_BIGINTEGER_FUNCTIONS_H
#define INC_1_ADS_BIGINTEGER_FUNCTIONS_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int sign;
} BigInt;

Node* createNode(int data);
BigInt* create(char* str);
void freeBigInt(BigInt* bigInt);
int count(BigInt* bigInt);
int isEmpty(BigInt* bigInt);
char* toString(BigInt* bigInt);
BigInt* clone(BigInt* bigInt);
void makeEmpty(BigInt* bigInt);
BigInt* add(BigInt* bigInt1, BigInt* bigInt2);
BigInt* subtract(BigInt* bigInt1, BigInt* bigInt2);
void removeLeadingZeros(BigInt* bigInt);

#endif
