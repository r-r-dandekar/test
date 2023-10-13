/******************************************************************************/
/**                For Exercise 1.3.4 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  Employee Raise                                              */
/*                                                                            */
/* Date        :  02-07-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* There are two arrays - one of student records and one of employee records  */
/* Each student record stores a last name, first name, and grade point index  */
/* Each employee record stores a last name, first name, and salary            */
/* Both arrays are sorted in alphabetic order by last name and first name     */
/* Assume no conflicting pair of last and first names                         */
/*                                                                            */
/* The function emp_raise() gives a raise to all employees who have a student */
/* record with grade-point index greater than or equal to a given amount      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define MAXRECORDS 100

struct student_rec {
    char last[20];
    char first[20];
    double gpi;
} students[MAXRECORDS], *s_ptr[MAXRECORDS];

struct employee_rec {
    char last[20];
    char first[20];
    int salary;
} employees[MAXRECORDS], *e_ptr[MAXRECORDS];

void init(void);

void sort_students(struct student_rec *a[], int n);
int partition_s(struct student_rec *a[], int n);

void sort_employees(struct employee_rec *a[], int n);
int partition_e(struct employee_rec *a[], int n);

int cmpnames(char *last1, char *first1, char *last2, char *first2);

int emp_raise(int percent, double min_gpi);

int search_student(char *last, char *first);

void init()
{
    char line[MAXLINE];
    char *p1, *p2;
    int i;

    struct student_rec s_temp[MAXRECORDS];
    struct employee_rec e_temp[MAXRECORDS];

    /* initialize student and employee records */
    for (i = 0; i < MAXRECORDS; i++)
    {
        strcpy(students[i].last, "");
        strcpy(students[i].first, "");
        students[i].gpi = 0.0;
        s_ptr[i] = &students[i];

        strcpy(employees[i].last, "");
        strcpy(employees[i].first, "");
        employees[i].salary = 0;
        e_ptr[i] = &employees[i];
    }

    /* read student records */
    printf("\t\t---===|| Enter student records ||===---\n\n"
           "Each record should be of the form "
           "\"<last name> <first name> <grade-point-index>\"\n"
           "For example: \"Sharma Rohan 2.0\"\n"
           "Each student record should be on a new line\n"
           "End input with EOF signal\n\n");

    i = 0;
    do      /* read lines and store data */
    {
        if (fgets(line, MAXLINE, stdin) == NULL)
            break;
        p1 = line;

        p2 = students[i].last;      /* read last name */
        while ( *p1 != '\0' && *p1 != ' ' && *p1 != '\t' && *p1 != '\n' )
        {
            *p2++ = *p1++;
        }
        *p2 = '\0';

        p1++;

        p2 = students[i].first;      /* read first name */
        while ( *p1 != '\0' && *p1 != ' ' && *p1 != '\t' && *p1 != '\n' )
        {
            *p2++ = *p1++;
        }
        *p2 = '\0';
        p1++;

        students[i].gpi = atof(p1);

        p1++;

        i++;
    } while (line[0] != EOF && i < 100);

    /* sort student records */
    sort_students(s_ptr, i);
    for (i = 0; i < MAXRECORDS; i++)
        s_temp[i] = *s_ptr[i];
    for (i = 0; i < MAXRECORDS; i++)
        students[i] = s_temp[i];



    /* read employee records */
    printf("\t\t---===|| Enter employee records ||===---\n\n"
           "Each record should be of the form "
           "\"<last name> <first name> <salary>\"\n"
           "For example: \"Sharma Rohan 20000\"\n"
           "Each student record should be on a new line\n"
           "End input with EOF signal\n\n");

    i = 0;
    do      /* read lines and store data */
    {
        if (fgets(line, MAXLINE, stdin) == NULL)
            break;
        p1 = line;

        p2 = employees[i].last;      /* read last name */
        while ( *p1 != '\0' && *p1 != ' ' && *p1 != '\t' && *p1 != '\n' )
        {
            *p2++ = *p1++;
        }
        *p2 = '\0';

        p1++;

        p2 = employees[i].first;      /* read first name */
        while ( *p1 != '\0' && *p1 != ' ' && *p1 != '\t' && *p1 != '\n' )
        {
            *p2++ = *p1++;
        }
        *p2 = '\0';
        p1++;

        employees[i].salary = atoi(p1);

        p1++;

        i++;
    } while (line[0] != EOF && i < 100);

    /* sort employee records */
    sort_employees(e_ptr, i);
    for (i = 0; i < MAXRECORDS; i++)
        e_temp[i] = *e_ptr[i];
    for (i = 0; i < MAXRECORDS; i++)
        employees[i] = e_temp[i];
}

void sort_students(struct student_rec *a[], int n)
{
    if (n <= 1)     /* do nothing if one or less elements */
        return;

    /* find pivot */
    int pi = partition_s(a, n);

    /* recursive calls on left and right sides of pivot */
    sort_students(a, pi);
    sort_students(a+pi, n-pi);
}
int partition_s(struct student_rec *a[], int n)
{
    int i, j;
    struct student_rec *sp, *temp;

    /* select rightmost element as pivot */
    sp = a[n-1];

    /* index for greater element */
    i = 0;

    /* traverse array, compare each element with pivot */
    for (j = 0; j < n-1; j++)
    {
        /* if current element is smaller than pivot, */
        /* swap with greater element at index i      */
        if ( cmpnames((*a[j]).last, (*a[j]).first, (*sp).last, (*sp).first) < 0 )
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
        }
    }

    /* swap pivot with greater element at index i */
    temp = a[i];
    a[i] = a[n-1];
    a[n-1] = temp;

    /* return partition point */
    return i;
}

void sort_employees(struct employee_rec *a[], int n)
{
    if (n <= 1)     /* do nothing if one or less elements */
        return;

    /* find pivot */
    int pi = partition_e(a, n);

    /* recursive calls on left and right sides of pivot */
    sort_employees(a, pi);
    sort_employees(a+pi, n-pi);
}
int partition_e(struct employee_rec *a[], int n)
{
    int i, j;
    struct employee_rec *sp, *temp;

    /* select rightmost element as pivot */
    sp = a[n-1];

    /* index for greater element */
    i = 0;

    /* traverse array, compare each element with pivot */
    for (j = 0; j < n-1; j++)
    {
        /* if current element is smaller than pivot, */
        /* swap with greater element at index i      */
        if ( cmpnames((*a[j]).last, (*a[j]).first, (*sp).last, (*sp).first) < 0 )
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
        }
    }

    /* swap pivot with greater element at index i */
    temp = a[i];
    a[i] = a[n-1];
    a[n-1] = temp;

    /* return partition point */
    return i;
}

int cmpnames(char *l1, char *f1, char *l2, char *f2)
{
    if (strcmp(l1, l2) > 0)
        return 1;
    else if (strcmp(l1, l2) < 0)
        return -1;
    else if (strcmp(f1, f2) > 0)
        return 1;
    else if (strcmp(f1, f2) < 0)
        return -1;
    else
        return 0;
}

int main()
{
    int i;
    init();
    printf("\n\n");
    emp_raise(10, 3.0);
    for (i = 0; i < MAXRECORDS; i++)
    {
        if ( strcmp(employees[i].last, "") != 0 )
            printf("%s %s : %d\n", employees[i].last, employees[i].first, employees[i].salary);
    }
    return 0;
}

/* emp_raise:  gives a raise to all employees with a student record with */
/*             grade-point index greater/equal to the specified amount   */
/*             returns the number of employees that got a raise          */
int emp_raise(int percent, double min_gpi)
{
    int i, index;
    for (i = 0; i < MAXRECORDS; i++)
    {
        if ( strcmp(employees[i].last, "") != 0 )
        {
            index = search_student(employees[i].last, employees[i].first);
            if (index == -1)
                continue;

            if (students[index].gpi >= min_gpi)
                employees[i].salary *= 1.0 + percent/100.0;
        }
    }
    return 0;
}

/* search_student: searches for a student with the given name */
/*                 returns array index of student if found    */
/*                 returns -1 if not found                    */
int search_student(char *last, char *first)
{
    int l = 0, r = MAXRECORDS-1, m, cmp;

    /* binary search for student by name */
    while (l <= r)
    {
        m = l + (r-l)/2;

        if ( strcmp(students[m].last, "") == 0 )
            cmp = 1;
        else
            cmp = cmpnames(students[m].last, students[m].first, last, first);

        if ( cmp == 0 )
            return m;

        if ( cmp < 0 )
            l = m+1;

        else
            r = m-1;
    }

    return -1;
}
