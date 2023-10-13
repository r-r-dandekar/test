/**********************************************\
|* For Exercise 1.2.2 of Data Structures in C *|
|*   (Book by Tenenbaum-Langsam-Augenstein)   *|
\**********************************************/
/* Reads a group of temperature readings with */
/* latitude,  prints a table of the average   */
/* temperature at each latitude, finds the    */
/* average temperature of the two hemispheres */
/* and finds which of hemisphere is warmer    */

#include <stdio.h>
#include <stdlib.h>

#define NODATA -274     /* signal that reading has no data */

#define MAXREADINGS 10  /* maximum readings per latitude */

#define BUFSIZE 50      /* size of buffer for reading data */


double temp[181][MAXREADINGS];  /*   array of temperatures  */
                                /*   1st index is latitude  */
                                /* 2nd index is reading no. */


double avg[181];    /* average temperature - index indicates latitude */

void init();
int read_data();
void find_avg();
void print_table();
void hemisphere_avg();
void warmer_hemisphere();

void init()
{
    int i, j;
    for (i=0; i < 181; i++)
        for (j=0; j < MAXREADINGS; j++)
            temp[i][j] = NODATA;
}

int main()
{
    init();

    read_data();

    find_avg();

    print_table();

    hemisphere_avg();

    warmer_hemisphere();

    return 0;
}

int read_data()
{
    char c, buf[BUFSIZE];
    int i, j, t, l;

    int inreading = 0;      /* flag for whether or not current character is in parentheses */

    printf("Enter temperature readings (in Celsius) in the format (<latidude> <temperature>), separated by commas\n"
           "For example: \"(60 27), (-30 33.3\" for 27 C at 60 N and 33.3 C at 30 S\n"
           "Multiple readings per latitude are permitted - end input with 'E' or EOF signal\n");

    while ( (c=getchar()) != EOF && c != 'E')       /* until end of input */
    {
        if (inreading)
        {
            if (i < BUFSIZE)
                buf[i++] = c;
            else
            {
                printf("Error: Reading too large! Ran out of buffer space!\n");
                return -1;
            }
        }
        if (c == '(')
        {
            inreading = 1;
            i = 0;
        }
        if (c == ')')
        {
            l = i;          /* assign length of reading to l */
            inreading = 1;
            t = atoi(buf);

            if (t > 90 || t < -90)
            {
                printf("Error: Invalid latitude %d!", t);
                return -1;
            }

            for (i = 0; i < l; i++)
                if (buf[i] == ' ')
                    break;

            j = 0;
            while ( j < MAXREADINGS )       /* find next free reading */
            {                               /* at current latitude    */
                if ( temp[t][j] != NODATA )
                    break;
                j++;
            }
            temp[t+91][j] = atof(&buf[i]);
        }
    }
    return 0;
}

void find_avg()
{
    int i, j, n;
    double sum;

    for (i=0; i < 181; avg[i++] = NODATA)   /* initialize avg */
        ;

    for (i=0; i < 181; i++)     /* calculate average temperatures */
    {
        n = 0;
        sum = 0.0;
        for (j=0; j < MAXREADINGS; j++)
        {
            if (temp[i][j] == NODATA)
                break;

            sum += temp[i][j];
            n++;
        }
        if (n != 0)
            avg[i] = sum/n;
    }
}

void print_table()
{
    int i;
    printf("Latitude\tAvg. Temperature (in C)\n");     /* print table head */
    for (i=180; i >= 0; i--)                    /* print rest of table */
    {
        if (avg[i] == NODATA)
            printf("    %d\t\t  NO DATA\n", i-90);
        else
            printf("    %d\t\t  %.2lf\n", i-90, avg[i]);
    }
    printf("\n");       /* extra line after table */
}

void hemisphere_avg()
{
    int i, n;
    double h_avg;

    /* North Hemisphere */
    h_avg = 0.0;
    n = 0;
    for (i=91; i < 181; i++)
    {
        if (avg[i] != NODATA)
        {
            h_avg += avg[i];
            n++;
        }
    }
    if (n != 0)
    {
        h_avg /= n;
        printf("Average temperature of Northern hemisphere: %.2lf C\n", h_avg);
    }

    /* South Hemisphere */
    h_avg = 0.0;
    n = 0;
    for (i=0; i < 90; i++)
    {
        if (avg[i] != NODATA)
        {
            h_avg += avg[i];
            n++;
        }
    }
    if (n != 0)
    {
        h_avg /= n;
        printf("Average temperature of Southern hemisphere: %.2lf C\n", h_avg);
    }
}

void warmer_hemisphere()
{
    int i, n = 0;
    double n_avg = 0.0, s_avg = 0.0;

    /* find average temperature of north and south hemispheres */
    /* only of latitudes with readings in both the hemispheres */

    for (i = 0; i < 90; i++)        /* for each latitude from 1 to 90 */
    {
        /* if both north and south hemispheres have data  for the latitude */
        if (avg[i+91] != NODATA && avg[89-i] != NODATA)
        {
            n++;
            n_avg += avg[i+91];     /* add average temperature for */
            s_avg += avg[89-1];     /* north and south separately  */
        }
    }

    if (n != 0)     /* if there was at least 1 suitable pair of readings */
    {
        n_avg /= n;
        s_avg /= n;

        /* compare average of both hemispheres and print result accordingly */
        if (n_avg > s_avg)
            printf("North hemisphere is warmer\n");
        else if (s_avg > n_avg)
            printf("South hemisphere is warmer\n");
        else
            printf("Neither hemisphere is warmer\n");
    }
    else            /* if there were no suitable pairs */
        printf("Not enough data to determine which hemisphere is warmer");
}
