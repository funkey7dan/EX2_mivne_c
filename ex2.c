// ***REMOVED*** Daniel Bronfman

#include <stdio.h>
#include <limits.h>
#include "ex2.h"
#define MAG_MASK 0x7FFFFFFF

int check_sign(magnitude a)
{

    unsigned int mask = 0x80000000;
    if(mask & a)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// return the magnitude of the number
magnitude get_mag(magnitude a)
{
//    if(a>0){
//
//    }
//    else{
//        int const mask = (a>>31)<<31;
//        unsigned int a_mag = ~(a&mask);
//        return (a_mag);
//    }
    int a_mag = a & MAG_MASK;
    return (a_mag);
}

int to_twos(magnitude a)
{

    return ~a + 1;
}

// a + b
magnitude add(magnitude a, magnitude b)
{

    magnitude result;
    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    int orig_a = a;
    int orig_b = b;
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a)
    {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = (get_mag(a + b));
                    if(check_sign(a + b) == (1))
                    {
                        return to_twos(result);
                    }
                    else
                    {
                        return result;
                    }
                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = (get_mag(a - b));
                    if(check_sign(a - b) == (0))
                    {
                        if(orig_a < -orig_b)
                        {
                            return -to_twos(result);
                        }
                        else
                        {
                            return to_twos(result);
                        }
                    }
                    else
                    {
                        if(orig_a < -orig_b)
                        {
                            return -(result);
                        }
                        else
                        {
                            return (result);
                        }
                    }
            }
            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = (get_mag(-a + b));
                    // check OF if sign changed
                    if(check_sign(-a + b) == (0))
                    {
                        if(-orig_a > orig_b)
                        {
                            return -to_twos(result);
                        }
                        else
                        {
                            return to_twos(result);
                        }
                    }
                    else
                    {
                        if(-orig_a > orig_b)
                        {
                            return -(result);
                        }
                        else
                        {
                            return -(result);
                        }
                    }
                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = (get_mag(-a + -b));
                    if(check_sign(-a + -b) == (0))
                    {
                        return -to_twos(result);
                    }
                    else
                    {
                        return -result;
                    }
            }
    }
}

magnitude sub(magnitude a, magnitude b)
{

    magnitude result;
    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a)
    {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = (get_mag(a - b));
                    if(check_sign(result) == (sign_a | sign_b))
                    {
                        return to_twos(result);
                    }
                    else
                    {
                        return result;
                    }

                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = get_mag(a - -b);
                    if(check_sign(result) == (sign_a | sign_b))
                    {
                        return to_twos(result);
                    }
                    else
                    {
                        return result;
                    }
            }

            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = get_mag(-a - b);
                    if(check_sign(result) == (sign_a | sign_b))
                    {
                        return to_twos(result);
                    }
                    else
                    {
                        return result;
                    }
                    // the sign of b is -, because the MSB is 1
                case 1:
                    to_twos(get_mag(-a + b));
                    if(check_sign(result) == (sign_a | sign_b))
                    {
                        return to_twos(result);
                    }
                    else
                    {
                        return result;
                    }
            }
    }
} // a - b
magnitude multi(magnitude a, magnitude b)
{

    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a)
    {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    return get_mag(a * b);
                    // the sign of b is -, because the MSB is 1
                case 1:
                    return to_twos(get_mag(a * -b));
            }
            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    return to_twos(get_mag(-a * b));
                    // the sign of b is -, because the MSB is 1
                case 1:
                    return to_twos(get_mag(-a * -b));
            }
    }
} // a * b

// true = 1, false = 0
int equal(magnitude a, magnitude b)
{ return (get_mag(a) == get_mag(b)) && (check_sign(a) == check_sign(b)); } // a = b
int greater(magnitude a, magnitude b)
{

    if(check_sign(a) == 0 && check_sign(b) == 1)
    {
        return 1;
    }
    else if(check_sign(a) == check_sign(b) && check_sign(a) == 0)
    {
        return get_mag(a) > get_mag(b);
    }
    else if(check_sign(a) == check_sign(b) && check_sign(a) == 1)
    {
        return get_mag(a) < get_mag(b);
    }
    else
    {
        return 0;
    }
} // a > b

