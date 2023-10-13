/* For Exercise 1.2.1 of Data Structures in C */
/*   (Book by Tenenbaum-Langsam-Augenstein)   */
/* Finds the median and mode of an int array  */
/* accepted from the user, and prints result  */

#include <stdio.h>

#define SIZE 4       /* number of elements in array */

double median(int arr[], int n);
int mode(int arr[], int n, int *hasmode);

int main()
{
    int arr[SIZE], i, m, hasmode;
    printf("Enter %d numbers: ", SIZE);
    for (i = 0; i < SIZE; i++)
        scanf("%d", arr+i);

    printf("Median of given data: %lf\n", median(arr, SIZE));

    m = mode(arr, SIZE, &hasmode);

    if (hasmode)
        printf("Mode of given data: %d\n", m);
    else
        printf("Given data has no mode\n");

    return 0;
}

double median(int arr_in[], int n)
{
    int i, step, temp, arr[n];
    for(i = 0; i < n; i++)                      /* copy array */
        arr[i] = arr_in[i];

    for (step = 0; step < n - 1; step++)        /* sort array */
    {
        for (i = 0; i < n - step - 1; i++)
        {
            if (arr[i] > arr[i+1])
            {
                temp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = temp;
            }
        }
    }
    if (n%2)                                    /* if odd number of elements */
        return arr[n/2];
    else
        return (arr[n/2] + arr[n/2 - 1]) / 2.0;
}

int mode(int arr[], int n, int *hasmode)
{
    int i, j, temp;
    int dels[n];        /* array of distinct elements */
    int freq[n];        /* frequencies of distinct elements */
    int dist = 0;       /* number of distinct elements found */
    int seen;           /* flag for whether or not current element has been seen before */

    for (i = 0; i < n; i++)
        freq[i] = -1;

    for (i = 0; i < n; i++)
    {
        seen = 0;
        for (j = 0; j < dist; j++)
            if (arr[i] == dels[j])
            {
                freq[j]++;
                seen = 1;
                break;
            }

        if (!seen)
        {
            dels[dist] = arr[i];
            freq[dist] = 1;
            dist++;
        }
    }
    for (j = 0; j < n - 1; j++)         /* sort distinct elements by frequency */
    {
        for (i = 0; i < n - j - 1; i++)
        {
            if (freq[i] < freq[i+1])
            {
                temp = freq[i+1];
                freq[i+1] = freq[i];
                freq[i] = temp;
                temp = dels[i+1];
                dels[i+1] = dels[i];
                dels[i] = temp;
            }
        }
    }
    if (freq[0] == freq[1])
    {
        *hasmode = 0;
        return 0;
    }
    else
    {
        *hasmode = 1;
        return dels[0];
    }
}
