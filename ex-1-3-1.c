/******************************************************************************/
/**                For Exercise 1.3.1 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  Complex Numbers                                             */
/*                                                                            */
/* Date        :  01-07-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* Uses structures to implement complex numbers, with functions for adding,   */
/* multiplying and negating complex numbers                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>

/* complex_num :  structure representing complex numbers */
/*                a - real part of the number            */
/*                b - imaginary part of the number       */
/*                complex number = (a + bi)              */
typedef struct complex_num {
    double a;
    double b;
} complex;

complex add(complex x, complex y);
complex mult(complex x, complex y);
complex negate(complex x);

int main()
{
    complex x, y, z;
    double p;
    printf("Enter real and imaginary parts of two complex numbers: \n\n");
    scanf("%lf%lf%lf%lf", &x.a, &x.b, &y.a, &y.b);
    z = add(x, y);
    printf("Sum of (%.2lf + %.2lfi) and (%.2lf + %.2lfi) "
           "is (%.2lf + %.2lfi)\n\n", x.a, x.b, y.a, y.b, z.a, z.b);
    z = mult(x, y);
    printf("Product of (%.2lf + %.2lfi) and (%.2lf + %.2lfi) "
           "is (%.2lf + %.2lfi)\n\n", x.a, x.b, y.a, y.b, z.a, z.b);
    z = negate(x);
    printf("-(%.2lf + %.2lfi) = (%.2lf + %.2lfi)\n\n", x.a, x.b, z.a, z.b);
    return 0;
}

complex add(complex x, complex y)
{
    complex sum;
    sum.a = x.a + y.a;
    sum.b = x.b + y.b;
    return sum;
}

complex mult(complex x, complex y)
{
    complex prod;
    prod.a = (x.a*y.a) - (x.b*y.b);
    prod.b = (x.a*y.b) + (x.b*y.a);
    return prod;
}

complex negate(complex x)
{
    complex neg = {-x.a, -x.b};
    return neg;
}
