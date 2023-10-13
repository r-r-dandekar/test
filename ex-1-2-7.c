/******************************************************************************/
/**                For Exercise 1.2.7 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  List Offset                                                 */
/*                                                                            */
/* Date        :  27-06-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* Accepts two one-dimensional parameters of the same size: range and sub -   */
/* range represents the range of an integer array, i.e. the dimension sizes   */
/* of a multi-dimensional integer array                                       */
/* The elements of sub reperesent subscripts of the foregoing array.          */
/* If sub[i] does not lie between 0 and range [i] - 1, all subscripts from i  */
/* onwards are missing                                                        */
/*                                                                            */
/* A function 'listoff' prints the offsets from the base of the array 'a'     */
/* represented by range, of all the elements of 'a' that are included in the  */
/* array (or single element) represented by sub, assuming each element to be  */
/* of size 1                                                                  */
/*                                                                            */
/* Note: Output does not match specimin output...                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSIZE 200     /* maximum size of range and sub */
#define MAXLINE 100     /* maximum size of an input line */

#define ESIZE 1          /* size of each element in the represented array */

void listoff(int range[], int sub[], int n);

int main()
{
    int range[MAXSIZE], sub[MAXSIZE];
    int n = 0, i;

    char line[MAXLINE], *ptr;
    char c;

    printf("Enter elements of 'range': \n");
    fgets(line, MAXLINE, stdin);        /* read input into line[] */
    i = 0;
    ptr = line;
    while ( *ptr != '\0' && *ptr != '\n')   /* interpret line[] */
    {
        if (isdigit(*ptr)) {
            range[i++] = atoi(ptr);     /* read next number into range[] */
            n++;                        /* increment n to count numbers  */

            while (isdigit(*++ptr))     /* go ahead to the next number   */
                   ;
        }
        ptr++;
    }

    for (i=0; i<n; i++)                 /*    initialize sub[]    */
        sub[i] = -1;

    printf("Enter elements of 'sub': \n");
    fgets(line, MAXLINE, stdin);        /* read input into line[] */
    i = 0;
    ptr = line;
    while ( *ptr != '\0' && *ptr != '\n' && i < n ) /* interpret line[] */
    {
        if (isdigit(*ptr)) {
            sub[i++] = atoi(ptr);       /* read next number into sub[]  */

            while (isdigit(*++ptr))     /* go ahead to the next number  */
                   ;
        }
        ptr++;
    }

    printf("Listoff output:\n");
    listoff(range, sub, n);

    return 0;
}

void listoff(int range[], int sub[], int n)
{
    int startoff = 0, endoff, i;
    int size[n];

    /* calculate size of each level of array */
    size[n-1] = ESIZE;
    for (i = n-2; i >= 0; i--)
    {
        size[i] = size[i+1]*range[i+1];
    }

    /* calculate offset for first element of sub[] */
    for (i = 0; i < n; i++)
    {
        if (sub[i] >= 0 && sub[i] < range[i])
            startoff += size[i]*sub[i];
        else
            break;
    }

    if (i < n)      /* if sub represents an array */
    {
        /* calculate offset for first element after sub[] */
        endoff = startoff + size[i-1];

        printf("%d\n", size[0]);

        for (i = startoff; i < endoff; i += ESIZE)
            printf("%d ", i);
    }
    else            /* if sub represents a single element */
            printf("%d ", startoff);

    printf("\n");
}
