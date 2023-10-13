/******************************************************************************/
/**                For Exercise 1.2.5 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  PrintAr                                                     */
/*                                                                            */
/* Date        :  25-06-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* Inputs an array of integers and prints the ekements on a series of pages   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define ROWS 50     /* rows in a page    */
#define COLS 20     /* columns in a page */

int *readarr(int m, int n);
void printarr(int *pa, int m, int n);

int main()
{
    int m, n, *pa;
    printf("Enter number of rows: ");
    scanf("%d", &m);
    printf("Enter number of columns: ");
    scanf("%d", &n);
    pa = readarr(m, n);
    printarr(pa, m, n);
    return 0;
}

int *readarr(int m, int n)
{
    int *pa = (int*)malloc(m*n*sizeof(int));    /* allocate space */
    int i, j;

    printf("Enter array elements:\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", pa+i*n+j );                  /* read array elements */
    return pa;
}

void printarr(int *pa, int m, int n)
{
    int i, j;
    int prow = 0, pcol = 0;     /* starting row and column of the page */

    while (prow < m)            /* while there is more to display...   */
    {
        printf("\t");
        for (j = pcol; j < pcol+COLS && j < n; j++) /* column headings */
            printf("COL %d\t", j-pcol);
        printf("\n");
        for (i = prow; i < prow+ROWS && i < m; i++)
        {
            printf("ROW %d\t", i-prow);                  /* row labels */
            for (j = pcol; j < pcol+COLS && j < n; j++)
            {
                printf("  %d\t", *(pa + i*n + j) ); /* print array element */
            }
            printf("\n");
        }

        if (j < n)                               /* set starting bounds */
            pcol += COLS;                           /* for next page       */
        else
            prow += ROWS;
    }
}
