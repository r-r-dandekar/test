/******************************************************************************/
/**                For Exercise 1.2.3 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  Department Store Chain Records                              */
/*                                                                            */
/* Date        :  22-06-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* There is a chain of 20 department stores, selling 10 different items.      */
/* Every month, each store manager submits data cards for the items,          */
/* consisiting of a branch number, an item number, and a sales figure. Some   */
/* managers may not submit cards for some items.                              */
/*                                                                            */
/* This program accepts the cards for a month and prints a table of the data  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define BRANCHCOUNT 20  /* number of branches */
#define ITEMCOUNT 10    /* number of items    */

int sales[BRANCHCOUNT][ITEMCOUNT];  /* stores data of sales for each item */
                                    /* the first index is branch number   */
                                    /* the second index is item number    */

void init();
int readcards();
void writetable();

void init()
{
    int i, j;
    for (i = 0; i < BRANCHCOUNT; i++)       /* initialize sales array */
        for (j = 0; j < ITEMCOUNT; j++)
            sales[i][j] = 0;
}

int main()
{
    init();

    if ( readcards() != 0 )     /* read cards, return 1 in case of an error   */
        return 1;

    writetable();

    return 0;
}

/* readcards:  accepts 'data cards' through standard input and stores data */
/*             returns 0 if successful, -1 in the event of an error        */
int readcards()
{
    int i = 0;
    int b_n, i_n;       /* brand number, item number, sales figure */
    char c, line[15];
    printf("Enter data cards:\n"
           "Card format - \"<branch_no.> <item_no.> <sales_fig.>\"\n"
           "Each card should be on a new line\n"
           "End input with 'E' or EOF on a new line\n\n");

    while ( (c=getchar()) != 'E' && c != EOF )
    {
        line[i++] = c;

        if (c == '\n')                          /* at the end of each line */
        {
            line[i] = '\0';

            i = 0;

            b_n = atoi(line) - 1;               /* get branch number  */
            if (b_n < 0 || b_n >= BRANCHCOUNT)
            {
                printf("Error: Invalid branch number '%d' in card \"%s\"", b_n+1, line);
                return -1;
            }

            while ((c=line[i++]) != ' ')        /* move to next field */
                if ( !c )
                {
                    printf("Error: Invalid card \"%s\" - not enough fields", line);
                    return -1;
                }

            i_n = atoi(&line[i]) - 1;           /*  get item number   */
            if (i_n < 0 || i_n >= BRANCHCOUNT)
            {
                printf("Error: Invalid item number '%d' in card \"%s\"", i_n+1, line);
                return -1;
            }

            while ((c=line[i++]) != ' ')        /* move to next field */
                if ( !c )
                {
                    printf("Error: Invalid card \"%s\" - not enough fields", line);
                    return -1;
                }

            sales[b_n][i_n] = atoi(&line[i]);   /* get sales figure  */

            i = 0;
        }
    }
    return 0;
}

/* writetable:  prints sales data to standard output  */
/*              assuming tab-stops every 8 characters */
void writetable()
{
    int i, j;
    int total[BRANCHCOUNT];     /* total for each branch */
    int gtotal = 0;             /* grand total for all branches */

    /* table header */
    printf("Branch no.\t");
    for (i = 1; i <= ITEMCOUNT; i++)
        printf("Item %d\t", i);
    printf("\tTotal\n");

    /* 2nd row to 2nd last row */
    for (i = 0; i < BRANCHCOUNT; i++)
    {
        total[i] = 0;
        printf("    %d\t\t", i+1);
        for (j = 0; j < ITEMCOUNT; j++)
        {
            printf("%d\t", sales[i][j]);
            total[i] += sales[i][j];
        }
        gtotal += total[i];
        printf("\t%d\n", total[i]);
    }

    /* last row */
    printf("TOTAL :\t\t");
    for (i = 0; i < ITEMCOUNT; i++)
        printf("\t");
    printf("\t%d\n", gtotal);
}
