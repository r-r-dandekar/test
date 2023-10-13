/* reads two strings of 0s and 1s, representing  */
/* binary numbers, and uses functions to perform */
/*  addition, subtraction and multiplication on  */
/* them without converting them to integer types */

#include <stdio.h>

#define MAXLENGTH 100

int add(char s1[], char s2[], char s3[]);
int subtract(char s1[], char s2[], char s3[]);
int multiply(char s1[], char s2[], char s3[]);

int iszero(char s[]);

int main()
{
    char s1[MAXLENGTH], s2[MAXLENGTH], s3[MAXLENGTH];

    printf("Enter two binary numbers: ");
    scanf("%s%s", s1, s2);

    add(s1, s2, s3);
    printf("Sum:        %s\n", s3);

    subtract(s1, s2, s3);
    printf("Difference: %s\n", s3);

    multiply(s1, s2, s3);
    printf("Product:    %s\n", s3);

    return 0;
}

/*     add:  adds two binary numbers      */
/* s1, s2 and s3 are strings of 0s and 1s */
/*     representing the binary numbers    */
/*  no. of bits in s1 and s2 must be same */
/*   returns 1 if overflow, 0 otherwise   */
int add(char *s1, char *s2, char *s3)
{
    int carry = 0;
    char c = '0';

    if (*s1 == '1' || *s2 == '1')
    {
        if(*s1 == *s2)
            carry = 1;
        else
            c = '1';
    }

    s1++;
    s2++;

    if ( (*s1 && *s2) && add(s1, s2, s3+1) )
    {
        if(c == '1')
        {
            c = '0';
            carry = 1;
        }
        else
            c = '1';
    }

    *s3 = c;
    return carry;
}

/* subtract:  subtracts two binary numbers */
/* s1, s2 and s3 are strings of 0s and 1s  */
/*     representing the binary numbers     */
/*  no. of bits in s1 and s2 must be same  */
/*   returns 1 if underflow, 0 otherwise   */
int subtract(char *s1, char *s2, char *s3)
{
    int borrow = 0;

    if (*s2 == '0')
        *s3 = *s1;
    else
    {
        if (*s1 == '0')
        {
            borrow = 1;
            *s3 = '1';
        }
        else
            *s3 = '0';
    }

    s1++;
    s2++;

    if ( (*s1 && *s2) && subtract(s1, s2, s3+1) )
    {
        if (*s3 == '1')
            *s3 = '0';
        else
            borrow = 1;
    }

    return borrow;
}



/* multiply:  multiplies 2 binary numbers  */
/* s1, s2 and s3 are strings of 0s and 1s  */
/*     representing the binary numbers     */
/*  no. of bits in s1 and s2 must be same  */
/*   returns 1 if overflow, 0 otherwise    */
int multiply(char *s1, char *s2, char *s3)
{
    int i, l=0;
    char one[MAXLENGTH], t1[MAXLENGTH], t2[MAXLENGTH], t3[MAXLENGTH];
    char *ps1 = s1, *ps2 = s2, *ps3 = s3, *pt1 = t1, *pt2 = t2, *pt3 = t3;

    while ( *ps1++ )
        *pt3++ = *ps3++ = '0';
    *pt3 = *ps3 = '\0';
    while (*pt1++ = *pt2++ = *ps2++)
        ;

    ps2 = s2;
    while (*ps2++)
        l++;

    for (i = 0; i < l-1; i++)
        one[i] = '0';
    one[i++] = '1';
    one[i] = '\0';

    while ( !iszero(t1) )
    {
        if( add(t3, s1, s3) )
            return 1;
        ps3 = s3;
        pt3 = t3;
        while (*pt3++ = *ps3++)
            ;
        subtract(t1, one, t2);
        pt1 = t1;
        pt2 = t2;
        while (*pt1++ = *pt2++)
            ;
    }

    return 0;
}

/* iszero:  checks if a binary number is 0 */
/* s is a string of 0s and 1s representing */
/* the binary number that is to be checked */
/*    returns 1 if zero, and 0 otherwise   */
int iszero(char *s)
{
    while (*s)
        if(*s++ != '0')
            return 0;
    return 1;
}
