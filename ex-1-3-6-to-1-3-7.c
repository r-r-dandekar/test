/******************************************************************************/
/**           For Exercise 1.3.6 and 1.3.7 of Data Structures in C           **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  Rational Numbers                                            */
/*                                                                            */
/* Date        :  02-07-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* Using the rational number representation given in the text, adds routines  */
/* to add, subtract and divide such numbers, and to test equality by first    */
/* equalizing denominators and then comparing                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct rational {
    int numerator;
    int denominator;

} RATIONAL;

void reduce(RATIONAL *inrat, RATIONAL *outrat);

int equal(RATIONAL *rat1, RATIONAL *rat2);
int equal2(RATIONAL *rat1, RATIONAL *rat2);

void add(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3);
void subtract(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3);
void multiply(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3);
void divide(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3);

/* reduce:  reduces a RATIONAL to its lowest term */
void reduce(RATIONAL *inrat, RATIONAL *outrat)
{
    int a, b, rem;

    if (inrat->numerator > inrat->denominator) {
        a = inrat->numerator;
        b = inrat->denominator;
    }
    else {
        a = inrat->denominator;
        b = inrat->numerator;
    }
    while (b != 0) {
        rem = a%b;
        a = b;
        b = rem;
    }

    outrat->numerator = inrat->numerator / a;
    outrat->denominator = inrat->denominator / a;

    if (outrat->denominator < 0)
    {
        outrat->numerator *= -1;
        outrat->denominator *= -1;
    }
}

/* equal: checks if two RATIONALs are equal            */
/*        returns 1 if they are equal, and 0 otherwise */
int equal(RATIONAL *rat1, RATIONAL *rat2)
{
    RATIONAL r1, r2;

    reduce(rat1, &r1);
    reduce(rat2, &r2);
    if (r1.numerator == r2.numerator &&
        r1.denominator == r2.denominator)
            return TRUE;

    return FALSE;
}
/* equal2: checks if two RATIONALs are equal by an alt. method */
/*                returns 1 if they are equal, and 0 otherwise */
int equal2(RATIONAL *rat1, RATIONAL *rat2)
{
    RATIONAL r1, r2;

    reduce(rat1, &r1);
    reduce(rat2, &r2);

    r1.numerator *= r2.denominator;
    r1.denominator *= r2.denominator;
    r2.numerator *= r1.denominator;
    r2.denominator *= r1.denominator;

    if (r1.numerator == r2.numerator &&
        r1.denominator == r2.denominator)
            return TRUE;

    return FALSE;
}

/* add: adds two RATIONALs and stores result in &r3 */
void add(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3)
{
    RATIONAL rat3;
    rat3.numerator = r1->numerator*r2->denominator + r2->numerator*r1->denominator;
    rat3.denominator = r1->denominator*r2->denominator;

    reduce(&rat3, r3);
}
/* subtract: subtracts two RATIONALs and stores result in &r3 */
void subtract(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3)
{
    RATIONAL rat3;
    rat3.numerator = r1->numerator*r2->denominator - r2->numerator*r1->denominator;
    rat3.denominator = r1->denominator*r2->denominator;

    reduce(&rat3, r3);
}

/* multiply: multiplies two RATIONALs and stores result in &r3 */
void multiply(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3)
{
    RATIONAL rat3;
    rat3.numerator = r1->numerator * r2->numerator;
    rat3.denominator = r1->denominator * r2->denominator;
    reduce(&rat3, r3);
}

/* divide: divides two RATIONALs and stores result in &r3 */
void divide(RATIONAL *r1, RATIONAL *r2, RATIONAL *r3)
{
    RATIONAL rat3;
    rat3.numerator = r1->numerator * r2->denominator;
    rat3.denominator = r1->denominator * r2->numerator;
    reduce(&rat3, r3);
}

/* main: driver function */
int main()
{
    RATIONAL r1 = {3, 2}, r2 = {7, 4}, r3, r4 = {2, 1}, r5 = {4, 2};
    add(&r1, &r2, &r3);
    printf("%d/%d\n", r3.numerator, r3.denominator);
    subtract(&r1, &r2, &r3);
    printf("%d/%d\n", r3.numerator, r3.denominator);
    multiply(&r1, &r2, &r3);
    printf("%d/%d\n", r3.numerator, r3.denominator);
    divide(&r1, &r2, &r3);
    printf("%d/%d\n", r3.numerator, r3.denominator);

    printf("%d %d\n", equal(&r4, &r5), equal2(&r4, &r5));

    return 0;
}
