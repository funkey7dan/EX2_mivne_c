// ***REMOVED*** Daniel Bronfman

#include <stdio.h>
#include "ex2.h"

#define MAG_MASK 0x7FFFFFFF
#define POS_MASK 0x80000000

int check_sign(magnitude a) {


    if (POS_MASK & a) {
        return 1;
    } else {
        return 0;
    }
}

// return the magnitude of the number
magnitude get_mag(magnitude a) {
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

int to_twos(magnitude a) {
    return ~a + 1;
}


// a + b
magnitude add(magnitude a, magnitude b) {

    magnitude result;
    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a) {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = a + b;
                    return get_mag(result);

                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = a + (-b);
                    // the positive number is greater, we expect a positive
                    if (a > b) {
                        return get_mag(result);
                    } else {
                        return -(get_mag(result));
                    }
            }
            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = (-a) + (b);
                    // the positive number is greater, we expect a negative
                    if (a > b) {
                        return -(get_mag(result));
                    } else {
                        return get_mag(result);
                    }

                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = -a - b;
                    return -(get_mag(result));
            }
    }


}

/*
magnitude sub(magnitude a, magnitude b) {

    magnitude result;
    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a) {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = (get_mag(a - b));
                    if (check_sign(result) == (sign_a | sign_b)) {
                        return to_twos(result);
                    } else {
                        return result;
                    }

                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = get_mag(a - -b);
                    if (check_sign(result) == (sign_a | sign_b)) {
                        return to_twos(result);
                    } else {
                        return result;
                    }
            }

            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = get_mag(-a - b);
                    if (check_sign(result) == (sign_a | sign_b)) {
                        return to_twos(result);
                    } else {
                        return result;
                    }
                    // the sign of b is -, because the MSB is 1
                case 1:
                    to_twos(get_mag(-a + b));
                    if (check_sign(result) == (sign_a | sign_b)) {
                        return to_twos(result);
                    } else {
                        return result;
                    }
            }
    }
} // a - b
*/
magnitude sub(magnitude a, magnitude b) {

    magnitude result;
    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a) {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = a - b;
                    if (a > b)
                        return get_mag(result);
                    else
                        return -get_mag(result);


                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = a - (-b);
                    return get_mag(result);
            }
            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    result = (-a) - (b);
                    return -(get_mag(result));

                    // the sign of b is -, because the MSB is 1
                case 1:
                    result = -a - (-b);
                    if (a > b)
                        return -(get_mag(result));
                    else
                        return get_mag(result);
            }
    }


}

magnitude multi(magnitude a, magnitude b) {

    int sign_a = check_sign(a);
    int sign_b = check_sign(b);
    a = get_mag(a);
    b = get_mag(b);
    switch (sign_a) {
        // the sign of a is +, because the MSB is 0
        case 0:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    return get_mag(a * b);
                    // the sign of b is -, because the MSB is 1
                case 1:
                    return -(get_mag(a * -b));
            }
            // the sign of a is -, because the MSB is 1
        case 1:
            switch (sign_b) {
                // the sign of b is +, because the MSB is 0
                case 0:
                    return -(get_mag(-a * b));
                    // the sign of b is -, because the MSB is 1
                case 1:
                    return (get_mag(-a * -b));
            }
    }
} // a * b

// true = 1, false = 0
int equal(magnitude a, magnitude b) {
    if ((a == -2147483648 && b == 0) || ((b == -2147483648 && a == 0))) {
        return 1;
    }
    return (get_mag(a) == get_mag(b)) && (check_sign(a) == check_sign(b));
} // a = b
int greater(magnitude a, magnitude b) {
    if (equal(a, b) == 1) {
        return 0;
    } else if (check_sign(a) == 0 && check_sign(b) == 1) {
        return 1;
    } else if (check_sign(a) == check_sign(b) && check_sign(a) == 0) {
        return get_mag(a) > get_mag(b);
    } else if (check_sign(a) == check_sign(b) && check_sign(a) == 1) {
        return get_mag(a) < get_mag(b);
    } else {
        return 0;
    }
} // a > b
