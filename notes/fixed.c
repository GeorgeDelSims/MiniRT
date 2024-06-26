#include "fixed.h"

// Convert an integer to fixed-point
fixed int_to_fixed(int i) 
{
    return (i * SCALE_FACTOR);
}

// Convert a fixed-point number to an integer
int fixed_to_int(fixed f) 
{
    return (f / SCALE_FACTOR);
}

// Convert a floating-point number to fixed-point
fixed float_to_fixed(float f) 
{
    return ((fixed)(f * SCALE_FACTOR));
}

// Convert a fixed-point number to floating-point
float fixed_to_float(fixed f) 
{
    return ((float)f / SCALE_FACTOR);
}

// Fixed-point multiplication
fixed fixed_mul(fixed a, fixed b) 
{
    return ((a * b) / SCALE_FACTOR);
}

// Fixed-point division
fixed fixed_div(fixed a, fixed b) 
{
    return ((a * SCALE_FACTOR) / b);
}

fixed   fixed_square(fixed a)
{
    return (fixed_mul(a, a));
}

fixed   fixed_sqrt(fixed a)
{
    fixed   result;
    fixed   root;

    if (a <= 0)
        return (0);
    root = a;
    while (1)
    {
        result = (root + fixed_div(a, root)) / 2;
        if (result == root || result == root + 1)
            break;
        root = result;
    }
    return (result);
}

/*
int main() 
{
    fixed a = float_to_fixed(1.5);
    fixed b = float_to_fixed(2.25);

    fixed sum = fixed_add(a, b);
    fixed diff = fixed_sub(a, b);
    fixed prod = fixed_mul(a, b);
    fixed quot = fixed_div(a, b);

    printf("a = %f\n", fixed_to_float(a));
    printf("b = %f\n", fixed_to_float(b));
    printf("sum = %f\n", fixed_to_float(sum));
    printf("diff = %f\n", fixed_to_float(diff));
    printf("prod = %f\n", fixed_to_float(prod));
    printf("quot = %f\n", fixed_to_float(quot));

    return (0);
}
*/