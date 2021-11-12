// ***REMOVED*** Daniel Bronfman

#include <stdio.h>
#include <limits.h>
#include "ex2.h"
#define MASK (~0)>>1


// TODO delete this?
int check_sign(magnitude a)
{

    unsigned int mask = 0x20000000;
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
unsigned int get_mag(magnitude a){
//    if(a>0){
//
//    }
//    else{
//        int const mask = (a>>31)<<31;
//        unsigned int a_mag = ~(a&mask);
//        return (a_mag);
//    }
    int a_mag = a&MASK;
    return (a_mag);
}

// a + b
magnitude add(magnitude a, magnitude b)
{
    magnitude mag_res = get_mag(a)+ get_mag(b);
    int sign = check_sign(a) ^ check_sign(b);
    return (mag_res | (mag_res & MASK));
    /*int sign_a = check_sign(a);
    int sign_b = check_sign(b);

    switch (sign_a)
    {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    return a + b;
                    // the sign of b is -, because the MSB is 1
                case 1:
                    return a - b;
            }
            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b)
            {
                // the sign of b is +, because the MSB is 0
                case 0:
                    return -a + b;
                    // the sign of b is -, because the MSB is 1
                case 1:
                    return -a - b;

            }
    }*/
}

magnitude sub(magnitude a, magnitude b)
{

    return 0;
} // a - b
magnitude multi(magnitude a, magnitude b)
{

    return 0;
} // a * b

// true = 1, false = 0
int equal(magnitude a, magnitude b)
{ return 0; } // a = b
int greater(magnitude a, magnitude b)
{ return 0; } // a > b

