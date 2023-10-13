#include <stdio.h>
#include <string.h>

#define MAXLENGTH 1000

void bin_to_ter(char *bin, char *ter);
void ter_to_bin(char *ter, char *bin);

int add(char s1[], char s2[], char s3[], int base);
int subtract(char s1[], char s2[], char s3[], int base);
int multiply(char s1[], char s2[], char s3[], int base);
void divide(char s1[], char s2[], char s3[], char s4[], int base);
int power(char s1[], char s2[], char s3[], int base);

int iszero(char s[]);

int main()
{
    char bin[MAXLENGTH], ter[MAXLENGTH];
    printf("Enter a ternary number: ");
    scanf("%s", ter);
    ter_to_bin(ter, bin);
    printf("Binary representation: %s\n", bin);
    return 0;
}

/* bin_to_ter:  converts a number from binary to ternary */
void bin_to_ter(char b[], char t[])
{
    int n, m, i, l;
    char s1[MAXLENGTH], s2[MAXLENGTH], s3[MAXLENGTH], one[MAXLENGTH], two[MAXLENGTH];
    char *ptr;
    n = strlen(b);
    m = (2*n)/3 + 2;

    for (i = 0; i < m; i++)
        t[i] = s1[i] = one[i] = two[i] = '0';
    t[i] = s1[i] = one[i] = two[i] = '\0';

    one[m-1] = '1';
    two[m-1] = '2';

    l = strlen(b);

    for (i=0; i < l; i++)
    {
        if(b[l-1-i] != '0')
        {
            power(two, s1, s2, 3);
            strcpy(s3, t);
            add(s2, s3, t, 3);
        }
        strcpy(s2, s1);
        add(one, s2, s1, 3);
    }

    ptr = t;
    while (*(++ptr) == '0')
        ;
    strcpy(t, ptr);
}

/* ter_to_bin:  converts a number from ternary to binary */
void ter_to_bin(char t[], char b[])
{
    int n, m, i, l;
    char s1[MAXLENGTH], s2[MAXLENGTH], s3[MAXLENGTH], one[MAXLENGTH], two[MAXLENGTH];
    char *p1, *p2;
    n = strlen(t);
    m = (3*n)/2 + 2;

    for (i = 0; i < m; i++)
        b[i] = s1[i] = one[i] = two[i] = '0';
    b[i] = s1[i] = one[i] = two[i] = '\0';

    one[m-1] = '1';
    two[m-1] = '2';

    p1 = t;
    p2 = s1+m-1;
    i = 0;
    while (*p1++)
        i++;
    p1-=2;
    while (i-- > 0)
        *p2-- = *p1--;

    p1 = b+m-1;
    l = strlen(s1);
    while ( !iszero(s1) )
    {
        strcpy(s2, s1);
        divide(s2, two, s1, s3, 3);
        *p1-- = s3[l-1];
    }

    p1 = b;
    while (*(++p1) == '0')
        ;
    strcpy(b, p1);
}

/* add:  adds two numbers with the same base */
/* both strings must have same no. of digits */
int add(char *s1, char *s2, char *s3, int base)
{
    int carry = 0;
    int temp;
    char c = '0';

    temp = *(s1++)-'0' + *(s2++)-'0';           /* add leftmost digits */
    *s3 = temp + '0';
    if ( temp >= base )
    {
        carry++;
        *s3 -= base;
    }

    if ( *s1&&*s2 )                             /* if there are digits to the right */
    {
        if ( temp = add(s1, s2, s3+1, base) )     /* add carry from next right digits */
        {
            *s3 += temp;
            if (*s3-'0' >= base)
            {
                carry++;
                *s3 -= base;
            }
        }
    }
    else                                        /* else, end the string */
        *(s3+1) = '\0';

    return carry;
}

/* subtract:  subtracts two numbers with the same base */
/* both input strings must have same number of digits  */
int subtract(char *s1, char *s2, char *s3, int base)
{
    int borrow = 0;
    int temp;
    char c = '0';

    temp = *(s1++)-'0' - *(s2++)+'0';           /* add leftmost digits */
    *s3 = temp + '0';
    if ( temp < 0 )
    {
        borrow++;
        *s3 += base;
    }

    if ( *s1&&*s2 )                             /* if there are digits to the right */
    {
        if ( temp = subtract(s1, s2, s3+1, base) )     /* subtract borrow from next right digits */
        {
            *s3 -= temp;
            if (*s3-'0' < 0)
            {
                borrow++;
                *s3 += base;
            }
        }
    }
    else                                        /* else, end the string */
        *(s3+1) = '\0';

    return borrow;
}

/* multiply:  muptiplies two numbers with the same base */
/*  both input strings must have same number of digits  */
int multiply(char *s1, char *s2, char *s3, int base)
{
    char t1[MAXLENGTH], t2[MAXLENGTH], one[MAXLENGTH];
    int i, l;
    l = strlen(s2);
    for(i=0; i < l; i++){
        *(s3+i) = '0';
        if(i == l-1)
            one[i] = '1';
        else
            one[i] = '0';
    }
    *(s3+i) = '\0';
    one[i] = '\0';

    strcpy(t2, s2);
    while ( !iszero(t2) )
    {
        strcpy(t1, s3);

        if (add(t1, s1, s3, base))      /* add s1 to s3 */
            return 1;

        strcpy(t1, t2);
        subtract(t1, one, t2, base);    /* decrement s2 */
    }

    return 0;
}

/* divide:  divides two numbers with the same base */
/*  both  strings must have same number of digits  */
/* stores the quotient in s3, and remainder in s4  */
void divide(char *s1, char *s2, char *s3, char *s4, int base)
{
    char t1[MAXLENGTH], t2[MAXLENGTH], one[MAXLENGTH];
    int i, l;
    l = strlen(s2);
    for(i=0; i < l; i++){
        *(s3+i) = '0';
        if(i == l-1)
            one[i] = '1';
        else
            one[i] = '0';
    }
    *(s3+i) = '\0';
    one[i] = '\0';

    strcpy(s4, s1);
    while ( !iszero(s4) )
    {
        strcpy(t1, s4);

        if (subtract(t1, s2, t2, base))     /* subtract s1 from s4 */
            return;
        else
            strcpy(s4, t2);

        strcpy(t1, s3);
        add(t1, one, s3, base);        /* increment s3 */
    }
}

/* power:  calculates s1 raised to s2, stores result in s3 */
/* both input strings must have the same number of digits  */
int power(char *s1, char *s2, char *s3, int base)
{
    char t1[MAXLENGTH], t2[MAXLENGTH], one[MAXLENGTH];
    int i, l;
    l = strlen(s2);
    for(i=0; i < l-1; i++){
        *(s3+i) = '0';
        one[i] = '0';
    }
    *(s3+i) = '1';
    one[i++] = '1';
    *(s3+i) = '\0';
    one[i] = '\0';

    strcpy(t2, s2);
    while ( !iszero(t2) )
    {
        strcpy(t1, s3);

        if (multiply(t1, s1, s3, base))     /* multiple s3 by s1 */
            return 1;

        strcpy(t1, t2);
        subtract(t1, one, t2, base);        /* decrement s2 */
    }

    return 0;
}

/* iszero:  checks if a given number is 0 */
/*   returns 1 if zero, and 0 otherwise   */
int iszero(char *s)
{
    while (*s)
        if(*s++ != '0')
            return 0;
    return 1;
}
