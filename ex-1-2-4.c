/******************************************************************************/
/**                For Exercise 1.2.4 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  Checkerboard                                                */
/*                                                                            */
/* Date        :  22-06-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* Inputs a state of a game of checkers at a particular instant, and prints   */
/* all possible moves that black can make from that position                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INBOARD(x,y) (x >= 0 && x < 7 && y >= 0 && y < 7)

int board[8][8];        /* 8x8 checkerboard */
                        /* 0 - empty square */
                        /* 1 - white man    */
                        /* 2 - white king   */
                        /* 3 - black man    */
                        /* 4 - black king   */

int readstate();
void printallblackmoves();
void printboard();

void printblackmoves(int row, int col);
int iswhite(int row, int col);
int isblack(int row, int col);
int inboard(int row, int col);

int main()
{
    if ( readstate() != 0 )
        return -1;
    printboard();
    printallblackmoves();
    return 0;
}

/* printboard:  displays the board */
void printboard()
{
    int i, j;

    /* file names */
    printf("  ");
    for (i = 0; i < 8; i++)
        printf("%c ", i+'A');
    printf("\n");

    for (i = 7; i >= 0; i--)
    {
        /* rank numbers */
        printf("%d ", i+1);


        /* 8x8 checkerboard */
        for (j = 0; j < 8; j++)
        {
            if ( (i+j)%2 == 0 )             /* 'block' used for white squares */
                printf("%c%c", 219, 219);   /* looks white on black terminals */
            else
            {
                switch (board[i][j])
                {
                    case 0:
                        printf("  ");
                        break;
                    case 1:
                        printf("WM");
                        break;
                    case 2:
                        printf("WK");
                        break;
                    case 3:
                        printf("BM");
                        break;
                    case 4:
                        printf("BK");
                        break;
                }
            }
        }
        /* rank numbers */
        printf(" %d\n", i+1);
    }

    /* file names */
    printf("  ");
    for (i = 0; i < 8; i++)
        printf("%c ", i+'A');
    printf("\n");
}

int readstate()
{
    int i = 0, j;
    int row;
    int col;
    int clr;            /* colour - 0 is white, 2 is black  */
    int type;           /* type - 1 is man, 2 is king       */
    int white = 0;      /* number of white pieces           */
    int black = 0;      /* number of black pieces           */

    char c, line[10];

    printf("Enter the pieces in the format \"<Colour><Type> <File><Rank>\"\n"
           "Key:\tW - White\n"
           "    \tB - Black\n"
           "    \tM - Man\n"
           "    \tK - King\n"
           "For example, enter \"WK A2\" for white king on A2 \n"
           "(Rows and columns start from 1)\n"
           "Entry for each piece should be on a new line\n"
           "End input with 'E' or EOF signal\n\n");

    while ( (c=getchar()) != EOF && c != 'E')
    {
        line[i++] = c;

        if (c == '\n')                  /* at the end of each line */
        {
            line[i-1] = '\0';
            if (i < 6)
            {
                printf("Error :  Entry '%s' is too short!\n", line);
                return -1;
            }
            i = 0;

            if (line[0] == 'W')         /* read colour */
                clr = 0;
            else if (line[0] == 'B')
                clr = 2;
            else
            {
                printf("Error :  Invalid colour '%c' in entry '%s'\n",
                       line[0], line);
                return -1;
            }

            if (line[1] == 'M')         /* read type */
                type = 1;
            else if (line[1] == 'K')
                type = 2;
            else
            {
                printf("Error :  Invalid type '%c' in entry '%s'\n",
                       line[1], line);
                return -1;
            }

            /* read row */
            if (toupper(line[3]) >= 'A' && toupper(line[3]) <= 'H')
                col = toupper(line[3]) - 'A';

            else
            {
                printf("Error :  Invalid row '%c' in entry '%s'\n",
                       line[3], line);
                return -1;
            }

            /* read column */
            if (line[4] >= '1' && line[4] <= '8')
                row = line[4] - '1';
            else
            {
                printf("Error :  Invalid row '%c' in entry '%s'\n",
                       line[4], line);
                return -1;
            }


            if (clr == 0)
                white++;
            else
                black++;

            if (white > 8)
            {
                printf("Error :  Too many white pieces!\n");
                return -1;
            }
            if (black > 8)
            {
                printf("Error :  Too many black pieces!\n");
                return -1;
            }

            if ( (row+col)%2 == 0 )
            {
                printf("Error :  Can't have a piece on white square %c%d!\n",
                       col+'A', row+1);
                return -1;
            }

            board[row][col] = type + clr;       /* store values in board */
        }
    }
    return 0;
}

/* printallblackmoves:  prints all possible moves for black in the current board sate */
void printallblackmoves()
{
    int i, j;
    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
            printblackmoves(i, j);
}

/* printblackmoves:  prints all possible moves for black from a given */
/*                   square, or nothing if no moves are possible      */
/*                   direction of black is from row 8 towards row 1   */
void printblackmoves(int row, int col)
{
    int isking;
    int tr, tc;     /* target row and column */

    if (board[row][col] == 3)
        isking = 0;
    else if (board[row][col] == 4)
        isking = 1;
    else
        return;

    /* -- moves common to men and kings -- */

    /* normal moves */
    tr = row-1;

    tc = col-1;
    if (INBOARD(tr, tc) && board[tr][tc] == 0)
        printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);

    tc = col+1;
    if (INBOARD(tr, tc) && board[tr][tc] == 0)
        printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);

    /* capture moves */
    tr = row-2;

    tc = col-2;
    if (INBOARD(tr, tc) && board[tr][tc] == 0 && iswhite(row-1, col-1))
        printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);

    tc = col+2;
    if (INBOARD(tr, tc) && board[tr][tc] == 0 && iswhite(row-1, col+1))
        printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);


    /* -- moves exclusive to kings -- */
    if (isking)
    {
        /* normal moves */
        tr = row+1;

        tc = col-1;
        if (INBOARD(tr, tc) && board[tr][tc] == 0)
            printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);

        tc = col+1;
        if (INBOARD(tr, tc) && board[tr][tc] == 0)
            printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);

        /* capture moves */
        tr = row+2;

        tc = col-2;
        if (INBOARD(tr, tc) && board[tr][tc] == 0 && iswhite(row+1, col-1))
            printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);

        tc = col+2;
        if (INBOARD(tr, tc) && board[tr][tc] == 0 && iswhite(row+1, col+1))
            printf("%c%d to %c%d\n", col+'A', row+1, tc+'A', tr+1);
    }
}

/* iswhite:  checks if a square contains a white piece */
int iswhite(int row, int col)
{
    if (board[row][col] == 1 || board[row][col] == 2)
        return 1;
    else
        return 0;
}

/* isblack:  checks if a square contains a black piece */
int isblack(int row, int col)
{
    if (board[row][col] == 3 || board[row][col] == 4)
        return 1;
    else
        return 0;
}

/* inboard:  checks if a square is within the bounds of the board */
int inboard(int row, int col)
{
    if (row >= 0 && row < 7 && col >= 0 && col < 7)
        return 1;
    else
        return 0;
}
