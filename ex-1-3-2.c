/******************************************************************************/
/**                For Exercise 1.3.2 of Data Structures in C                **/
/**                  (Book by Tenenbaum-Langsam-Augenstein)                  **/
/******************************************************************************/
/*                                                                            */
/* Title       :  Real Numbers                                                */
/*                                                                            */
/* Date        :  01-07-2023                                                  */
/*                                                                            */
/* Description :                                                              */
/* Uses structures to implement real numbers, with two parts: digits to the   */
/* left of the decimal point, and digits to the right of the decimal point    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>

/* realtype :  structure representing a real number   */
/*             left - digits to left of decimal point */
/*             right - digits to right of decimal point */
struct realtype {
    int left;
    int right;
};

struct realtype getrt(void);

struct realtype ftor(double d);
double rtof(struct realtype r);

struct realtype add(struct realtype a, struct realtype b);
struct realtype subtract(struct realtype a, struct realtype b);
struct realtype multiply(struct realtype a, struct realtype b);

int main()
{
    double d;
    struct realtype a, b, c;
    printf("Enter two real numbers: ");
    a = getrt();
    b = getrt();
    c = multiply(a ,b);
    printf("Product: %d.%d\n", c.left, c.right);

    return 0;
}

/* getrt:  reads a real number and returns its realtype representation */
struct realtype getrt()
{
    char c;
    struct realtype r = {0, 0};
    while ( (c=getchar()) != '\n' && c != ' ' && c != '\t' && c != EOF && c != '.')
        if (isdigit(c))           /* get part left of decimal point  */
        {
            r.left *= 10;
            r.left += c-'0';
        }

    if (c != '.')
        return r;

    while ( (c=getchar()) != '\n' && c != ' ' && c != '\t' && c != EOF && c != '.')
        if (isdigit(c))           /* get part right of decimal point */
        {
            r.right *= 10;
            r.right += c-'0';
        }

    return r;
}

/* ftor:  converts a double to its realtype representation */
struct realtype ftor(double d)
{
    struct realtype r;
    int i = 0;
    r.left  = (int) d;
    d -= r.left;
    r.right = 0;
    if (d < 0.0)
        d *= -1;
    while ( d != 0.0 && i < 5)
    {
        r.right *= 10;
        d *= 10;
        r.right += (int) d;
        d -= (int) d;
        i++;
    }
    return r;
}

/* rtof:  converts a realtype to its double representation */
double rtof(struct realtype r)
{
    double d;
    int n;

    d = r.right;

    while (r.right)
    {
        r.right /= 10;
        d /= 10.0;
    }
    d += r.left;

    return d;
}

/* add:  returns the sum of two realtype numbers */
struct realtype add(struct realtype a, struct realtype b)
{
    struct realtype c = {0, 0};
    int t;
    int dra = 0, drb = 0;       /* digits in right component of a and b */
    int ar, br, cr;

    c.left = a.left + b.left;

    t = a.right;
    while (t)                   /* count digits right of decimal point of a */
    {
        dra++;
        t /= 10;
    }
    t = b.right;
    while (t)                   /* count digits right of decimal point of b */
    {
        drb++;
        t /= 10;
    }

    ar = a.right;
    br = b.right;

    while (dra > drb)       /* pad br with 0s if needed */
    {
        br *= 10;
        drb++;
    }
    while (drb > dra)       /* pad ar with 0s if needed */
    {
        ar *= 10;
        dra++;
    }

    cr = ar + br;

    t = cr;
    while (dra--)
        t /= 10;

    if (t)
    {
        c.left += t;
        while (drb--)
            t *= 10;
        cr -= t;
    }

    c.right = cr;

    return c;
}

/* subtract:  returns the difference of two realtype numbers */
struct realtype subtract(struct realtype a, struct realtype b)
{
    struct realtype c = {0, 0};

    int al = a.left, ar = a.right, bl = b.left, br = b.right;
    int t, negate = 0;
    int dra = 0, drb = 0;       /* digits in right component of a and b */

    t = a.right;
    while (t)                   /* count digits right of decimal point of a */
    {
        dra++;
        t /= 10;
    }
    t = b.right;
    while (t)                   /* count digits right of decimal point of b */
    {
        drb++;
        t /= 10;
    }

    while (dra > drb)       /* pad br with 0s if needed */
    {
        br *= 10;
        drb++;
    }
    while (drb > dra)       /* pad ar with 0s if needed */
    {
        ar *= 10;
        dra++;
    }

    c.left = al - bl;
    c.right = ar - br;

    if (c.left < 0)
    {
        c.left++;
        t = 1;
        while (dra--)
            t *= 10;
        c.right = t - c.right;
        if (c.left == 0)
            negate = 1;
    }

    if (c.right < 0)
    {
        c.left--;
        t = 1;
        while (dra--)
            t *= 10;
        c.right = t + c.right;
        if (c.left == 0)
            negate = 1;
    }

    if (negate)
        c.right = -c.right;

    return c;
}

/* multiply:  returns the product of two realtype numbers */
struct realtype multiply(struct realtype a, struct realtype b)
{
    return ftor(rtof(a)*rtof(b));
}
