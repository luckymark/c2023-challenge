#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10000
#define SCALE 150000
#define ARRINIT(x) memset(x, 0, sizeof(x))

typedef struct {
    int len;
    int data[MAX_DIGITS];
} BigInt;

void multiply(BigInt* a, int b, BigInt* result) {
    int carry = 0;
    for (int i = 0; i < a->len; i++) {
        int temp = a->data[i] * b + carry;
        result->data[i] = temp % SCALE;
        carry = temp / SCALE;
    }
    if (carry != 0) {
        result->data[a->len] = carry;
        result->len = a->len + 1;
    } else {
        result->len = a->len;
    }
}

void divide(BigInt* a, int b, BigInt* quotient, int* remainder) {
    ARRINIT(quotient->data);
    quotient->len = 0;
    *remainder = 0;

    for (int i = 0; i < a->len; i++) {
        int temp = *remainder * SCALE + a->data[i];
        quotient->data[i] = temp / b;
        *remainder = temp % b;
    }
    quotient->len = a->len;
    while (quotient->len > 1 && quotient->data[quotient->len - 1] == 0) {
        quotient->len--;
    }
}

void subtract(BigInt* a, BigInt* b, BigInt* result) {
    int borrow = 0;
    for (int i = 0; i < a->len || i < b->len || borrow != 0; i++) {
        if (i < a->len) {
            a->data[i] -= borrow;
        }
        if (i < b->len) {
            a->data[i] -= b->data[i];
        }
        borrow = (a->data[i] < 0) ? 1 : 0;
        a->data[i] = (a->data[i] + SCALE) % SCALE;
    }
    result->len = a->len;
    while (result->len > 1 && result->data[result->len - 1] == 0) {
        result->len--;
    }
    memcpy(result->data, a->data, sizeof(int) * result->len);
}

void output(BigInt* num) {
    printf("%d.", num->data[0]);
    for (int i = 1; i < num->len; i++) {
        printf("%04d", num->data[i]);
    }
    printf("\n");
}

int main() {
    BigInt a, b, ar, br, t1, t2, t3;
    int k = 1;
    a.len = 1;
    a.data[0] = SCALE - 1;  // Initialize a with 9999...9999 (SCALE-1 digits of 9)
    b.len = 1;
    b.data[0] = 2 * SCALE + 3;  // Initialize b with 20003 (2 * SCALE + 3)
    arrinit(&ar);  // Temporary variables for multiplication and division operations. Initialize them to zero.
    arrinit(&br);  // Temporary variables for multiplication and division operations. Initialize them to zero.
    BigInt piResult;  // To store the calculated value of pi. Initialize it to zero. piResult is our final result. It is printed at the end.
    arrinit(&piResult); // Temporary variables for subtraction operation. Initialize them to zero. 
    arrinit(&t1); arrinit(&t2); arrinit(&t3); 
    while (k <= MAX_DIGITS) { multiply(&a, k, &t1); 
    }
    return 0;
    }
    
